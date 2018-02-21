#ifndef _ChessPoint_h_
#define _ChessPoint_h_
/*
   By @huangjiahua 2016301500180
 */

struct ChessPoint {
    int rank;
    int col;
    ChessPoint(int x, int y):rank(x), col(y) { }
};

bool operator==(const ChessPoint &lhs, const ChessPoint &rhs)
{
    return lhs.rank == rhs.rank && lhs.col == rhs.col;
}

bool operator!=(const ChessPoint &lhs, const ChessPoint &rhs)
{
    return !(lhs == rhs);
}



#endif
