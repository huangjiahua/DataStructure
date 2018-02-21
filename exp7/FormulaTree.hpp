#ifndef _FormulaTree_hpp_
#define _FormulaTree_hpp_

#include <string>
#include <memory>
#include <cctype>
#include <vector>

struct Priority {
    int operation;
    int brace;
    Priority(int o, int b): operation(o), brace(b) { }
};

struct Node {
    std::string data;
    Priority p;
    std::shared_ptr<Node> left, right;
    Node(const std::string& s, int i, int j): data(s), p(i, j) { }
};

class FormulaTree {
    using nodePtr = std::shared_ptr<Node>;
    friend int calc(const FormulaTree& tree);
    friend int calc(const nodePtr x);
public:
    FormulaTree() = default;
    FormulaTree(const std::vector<std::string>& formula);
    void put(const std::string&);
    void put(Priority, const std::string&);
    bool empty() { return root == nullptr; }

private:
    void put(nodePtr&, const std::string&);
    void put(nodePtr&, Priority, const std::string&);

    nodePtr root;
};

FormulaTree::FormulaTree(const std::vector<std::string>& f)
{
    int braceCondition = 0;
    for (const auto& word : f) {
        if (isdigit(word[0]))
            put(word);
        else {
            switch (word[0]) {
                case '*': {
                    put(Priority(1, braceCondition), word);
                    break;
                }
                case '/': {
                    put(Priority(1, braceCondition), word);
                    break;
                }
                case '+': {
                    put(Priority(0, braceCondition), word);
                    break;
                }
                case '-': {
                    put(Priority(0, braceCondition), word);
                    break;
                }
                case '(': {
                    ++braceCondition;
                    break;
                }
                case ')': {
                    --braceCondition;
                    break;
                }
            }
        }
    }
}

bool operator>(const Priority& lhs, const Priority& rhs)
{
    if (lhs.brace != rhs.brace)
        return lhs.brace > rhs.brace;
    return lhs.operation > rhs.operation;
}

void FormulaTree::put(const std::string& num)
{
    put(root, num);
}

void FormulaTree::put(Priority priority, const std::string& opt)
{
    put(root, priority, opt);
}

void FormulaTree::put(nodePtr& x, const std::string& num)
{
    if (x == nullptr) {
        x = std::make_shared<Node>(num, 100, 100);
        return ;
    }
    put(x->right, num);
}

void FormulaTree::put(nodePtr& x, Priority p, const std::string& opt)
{
    if (!(p > x->p)) {
        nodePtr temp = x;
        x = std::make_shared<Node>(opt, p.operation, p.brace);
        x->left = temp;
        return ;
    }
    put(x->right, p, opt);
}

int calc(const typename FormulaTree::nodePtr x)
{
    if (isdigit(x->data[0]))
        return std::stoi(x->data);
    else
        switch (x->data[0]) {
            case '+': {
                return calc(x->left) + calc(x->right);
                break;
            }

            case '-': {
                return calc(x->left) - calc(x->right);
                break;
            }

            case '*': {
                return calc(x->left) * calc(x->right);
                break;
            }

            case '/': {
                return calc(x->left) / calc(x->right);
                break;
            }
        }
    return 0;
}

int calc(const FormulaTree& tree)
{
    return calc(tree.root);
}



#endif
