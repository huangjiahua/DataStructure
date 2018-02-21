#include "FormulaTree.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;


int main()
{
    vector<string> f1;
    string word;
    while (cin >> word) {
        f1.push_back(word);
    }
    FormulaTree tree(f1);



    cout << calc(tree) << endl;

}
