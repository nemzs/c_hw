//
// Created by stas on 12.03.16.
//

#ifndef TASK3_RATIONAL_H
#define TASK3_RATIONAL_H


#include <algorithm>


class rational {
private:
    int num, denom;

    void goPrime();

public:
    rational(int);

    rational(int, int);


    int getNum() const;

    int getDenom() const;

    rational operator+(rational const &) const;

    rational operator-(rational const &) const;

    rational operator*(rational const &) const;

    rational operator/(rational const &) const;

};

#endif TASK3_RATIONAL_H