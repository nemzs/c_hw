#include <iostream>
#include "rational.h"

using namespace std;

void rational::goPrime() {
    int justDoIt = __gcd(num, denom);
    if (justDoIt != 0) {
        num /= justDoIt;
        denom /= justDoIt;
    }
}

rational::rational(int a) {
    num = a;
    denom = 1;
}

rational::rational(int a, int b) {
    num = a;
    denom = b;
}

int rational::getNum() const {
    return (num);
}

int rational::getDenom() const {
    return (denom);
}

rational rational::operator+(const rational &b) const {
    rational c(this->getNum() * b.getDenom() + b.getNum() * this->getDenom(), this->getDenom() * b.getDenom());
    c.goPrime();
    return (c);
}

rational rational::operator-(const rational &b) const {
    rational c(this->getNum() * b.getDenom() - b.getNum() * this->getDenom(), this->getDenom() * b.getDenom());
    c.goPrime();
    return (c);
}

rational rational::operator*(const rational &right) const {
    return (rational(this->getNum() * right.getNum(), this->getDenom() * right.getDenom()));
}

rational rational::operator/(const rational &right) const {
    return (rational(this->getNum() * right.getDenom(), this->getDenom() * right.getNum()));
}