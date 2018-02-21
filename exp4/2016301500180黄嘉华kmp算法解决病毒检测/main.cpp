#include <iostream>
#include <string>
#include <fstream>
#include "Virus.h"
#include "kmp.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

/*
 * kmp find the substring and return the index
 */
int findSubString(const string& t, const PatternString& p);

/*
 * print the output
 */
std::ostream& print_output(std::ostream&, int, const string&, const string&);

int main()
{
    while (true) {
        string input, pattern;
        cout << "Please enter the target DNA or the file name(-filename)"
             << "\nEnter 'q' to quit: ";
        cin >> input;
        if (input[0] == 'q')
            break; // terminate the program
        if (input[0] == '-') { // input with file
            std::ifstream in(input.substr(1, input.size()-1));
            string word;
            input.clear();
            while (in >> word)
                input += word;
        }
        // the dna target string is ready
        cout << "Please enter the pattern DNA: ";
        cin >> pattern;
        Virus virus(pattern);
        int index = 0;
        // the pattern is ready;
        for (int i = 0; i != virus.size(); ++i) {
            index = findSubString(input, virus.pattern(i));
            if (index != -1) // found!
                break;
        }
        print_output(cout, index, input, pattern);
    }
}

std::ostream& print_output(std::ostream& os, int i, const string& dna,
                           const string& v)
{
    if (i == -1) {
        os << "Negative!" << endl;
        os << "Not infected" << endl;
        return os;
    }
    os << "Positive!" << endl;
    os << "Virus DNA begins at pos " << i << "." << endl;
    int start = i > 4 ? i - 5 : 0;
    int end = dna.size() - i > 5 ? i + v.size() + 5 : dna.size();
    string line1 = dna.substr(start, end-start);
    line1 = "..." + line1 + "...";
    string line2(line1.size(), ' ');
    line2[3 + i - start] = '|';
    line2[3 + i - start + v.size() - 1] = '|';
    cout << line1 << "\n"
         << line2 << endl;
    return os;
}
