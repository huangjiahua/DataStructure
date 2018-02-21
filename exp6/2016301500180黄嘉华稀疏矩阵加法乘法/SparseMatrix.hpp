#ifndef _SparseMatrix_h_
#define _SparseMatrix_h_

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
using std::vector;

class MatrixNode {
public:
    int rank;
    int col;
    int value;
    MatrixNode(int r, int c, int v): rank(r), col(c), value(v) { }
};

bool operator<(const MatrixNode &lhs, const MatrixNode &rhs)
{
    if (lhs.rank < rhs.rank)
        return true;
    else if (lhs.rank == rhs.rank)
        return lhs.col < lhs.col;
    return false;
}

class SparseMatrix {
friend SparseMatrix operator*(const SparseMatrix& lhs, const SparseMatrix& rhs);
friend std::ostream& operator<<(std::ostream&, const SparseMatrix&);
private:
    int r, c;
    vector<MatrixNode> data;
public:
    int rank() const { return r; }
    int col() const { return c; }
    SparseMatrix(int i, int j): r(i), c(j) { }
    SparseMatrix(const SparseMatrix& rhs): r(rhs.r), c(rhs.c),
                                           data(rhs.data) { }
    SparseMatrix(const vector<vector<int>>&& m): r(m.size()), c(m[0].size())
    {
        for (int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if (m[i][j] != 0)
                    data.emplace_back(i, j, m[i][j]);
    }



    SparseMatrix& operator+=(const SparseMatrix& lhs)
    {
        if (r != lhs.r || c != lhs.c) {
            throw "Wrong Grammer";
        }
        for (const auto & item : lhs.data) {
            auto iter = std::find_if(data.begin(), data.end(),
                [item](MatrixNode &mn){
                return (item.rank == mn.rank && item.col == mn.col);
            });
            if (iter == data.cend())
                data.push_back(item);
            else
                iter->value += item.value;
        }
        std::sort(data.begin(), data.end());
        return *this;
    }

    SparseMatrix& traverse()
    {
        for (auto &item : data)
            std::swap(item.rank, item.col);
        std::swap(c, r);
        std::sort(data.begin(), data.end());
        return *this;
    }


};

SparseMatrix operator*(const SparseMatrix& lhs, const SparseMatrix& rhs)
{
    if (lhs.c != rhs.r)
        throw "Wrong Grammer";
    vector<MatrixNode> vn;
    int rank = lhs.r, col = rhs.c;
    for (int i = 0; i < rank; ++i)
        for (int j = 0; j < col; ++j) {
            auto literb = std::find_if(lhs.data.begin(), lhs.data.end(),
                [i](const MatrixNode& m) {
                    return m.rank == i;
                });
            auto riterb = std::find_if(rhs.data.begin(), rhs.data.end(),
                [j](const MatrixNode& m) {
                    return m.col == j;
                });

            if (literb == lhs.data.end() || riterb == rhs.data.end())
                break;

            auto litere = std::find_if(literb, lhs.data.end(),
                [i](const MatrixNode& m) {
                    return m.rank != i;
                });
            auto ritere = std::find_if(riterb, rhs.data.end(),
                [j](const MatrixNode& m) {
                    return m.col != j;
                });

            int value = 0;
            int l, r;
            for (int k = 0; k < lhs.col(); ++k) {
                l = r = 0;
                if (literb != litere && literb->col == k) {
                    l = literb->value;
                    ++literb;
                }
                if (riterb != ritere && riterb->rank ==k) {
                    r = riterb->value;
                    ++riterb;
                }
                value += l * r;
            }
            if (value != 0) {
                vn.emplace_back(i, j, value);
            }
        }
    SparseMatrix ret(rank, col);
    std::copy(vn.begin(), vn.end(), std::back_inserter(ret.data));
    return ret;
}

SparseMatrix operator+(const SparseMatrix& lhs, const SparseMatrix& rhs)
{
    SparseMatrix ret(lhs);
    ret += rhs;
    return ret;
}

std::ostream& operator<<(std::ostream&os, const SparseMatrix& m)
{
    auto iter = m.data.cbegin();
    for (int i = 0; i < m.rank(); ++i) {
        for (int j = 0; j < m.col(); ++j) {
            if (i == iter->rank && j == iter->col) {
                os << std::setw(2) << iter->value;
                if (iter != m.data.cend())
                    ++iter;
            }
            else
                os << std::setw(2) << 0;
            os << ' ';
        }
        os << std::endl;;
    }
    return os;
}




#endif
