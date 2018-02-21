#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <fstream>
#include "FormulaTree.hpp"
using namespace std;

vector<string> stoFormula(const string &);
string stoFile(const string &);

int main()
{
    string line;
    cout << ">> ";
    while (getline(cin, line)) {
        auto flag = find_if_not(line.begin(), line.end(),
            [](char c) {
                return c == ' ';
            });
        if (*flag == '-') {
            ifstream is(stoFile(line));
            string line2;
            while (getline(is, line2)) {
                FormulaTree ff(stoFormula(line2));
                cout << ">> " << line2 << " = "
                     << calc(ff) << endl;
            }
            cout << ">> ";
        }
        else if (*flag == 'q')
            break;
        else {
            FormulaTree fs(stoFormula(line));
            cout << ">> " << calc(fs) << endl;
            cout << ">> ";
        }
    }

    return 0;
}

vector<string> stoFormula(const string &s)
{
    vector<string> ret;
    string number;
    for (const char c : s) {
        if (c == ' ')
            continue;
        if (!isdigit(c)) {
            if (!number.empty()) {
                ret.push_back(number);
                number.clear();
            }
            ret.emplace_back(1,c);
        }
        else {
            number.push_back(c);
        }
    }
    if (!number.empty())
        ret.push_back(number);

    return ret;
}

string stoFile(const string &s)
{
    string file;
    for (auto c = s.begin(); c != s.end(); ++c) {
        if (*c == ' ')
            continue;
        if (*c == '-' && *(c + 1) == 'f') {
            c += 2;
            continue;
        }
        file.push_back(*c);
    }
    return file;
}
