/*
   By @huangjiahua 2016301500180
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <sstream>
#include "ChessPoint.h"

using std::cout;
using std::cerr;
using std::vector;
using std::endl;
using std::string;

/*
** 计算非行尾棋子的下一个点
 */
ChessPoint next(const ChessPoint&);
/*
** 计算行尾棋子的下一个点
 */
ChessPoint newLine(const ChessPoint&);
/*
** 处理命令行参数 并返回问题的规模
*/
int tackleArgs(int argc, char const *args[]);
/*
** 检验该点能否插入
 */
bool checkBoard(const ChessPoint &curr, vector<ChessPoint> &stack);
/*
** 输出结果
 */
void print(std::ostream&, const vector<ChessPoint> &);

int main(int argc, char const *argv[]) {
    /* code */
    int size = tackleArgs(argc, argv);
    if (size <= 3) {
        cerr << "Wrong Board Size" << endl;
        return -1;
    }
    string outFile = std::to_string(size) + "Queens.txt";
    std::ofstream out(outFile);
    string output;
    std::ostringstream oss;

    vector<ChessPoint> stack;
    int record = 0;
    /*
    ** 插入初始点
     */
    stack.push_back(ChessPoint(0, 0));
    ChessPoint currPoint = newLine(*stack.cbegin());

    while (true) {
        if (checkBoard(currPoint, stack)) { //如果这个棋子能放
            stack.push_back(currPoint);
            if (stack.size() == size) { //如果栈满
                ++record;
                oss << record << "." << endl;
                print(oss, stack);  //输出
                stack.pop_back();
                while (stack.size() != 1 && stack.back().col == size - 1)
                    stack.pop_back();
                if (stack.size() == 1 && stack[0].col == size - 1)
                    break;
                currPoint = next(stack.back());
                stack.pop_back();
            }
            else //如果栈不满
                currPoint = newLine(stack.back());
        }
        else {//如果这个棋子不能放
            if (currPoint.col != size - 1) //如果这一点不是行尾
                currPoint = next(currPoint);
            else  {//如果是行尾
                while (stack.size() != 1 && stack.back().col == size - 1)
                    stack.pop_back();
                if (stack.size() == 1 && stack[0].col == size - 1)
                    break;
                currPoint = next(stack.back());
                stack.pop_back();
            }
        }

    }


    cout << outFile << " : " << record << " solutions" << endl;
    out << "----- " << outFile << " : " << record << " solutions -----\n"
        << endl;
    out << oss.str();

    return 0;
}


ChessPoint next(const ChessPoint &curr)
{
    return ChessPoint(curr.rank, curr.col + 1);
}

ChessPoint newLine(const ChessPoint &curr)
{
    return ChessPoint(curr.rank+1, 0);
}

int tackleArgs(int argc, char const *args[])
{
    if (argc != 2) {
        cerr << "Wong Usage" << endl;
        cerr << "Right: Queens [int]" << endl;
        return -1;
    }

    return std::stoi(string(args[1]));
}

bool checkBoard(const ChessPoint &curr, vector<ChessPoint> &stack)
{
    for (const auto &p : stack) {
        if (p.col == curr.col)
            return false;
        if (abs(p.col - curr.col) == abs(p.rank - curr.rank))
            return false;
    }
    return true;
}

void print(std::ostream &os, const vector<ChessPoint>& stack)
{
    for (int i = 0; i < stack.size(); ++i) {
        for (int j = 0; j < stack.size(); ++j) {
            ChessPoint temp(i, j);
            if (find(stack.begin(), stack.end(), temp) != stack.end())
                os << "1 ";
            else
                os << "0 ";
        }
        os << endl;
    }
    for (const auto &i : stack)
        os << "(" << i.rank << ", " << i.col << ")" << " ";
    os << '\n' << endl;
}
