#include <iostream>
#include <string>
#include "kmp.h"
#include "Virus.h"
using namespace std;

int main()
{
    string dna;
    cin >> dna;
    Virus v(std::move(dna));
    string t;
    cin >> t;
    for (int i = 0; i < v.size(); ++i)
        cout << findSubString(t, v.pattern(i)) << endl;;
}
