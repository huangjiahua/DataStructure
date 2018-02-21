#include <iostream>
#include <cstring>
#include <cstdio>
#include "btreeFunctions.h"
#include "btree.h"
using namespace std;

void print(char ch)
{
    std::cout << ch << " ";
}

int main(int argc, char const *argv[])
{
    char str[MaxSize];

    scanf("%s", str);
    BTNode<char>* root;
    CreateBTree(root, str);
    DispBTree(root);
    printf("%c", '\n');
    printf("%d\n", BTHeight(root));
    cout << endl;
    cout << endl;
    NonRecursive::PreOrder(root, print);
    cout << endl;
    PreOrder(root, print);
    cout << endl;
    cout << endl;
    NonRecursive::InOrder(root, print);
    cout << endl;
    InOrder(root, print);
    cout << endl;
    cout << endl;
    NonRecursive::PostOrder(root, [](char ch) { printf("%c ", ch); });
    cout << endl;
    PostOrder(root, [](char ch) { printf("%c ", ch); });
    cout << '\n' << endl;
    LevelOrder(root, print);
    cout << endl;
    DestroyBTree(root);

    return 0;
}
