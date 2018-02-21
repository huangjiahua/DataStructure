#ifndef _btreeFunctions_h_
#define _btreeFunctions_h_
#define MaxSize 50
#include "btree.h"
#include <cstdlib>
#include <utility>
#include <cstdio>
#include <list>
typedef char ElemType;


void CreateBTree(BTNode<ElemType> * &b, const char *str)
{
    BTNode<ElemType> * St[MaxSize], * p;
    int top = -1, k, j = 0;
    char ch;
    b = NULL;
    ch = str[j];
    while (ch != '\0') {
        switch (ch) {
            case '(': {
                ++top;
                St[top] = p;
                k = 1;
                break;
            }
            case ')': {
                --top;
                break;
            }
            case ',': {
                k = 2;
                break;
            }
            default: {
                p = (BTNode<ElemType>*)malloc(sizeof(BTNode<ElemType>));
                p->lchild = p->rchild = NULL;
                p->data = ch;
                if (b == NULL)
                    b = p;
                else {
                    if (k == 1)
                        St[top]->lchild = p;
                    else if (k == 2)
                        St[top]->rchild = p;
                }
            }
        }
        ++j;
        ch = str[j];
    }
}

void DestroyBTree(BTNode<ElemType> * &b)
{
    if (b == NULL)
        return ;
    DestroyBTree(b->lchild);
    DestroyBTree(b->rchild);
    free(b);
}

BTNode<ElemType> *FindNode(BTNode<ElemType> *b, char x)
{
    if (b == NULL)
        return NULL;
    BTNode<ElemType> *p;
    if (b->data == x)
        return b;
    if ((p = FindNode(b->lchild, x)) != NULL)
        return p;
    else
        return FindNode(b->rchild, x);
}

BTNode<ElemType> *LchildNode(BTNode<ElemType> *p)
{
    return p->lchild;
}

BTNode<ElemType> *RchildNode(BTNode<ElemType> *p)
{
    return p->rchild;
}

int BTHeight(BTNode<ElemType> *b)
{
    if (b == NULL)
        return 0;
    int l, r;
    l = BTHeight(b->lchild);
    r = BTHeight(b->rchild);
    return (l > r) ? l + 1 : r + 1;
}

void DispBTree(BTNode<ElemType> *b)
{
    if (b == NULL)
        return ;
    printf("%c", b->data);
    if (b->lchild != NULL || b->rchild != NULL) {
        printf("%c", '(');
        DispBTree(b->lchild);
        printf("%c", ',');
        DispBTree(b->rchild);
        printf("%c", ')');
    }
}

void PreOrder(BTNode<ElemType> *b, void(*f)(ElemType))
{
    if (b == NULL)
        return;
    f(b->data);
    PreOrder(b->lchild, f);
    PreOrder(b->rchild, f);
}

void InOrder(BTNode<ElemType> *b, void(*f)(ElemType))
{
    if (b == NULL)
        return;
    InOrder(b->lchild, f);
    f(b->data);
    InOrder(b->rchild, f);
}

void PostOrder(BTNode<ElemType> *b, void(*f)(ElemType))
{
    if (b == NULL)
        return;
    PostOrder(b->lchild, f);
    PostOrder(b->rchild, f);
    f(b->data);
}

namespace NonRecursive {

void PreOrder(BTNode<ElemType>* b, void(*f)(ElemType))
{
    BTNode<ElemType>* p;
    BTNode<ElemType>* st[MaxSize];
    int top = -1;
    p = b;
    while (top != -1 || p != NULL) {
        while (p != NULL) {
            f(p->data);
            st[++top] = p;
            p = p->lchild;
        }
        if (top != -1) {
            p = st[top--];
            p = p->rchild;
        }
    }
}

void InOrder(BTNode<ElemType>*b, void(*f)(ElemType))
{
    BTNode<ElemType>* p;
    BTNode<ElemType>* st[MaxSize];
    int top = -1;
    p = b;
    while (top != -1 || p != NULL) {
        while (p != NULL) {
            st[++top] = p;
            p = p->lchild;
        }
        if (top != -1) {
            p = st[top--];
            f(p->data);
            p = p->rchild;
        }
    }
}

void PostOrder(BTNode<ElemType>* b, void(*f)(ElemType))
{
    BTNode<ElemType> *p, *r;
    bool flag;
    int top = -1;
    BTNode<ElemType>* st[MaxSize];
    p = b;
    do {
        while (p != NULL) {
            st[++top] = p;
            p = p->lchild;
        }
        flag = true;
        r = NULL;
        while (flag && top != -1) {
            p = st[top];
            if (p->rchild == r) {
                f(p->data);
                --top;
                r = p;
            }
            else {
                p = p->rchild;
                flag = false;
            }
        }

    } while (top != -1);

}


}

void LevelOrder(BTNode<ElemType> *b, void(*f)(ElemType ))
{
    decltype(b) p;
    std::list<decltype(b)> queue;
    queue.push_back(b);
    while (!queue.empty()) {
        p = *queue.begin();
        f(p->data);
        queue.pop_front();
        if (p->lchild != NULL)
            queue.push_back(p->lchild);
        if (p->rchild != NULL)
            queue.push_back(p->rchild);
    }
}



#endif
