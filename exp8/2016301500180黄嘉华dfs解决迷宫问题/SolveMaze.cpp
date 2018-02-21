#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include "AdjacencyTable.hpp"
#include "MazeFunctions.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
    if (argc < 3) {
        cerr << "Wrong Usage -> SolveMaze -t test.txt" << endl;
        return -1;
    }
    int mode;
    mode = (argv[1][1] == 't' ? 0 : 1);
    ifstream input(argv[2]);

    vector<vector<int>> maze;
    vector<vector<int>> results;
    AdjacencyTable table;
    makeMaze(input, maze);
    mazeToTable(maze, table);
    findAllResults(table, results);

    for (const auto& v : maze) {
        for (const auto& i : v)
            cout << i << " ";
        cout << endl;
    }
    cout << endl;

    switch (mode) {
        case 0: {
            for (const auto& v : results) {
                for (int i = ctoi(1, 1, table.col());
                     ; i = v[i]) {
                    cout << "(" << itoc(i, table.col()).first
                         << ", " << itoc(i, table.col()).second
                         << ")";
                    if (i == v[i])
                        break;
                    cout << " -> ";
                }
                cout << '\n' << endl;
            }
            break;
        }

        case 1: {
            vector<unordered_set<int>> vs;
            for (const auto& v : results) {
                vs.emplace_back(v.begin(), v.end());
                vs.back().insert(ctoi(1, 1, table.col()));
            }
            for (int n = 0; n < vs.size(); ++n) {
                for (int i = 0; i < table.rank(); ++i) {
                    for (int j = 0; j < table.col(); ++j) {
                        if (vs[n].find(ctoi(i, j, table.col())) != vs[n].end())
                            cout << 1 << " ";
                        else
                            cout << "_" << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            break;
        }
        default:
            break;
    }

    return 0;
}
