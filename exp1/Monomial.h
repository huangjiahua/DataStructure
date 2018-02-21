#ifndef _Monomial_h_
#define _Monomial_h_
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
struct Monomial {
    int coefficient;
    int index;
    Monomial(int c, int i): coefficient(c), index(i) { }
    Monomial(const std::string &mono);
};

bool operator<(const Monomial& lhs, const Monomial& rhs) {
    return lhs.index < rhs.index;
}

Monomial operator+(const Monomial& lhs, const Monomial&rhs) {
    if (lhs.index != rhs.index)
        std::cerr << "Wrong+" << std::endl;
    return Monomial(lhs.coefficient + rhs.coefficient, lhs.index);
}

Monomial operator*(const Monomial& lhs, const Monomial& rhs) {
    return Monomial(lhs.coefficient * rhs.coefficient,
                    lhs.index + rhs.index);
}

Monomial &operator+=(Monomial &lhs, const Monomial& rhs)
{
    if (lhs.index != rhs.index)
        std::cerr << "Wrong+=" << std::endl;
    lhs.coefficient += rhs.coefficient;
    return lhs;
}

std::ostream &operator<<(std::ostream &os, const Monomial &m)
{
    if (m.index == 0)
        os << abs(m.coefficient);
    else {
        os << abs(m.coefficient);
        if (m.index == 1)
            os << "x";
        else
            os << "x^" << m.index;

    }

    return os;
}

Monomial::Monomial(const std::string &mono) {
    using std::string;
    index = 1;
    auto iter = mono.cbegin();

    for ( ; iter != mono.cend(); ++iter)
        if (!isdigit(*iter) && !isspace(*iter))
            break;
    coefficient = std::stoi(string(mono.cbegin(), iter));
    if (iter == mono.cend())
        index = 0;
    else {
        while (iter != mono.cend() && !isdigit(*iter)) {
            if (*iter == '-')
                index = -1;
            ++iter;
        }
        if (iter == mono.cend())
            index = 1;
        else
            index *= std::stoi(string(iter, mono.cend()));
    }
}


#endif
