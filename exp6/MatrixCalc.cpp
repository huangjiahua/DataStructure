#include <iostream>
#include "SparseMatrix.hpp"
#include <vector>
#include <sstream>
#include <string>
using namespace std;

vector<vector<int>> getFullMatrix(std::istream& os = cin);

int main()
{
    while (true) {
        cout << "What's the operation do you want to do?\n"
             << "T--traverse  +--add  *--multiply  q--quit"
             << endl;
        string operation;
        getline(cin, operation);
        if (operation[0] == 'q')
            break;
        switch (operation[0]) {
            case 'T': {
                cout << "Input the matrix you want to traverse" << endl;
                SparseMatrix m(std::move(getFullMatrix()));
                m.traverse();
                cout << '\n' << m << endl;
                break;
            }

            case '+': {
                cout << "Input the left matrix" << endl;
                SparseMatrix l(std::move(getFullMatrix()));
                cout << "Input the right matrix" << endl;
                SparseMatrix r(std::move(getFullMatrix()));
                cout << l + r << endl;
                break;
            }

            case '*': {
                cout << "Input the left matrix" << endl;
                SparseMatrix l(std::move(getFullMatrix()));
                cout << "Input the right matrix" << endl;
                SparseMatrix r(std::move(getFullMatrix()));
                cout << '\n' << l * r << endl;
                break;
            }
            default: break;
        }
    }
}

vector<vector<int>> getFullMatrix(std::istream& is)
{
    vector<vector<int>> ret;
    string line;
    while (true) {
        getline(is, line);
        if (line == "end")
            break;
        istringstream iss(line);
        int data;
        vector<int> rank;
        while (iss >> data) {
            rank.push_back(data);
        }
        ret.push_back(std::move(rank));
    }
    return ret;
}
