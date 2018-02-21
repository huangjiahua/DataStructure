#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream is("test1.txt");
    ofstream os("new.txt");
    string line;
    while (getline(is, line)) {
        string s;
        for (auto i = line.begin(); i != line.end(); ++i) {
            if (*i == '[') {
                while (*i != ']')
                    ++i;
                continue;
            }
            if (*i == ' ')
                continue;
            s.push_back(*i);
        }
        os << s << endl;
    }
}
