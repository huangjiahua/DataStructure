#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <cmath>

using std::vector;
using std::endl;
using std::cout;
using std::string;

struct Chess {
    int rank;
    int col;
    Chess(int i, int j): rank(i), col(j) { }
};

int args(int, char *argv[]);
std::ostream& print(std::ostream&, const vector<Chess>&);
bool Queens(int N, vector<Chess>, Chess, int&, std::ostream&);
bool check_board(Chess , const vector<Chess>&);

int main(int argc, char *argv[])
{
    int count;
    const int N = args(argc, argv);
    std::ostringstream os;
    vector<Chess> board;
    Queens(N, board, Chess(0, 0), count, os);
    cout << os.str() << endl;

    return 0;
}

int args(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Wrong Usage" << endl;
        exit(EXIT_FAILURE);
    }
    string temp = argv[1];
    return std::stoi(temp);
}

std::ostream& print(std::ostream& os, const vector<Chess>& c)
{
    for (const auto& i : c) {
        for (int j = 1; j <= c.size(); ++j) {
            if (j == i.col)
                os << 1 << " ";
            else
                os << 0 << " ";
        }
        os << endl;
    }
    for (const auto& i : c) {
        os << "(" << i.rank << ", " << i.col << ") ";
    }
    os << endl;
    os << endl;
    return os;
}

bool Queens(int N, vector<Chess> board, Chess chess,
            int& count, std::ostream& os)
{
    if (!check_board(chess, board))
        return false;
    if (chess.rank != 0)
        board.push_back(chess);
    if (board.size() == N) {
        ++count;
        os << count << "." << endl;
        print(os, board);
        return true;
    }

    for (int i = 1; i <= N; ++i)
        Queens(N, board, Chess(chess.rank+1, i), count, os);

    return false;
}

bool check_board(Chess chess, const vector<Chess>& board)
{
    if (board.size() == 0)
        return true;
    for (const auto& c : board) {
        if (chess.col == c.col)
            return false;
        if (abs(c.col - chess.col) == abs(c.rank - chess.rank))
            return false;
    }
    return true;
}
