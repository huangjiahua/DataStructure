#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
    string line;
    vector<vector<int>> v;
    int data;
    while (getline(cin, line)) {
        if (line == "end")
            break;
        vector<int> vi;
        istringstream iss(line);
        while (iss >> data)
            vi.push_back(data);
        v.push_back(vi);
    }
    for (auto & i : v) {
        for (auto & j : i)
            cout << j << " ";
        cout << endl;
    }
}
