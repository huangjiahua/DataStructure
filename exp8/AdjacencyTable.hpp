#ifndef _AdjacencyTable_hpp_
#define _AdjacencyTable_hpp_
#include <vector>
#include <memory>
#include <iostream>
#include <unordered_set>

struct TableNode {
    int data;
    std::shared_ptr<TableNode> next;
    TableNode(int i, std::shared_ptr<TableNode> p): data(i), next(p) { }
};

class AdjacencyTable {
friend void mazeToTable(const std::vector<std::vector<int>>&, AdjacencyTable&);
friend void findAllResults(const AdjacencyTable&, std::vector<std::vector<int>>&);
friend void findAllResults(std::shared_ptr<TableNode> p,
        std::vector<std::vector<int>>& r, std::unordered_set<int> found,
        std::vector<int> curr);
public:
    AdjacencyTable() = default;
    void set(int i, int j) { r = i; c = j; }
    AdjacencyTable(int i, int j): r(i), c(j) { }
    using iterator = std::vector<std::shared_ptr<TableNode>>::iterator;
    iterator begin() { return array.begin(); }
    iterator end() { return array.end(); }
    void addItem(int index, int data)
    {
        auto p = array[index];
        auto oldFirst = p->next;
        p->next = std::make_shared<TableNode>(data, oldFirst);
    }
    std::shared_ptr<TableNode>& operator[](std::size_t i)
    {
        return array[i];
    }
    const std::shared_ptr<TableNode>& operator[](std::size_t i) const
    {
        return array[i];
    }
    int rank() const { return r; }
    int col() const { return c; }
private:
    int r, c;
    std::vector<std::shared_ptr<TableNode>> array;
};



#endif
