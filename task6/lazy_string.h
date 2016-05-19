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
    /*
        creates an empty string
        *return lazy_string (size = length = 0, undefined capacity);
    */
    lazy_string();

    /*
        creates an lazy_string containing chars from str
        *arg std::string
    */
    lazy_string(const std::string str);

    /*
        returns lazy_string that contain chars between [st, st + len)
        *arg st - first char of the substring
        *arg len - len of the substring
        *return An empty string if st==size()
        *return substring
        *throws std::out_of_range("lazy_string") if len > size()
    */
    lazy_string substr(size_t st, size_t len);

    /*

        returns lazy_string that contain chars from st to end of the string
        *arg st - first char of the substring
        *return substring from st to end of the string
        *throws std::out_of_range("lazy_string") if len > size()
    */
    lazy_string substr(size_t st);

    /*
        returns a reference to the char at st position
        function check if valid position, if not throws std::out_of_range
        *arg st - first char of the substring
        *return a reference to the char
        *throws std::out_of_range("lazy_string") if(st >= size() || st < 0)
    */
    char_ref at(size_t index);

    char at(size_t index) const;

    /*
        return the number of char in the string
        *return the number of chars in the string
    */
    size_t length();

    /*
        return the number of char in the string
        *return the number of chars in the string
    */
    size_t size();

    /*
        Get the string from the input stream in lazy, old version of lazy replaced with new string
        *arg in std::istream input stream wich chars are extracting
        *lazy lazy lazy_string string to replace with new excracted string
        *return in argument
    */
    friend std::istream &operator>>(std::istream &in, lazy_string &lazy);

    /*
        Put the string into the output stream
        *arg out std::ostream output stream where the string is put
        *lazy lazy lazy_string string to excract chars and put into stream
        *return out argument
    */
    friend std::ostream &operator<<(std::ostream &out, lazy_string &lazy);

    /*
        returns a reference to the char at st position
        without validation check
        *param st - first char of the substring
        *return if pos == size(), a reference to null char
        *return a reference to the char
        *throws std::out_of_range("lazy_string") if(st >= size() || st < 0)
    */
    char_ref operator[](size_t pos);

    char operator[](size_t pos) const;

    /*
        creates a std::string copy of chars of current lazy_string
        *return a std::string copy of chars of current lazy_string
    */
    operator std::string();

private:
    lazy_string(size_t start, size_t len, std::shared_ptr<std::string> some);

    std::shared_ptr<std::string> some;
    size_t start, len;
};


#endif //TASK6_LAZY_STRING_H

