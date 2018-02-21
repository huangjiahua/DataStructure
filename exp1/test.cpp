#include "Polynomial.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    Monomial p("3x^5");
    Monomial q("6x^7");

    cout << p * q << endl;
}
