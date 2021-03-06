#include <iostream>
#include <cstdio>
#include <memory>
#include <typeinfo>
#include "lazy_string.h"

using namespace std;

//constructors
lazy_string::lazy_string() : start(0), len(0), some(std::make_shared<std::string>("")) { };

lazy_string::lazy_string(string str) : start(0), len(str.length()), some(std::make_shared<std::string>(str)) { };

lazy_string::lazy_string(size_t start, size_t len, std::shared_ptr<std::string> some) : start(start), len(len),
                                                                                        some(some) { };

istream &operator>>(istream &in, lazy_string &ns) {
    auto tmp = std::make_shared<string>();
    in >> *tmp;
    ns.start = 0;
    ns.len = (*tmp).length();
    ns.some = tmp;
}

ostream &operator<<(ostream &out, lazy_string &ns) {
    out << ns.some->substr(ns.start, ns.len);
}

lazy_string::operator string() {
    return some->substr(start, len);
}

lazy_string lazy_string::substr(size_t st, size_t g_len) {
    if (st > len) {
        throw out_of_range("lazy_string");
    }
    if (g_len + st > len) {
        return (lazy_string(st + start, len - st, some));
    }
    return (lazy_string(st + start, g_len, some));
}

lazy_string lazy_string::substr(size_t st) {
    if (st > len) {
        throw out_of_range("lazy_string");
    }
    return (lazy_string(st + start, len - st, some));
}


lazy_string::char_ref::char_ref(lazy_string * some, size_t
index) :

lazy(some), index(index) { }

lazy_string::char_ref lazy_string::operator[](size_t i) {
    return char_ref(const_cast<lazy_string *>(this), i);
}

lazy_string::char_ref::operator char() const {
    return ((*lazy->some)[lazy->start + index]);
}

char lazy_string::operator[](size_t index) const {
    return ((*some)[start + index]);
}

lazy_string::char_ref &lazy_string::char_ref::operator=(char nchar) {
    if (lazy->some.use_count() > 1) {
        lazy->some = std::make_shared<std::string>(lazy->some->substr(lazy->start, lazy->len));
        lazy->start = 0;
    }
    (*lazy->some)[index + lazy->start] = nchar;
    return (*this);
}

lazy_string::char_ref lazy_string::at(size_t index) {
    if (index >= len || index < 0)
        throw out_of_range("lazy_string");
    return char_ref(const_cast<lazy_string *>(this), index);
}

size_t lazy_string::length() {
    return len;
}

size_t lazy_string::size() {
    return len;
}
/*
int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt","w",stdout);
    string s = "tniceing!!!";
    lazy_string test("test");
    cin >> test;
    cout << test.length();
    cout << test.size();
    //cout<<test;
}
*/

