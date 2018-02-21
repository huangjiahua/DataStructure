#include <fstream>
#include <cctype>
#include <cstdio>
#include <iostream>

using namespace std;


int main()
{
    std::ifstream input;
    input.open("names.txt");

    string word;
    while (input >> word)
        cout << word << endl;
}
