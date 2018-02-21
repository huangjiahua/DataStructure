#ifndef _btree_h_
#define _btree_h_

template <typename T>
struct BTNode
{
    T data;
    BTNode *lchild;
    BTNode *rchild;
};

#endif
