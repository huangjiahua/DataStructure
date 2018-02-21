#include <iostream>
#include <fstream>
#include "MazeFunctions.hpp"
#include "AdjacencyTable.hpp"
#include <vector>
using namespace std;

int main()
{
	vector<vector<int>> temp;
	ifstream input("text2.txt");
	makeMaze(input, temp);
	for (const auto &v : temp) {
		for (const auto &i : v)
			cout << i << " ";
		cout << endl;
	}
	cout << endl;

	AdjacencyTable t;
	mazeToTable(temp, t);
	testPrint(cout, t);
    cout << endl;
    vector<vector<int>> results;
    findAllResults(t, results);
    for (const auto &v : results) {
        for (const auto &i : v)
            cout << i << " ";
        cout << endl;
    }



}
