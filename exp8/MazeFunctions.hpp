#ifndef _MazeFunctions_hpp_
#define _MazeFunctions_hpp_
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include "AdjacencyTable.hpp"

void makeMaze(std::ifstream& is,  std::vector<std::vector<int>>& maze)
{
    std::string str;
    while (getline(is, str)) {
        std::istringstream input(str);
        std::vector<int> line;
        int i;
        while (input >> i)
            line.push_back(i);
        maze.push_back(line);
    }
}

int ctoi(int i, int j, int b)
{
    return i * b + j;
}

std::pair<int, int> itoc(int index, int b)
{
    return {index / b, index % b};
}

void mazeToTable(const std::vector<std::vector<int>>& maze,
        AdjacencyTable& table)
{
    int N = maze[0].size();
    table.set(maze.size(), N);
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < N; ++j) {
            int curr = ctoi(i, j, N);
            table.array.push_back(
                    std::make_shared<TableNode>(curr, nullptr));
            if (maze[i][j] == 1)
                continue;
            if (i - 1 >= 0 && maze[i-1][j] == 0)
                table.addItem(curr, ctoi(i-1, j, N));
            if (j - 1 >= 0 && maze[i][j-1] == 0)
                table.addItem(curr, ctoi(i, j-1, N));
            if (i + 1 < maze.size() && maze[i+1][j] == 0)
                table.addItem(curr, ctoi(i+1, j, N));
            if (j + 1 < N && maze[i][j+1] == 0)
                table.addItem(curr, ctoi(i, j+1, N));
        }
    }
}

std::ostream& testPrint(std::ostream& os,  AdjacencyTable& t)
{
    for (auto p : t) {
        auto p1 = p;
        os << "(";
        os << itoc(p1->data, t.col()).first << ", "
           << itoc(p1->data, t.col()).second;
        os << ")" << " -> ";
        p1 = p1->next;
        while (p1 != nullptr) {
            os << "(";
            os << itoc(p1->data, t.col()).first << ", "
               << itoc(p1->data, t.col()).second;
            os << ")" << " -> ";
            p1 = p1->next;
        }
        std::cout << "NULL" << std::endl;
    }
    return os;
}

void findAllResults(std::shared_ptr<TableNode> p,
        std::vector<std::vector<int>>& r, std::unordered_set<int> found,
        std::vector<int> curr, const AdjacencyTable& t)
{
    if (p->data == ctoi(t.rank()-2, t.col()-2, t.col())) {
        curr[p->data] = p->data;
        r.push_back(curr);
        return ;
    }
    auto np = p->next;
    while (np != nullptr) {
        if (found.find(np->data) == found.end()) {
            curr[p->data] = np->data;
            found.insert(np->data);
            findAllResults(t[np->data], r, found, curr, t);
        }
        np = np->next;
    }
}

void findAllResults(const AdjacencyTable& t, std::vector<std::vector<int>>& r)
{
    std::unordered_set<int> found;
    std::vector<int> result(t.col() * t.rank(), -1);
    found.insert(ctoi(1, 1, t.col()));
    findAllResults(t[ctoi(1, 1, t.col())], r, found, result, t);
}



#endif
