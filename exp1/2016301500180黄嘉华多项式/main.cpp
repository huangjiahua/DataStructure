#include <string>
#include <iostream>
#include "Polynomial.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main()
{
    string line;
    while (getline(cin, line)) {
        auto i = line.cbegin();
        auto j = line.cbegin();
        char operation;

        while (*i == ' ') {
            ++i;
            ++j;
        }
        while (*j != ')')
            ++j;
        Polynomial l(string(i + 1, j));

        while (*j != '*' && *j != '+')
            ++j;
        operation = *j;

        while (*j != '(')
            ++j;
        i = j;
        while(*j != ')')
            ++j;
        Polynomial r(string(i + 1, j));

        if (operation == '*')
            cout << l * r << endl;
        else if (operation == '+')
            cout << l + r << endl;
    }
    return 0;
}
