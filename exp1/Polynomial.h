#ifndef _Polynomial_h_
#define _Polynomial_h_
#include "OrderedList.h"
#include "Monomial.h"
#include <string>

class Polynomial: public OrderedList<Monomial> {
public:
    void add_monomial(Monomial item);
    Polynomial(const std::string &poly);
    Polynomial() = default;
    Polynomial &operator+=(const Polynomial& rhs);
};

void Polynomial::add_monomial(Monomial item)
{
    auto curr = first;
    for ( ; curr != nullptr; curr = curr->next)
        if (curr->item.index == item.index) {
            curr->item += item;
            return ;
        }

    if (first == nullptr || item < first->item) {
        auto oldfirst = first;
        first = std::make_shared<Node<Monomial>>(item);
        first->next = oldfirst;
        ++sz;
        return ;
    }

    curr = first;
    auto last = first;
    while (curr != nullptr && curr->item < item) {
        last = curr;
        curr = curr->next;
    }
    last->next = std::make_shared<Node<Monomial>>(item);
    last->next->next = curr;
    ++sz;
}

Polynomial::Polynomial(const std::string& poly)
{
    using std::string;
    auto i = poly.cbegin(), j = poly.cbegin();
    int symbol = 1;
    while (j != poly.cend()) {
        for (; j != poly.cend(); ++j) {
            if (j == poly.cbegin())
                continue;
            if (*j == '-') {
                if (*(j - 1) == '^')
                    continue;
                else
                    break;
            }
            if (*j == '+')
                break;
        }
        if (*i == '-') {
            symbol = -1;
            ++i;
        }
        if (*i == '+')
            ++i;

        Monomial newItem(string(i, j));
        newItem.coefficient *= symbol;
        this->add_monomial(newItem);

        i = j;
        if (j == poly.cend())
            break;
        ++j;
        symbol = 1;
    }
}

std::ostream &operator<<(std::ostream &os, const Polynomial &p)
{
    auto curr = p.cbegin();
    for ( ; curr != nullptr; curr = curr->next) {
        if (curr == p.cbegin() && curr->item.coefficient < 0)
            os << "-";
        os << curr->item;
        if (curr->next != nullptr) {
            os << " ";
            os << (curr->next->item.coefficient < 0 ? "- " : "+ ");
        }
    }
    return os;
}

Polynomial &Polynomial::operator+=(const Polynomial &rhs)
{
    auto j = rhs.cbegin();
    for ( ; j != nullptr; j = j->next)
        this->add_monomial(j->item);
    return *this;
}

Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs)
{
    Polynomial ret;
    auto i = lhs.cbegin();
    auto j = rhs.cbegin();
    for ( ; i != nullptr; i = i->next)
        ret.add_monomial(i->item);
    for ( ; j != nullptr; j = j->next)
        ret.add_monomial(j->item);
    return ret;
}

Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs)
{
    Polynomial ret;
    auto i = lhs.cbegin();
    auto j = rhs.cbegin();
    for (; i != nullptr; i = i->next) {
        for (j = rhs.cbegin(); j != nullptr; j = j->next) {
            ret.add_monomial(i->item * j->item);
        }
    }
    return ret;
}





#endif
