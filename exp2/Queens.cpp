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
#include "Stack.h"

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
bool checkBoard(const ChessPoint &curr, const ADT::Stack<ChessPoint>& stack);
/*
** 输出结果
 */
void print(std::ostream&, ADT::Stack<ChessPoint> stack);

int main(int argc, char const *argv[]) {
    /* code */
    int size = tackleArgs(argc, argv);
    if (size <= 3) {
        cerr << "Wrong Board Size" << endl;
        return -1;
    }
    string outFile = std::to_string(size) + "Queens";
    string output;
    std::ostringstream oss;

    ADT::Stack<ChessPoint> st;
    int record = 0;
    /*
    ** 插入初始点
     */
    st.push(ChessPoint(0, 0));
    ChessPoint currPoint = newLine(st.top());

    while (true) {
        if (checkBoard(currPoint, st)) { //如果这个棋子能放
            st.push(currPoint);
            if (st.size() == size/* st.size() == size */) { //如果栈满
                ++record;
                oss << record << "." << endl;
                print(oss, st);  //输出
                st.pop();
                while (st.size() != 1 && st.top().col == size - 1)
                    st.pop();
                if (st.size() == 1 && st.top().col == size - 1)
                    break;
                currPoint = next(*st.begin());
                st.pop();
            }
            else //如果栈不满
                currPoint = newLine(st.top());
        }
        else {//如果这个棋子不能放
            if (currPoint.col != size - 1) //如果这一点不是行尾
                currPoint = next(currPoint);
            else  {//如果是行尾
                while (st.size() != 1 && st.top().col == size - 1)
                    st.pop();
                if (st.size() == 1 && st.top().col == size - 1)
                    break;
                currPoint = next(st.top());
                st.pop();
            }
        }

    }


    cout << "----- " << outFile << " : " << record << " solutions -----\n"
        << endl;
    cout << oss.str();
    cout << "----- " << outFile << " : " << record << " solutions -----\n"
         << endl;

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

bool checkBoard(const ChessPoint &curr, const ADT::Stack<ChessPoint> &stack)
{
    for (const auto &p : stack) {
        if (p.col == curr.col)
            return false;
        if (abs(p.col - curr.col) == abs(p.rank - curr.rank))
            return false;
    }
    return true;
}



void print(std::ostream &os, ADT::Stack<ChessPoint> st)
{
    ADT::Stack<ChessPoint> t;
    while (!st.isEmpty())
        t.push(st.pop());
    ADT::Stack<ChessPoint>::iterator iter = t.begin();
    for (int i = 0; i < t.size(); ++i) {
        for (int j = 0; j < t.size(); ++j) {
            ChessPoint temp(i, j);
            if (iter != t.end() && temp == *iter) {
                os << "1 ";
                ++iter;
            }
            else
                os << "0 ";
        }
        os << endl;
    }
    for (const auto &i : t)
        os << "(" << i.rank << ", " << i.col << ")" << " ";
    os << "\n" << endl;

}
