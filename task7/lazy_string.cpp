#include <iostream>
#include <cstdio>
#include <memory>
#include <typeinfo>
#include "lazy_string.h"

using namespace std;

//constructors
lazy_string::lazy_string() : start(0), len(0), some(std::make_shared<std::string>("")),
                             lock(std::make_shared<ReadWriteLock>()) { };

lazy_string::lazy_string(string str) : start(0), len(str.length()), some(std::make_shared<std::string>(str)),
                                       lock(std::make_shared<ReadWriteLock>()) { };

lazy_string::lazy_string(size_t start, size_t len, std::shared_ptr<std::string> some,
                         std::shared_ptr<ReadWriteLock> lock) : start(start), len(len),
                                                                some(some), lock(lock) { };

ReadWriteLock::ReadWriteLock() : readers(0) { }

ReadWriteLock::ReadWriteLock(const ReadWriteLock &lock) : readers(0) { }

void ReadWriteLock::readLock() {
    mutex.lock();
    readers++;
    mutex.unlock();
}

void ReadWriteLock::readUnlock() {
    readers--;
}

void ReadWriteLock::writeLock() {
    mutex.lock();
    while (readers.load() > 0) {
        this_thread::yield();
    }
}

void ReadWriteLock::writeUnlock() {
    mutex.unlock();
}

istream &operator>>(istream &in, lazy_string &ns) {
    auto tmp = std::make_shared<string>();
    in >> *tmp;
    ns.lock->writeLock();
    auto old_lock = ns.lock;
    ns.lock = std::make_shared<ReadWriteLock>();
    ns.start = 0;
    ns.len = (*tmp).length();
    ns.some = tmp;
    old_lock->writeUnlock();
}

ostream &operator<<(ostream &out, lazy_string &ns) {
    ns.lock->readLock();
    out << ns.some->substr(ns.start, ns.len);
    ns.lock->readUnlock();
    return (out);
}

lazy_string::operator string() {
    lock->readLock();
    string tmp = some->substr(start, len);
    lock->readUnlock();
    return tmp;
}

lazy_string lazy_string::substr(size_t st, size_t g_len) {
    lock->readLock();
    if (st > len) {
        throw out_of_range("lazy_string");
    }
    std::shared_ptr<std::string> tmp_some = some;
    std::shared_ptr<ReadWriteLock> tmp_lock = lock;
    size_t tmp_start = start;
    size_t tmp_len = len;
    lock->readUnlock();
    if (g_len + st > tmp_len) {
        return (lazy_string(st + tmp_start, tmp_len - st, tmp_some, tmp_lock));
    }
    return (lazy_string(st + tmp_start, g_len, tmp_some, tmp_lock));
}

lazy_string lazy_string::substr(size_t st) {
    lock->readLock();
    if (st > len) {
        throw out_of_range("lazy_string");
    }
    std::shared_ptr<std::string> tmp_some = some;
    std::shared_ptr<ReadWriteLock> tmp_lock = lock;
    size_t tmp_start = start;
    size_t tmp_len = len;
    lock->readUnlock();
    return (lazy_string(st + tmp_start, tmp_len - st, tmp_some, tmp_lock));
}


lazy_string::char_ref::char_ref(lazy_string * some, size_t
index) :

lazy(some), index(index) { }

lazy_string::char_ref lazy_string::operator[](size_t i) {
    lock->readLock();
    char_ref tmp = char_ref(const_cast<lazy_string *>(this), i);
    lock->readUnlock();
    return tmp;
}

lazy_string::char_ref::operator char() const {
    lazy->lock->readLock();
    char tmp = (*lazy->some)[lazy->start + index];
    lazy->lock->readUnlock();
    return tmp;
}

char lazy_string::operator[](size_t index) const {
    lock->readLock();
    char tmp = (*some)[start + index];
    lock->readUnlock();
    return tmp;
}

lazy_string::char_ref &lazy_string::char_ref::operator=(char nchar) {
    lazy->lock->writeLock();
    std::shared_ptr<ReadWriteLock> tmp_lock = lazy->lock;
    if (lazy->some.use_count() > 1) {
        lazy->some = std::make_shared<std::string>(lazy->some->substr(lazy->start, lazy->len));
        lazy->start = 0;
        lazy->lock = std::make_shared<ReadWriteLock>();
    }
    (*lazy->some)[index + lazy->start] = nchar;
    tmp_lock->writeUnlock();
    return (*this);
}

lazy_string::char_ref lazy_string::at(size_t index) {
    lock->readLock();
    if (index >= len || index < 0)
        throw out_of_range("lazy_string");
    char_ref tmp = char_ref(const_cast<lazy_string *>(this), index);
    lock->readUnlock();
    return tmp;
}

size_t lazy_string::length() {
    lock->readLock();
    size_t tmp = len;
    lock->readUnlock();
    return tmp;
}

size_t lazy_string::size() {
    return length();
}

