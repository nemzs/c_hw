#ifndef TASK6_LAZY_STRING_H
#define TASK6_LAZY_STRING_H

#include <iostream>
#include <cstdio>
#include <memory>

class lazy_string {
    struct char_ref {
        friend class lazy_string;

        operator char() const;

        char_ref &operator=(char);

    private:
        char_ref(lazy_string *, size_t);

        const size_t index;
        lazy_string *const lazy;
    };

public:
    lazy_string(std::string str) : start(0), len(str.length()), some(std::make_shared<std::string>(str)) { };

    lazy_string substr(size_t st, size_t len);

    lazy_string substr(size_t st);

    char_ref at(size_t index);

    char at(size_t index) const;

    size_t length();

    size_t size();

    friend std::istream &operator>>(std::istream &in, lazy_string &ns);

    friend std::ostream &operator<<(std::ostream &out, lazy_string &ns);

    char_ref operator[](size_t pos);

    char operator[](size_t pos) const;

    operator char();

    operator std::string();

private:
    lazy_string(size_t start, size_t len, std::shared_ptr<std::string> some) : start(start), len(len), some(some) { };
    std::shared_ptr<std::string> some;
    size_t start, len;
};


#endif //TASK6_LAZY_STRING_H

