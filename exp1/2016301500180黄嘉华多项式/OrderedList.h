#ifndef _OrderedList_
#define _OrderedList_
#include <memory>
#include <iostream>

template <typename Item>
struct Node {
    Item item;
    std::shared_ptr<Node<Item>> next;
    Node(const Item& i): item(i) { }
};

template <typename T>
class OrderedList {
public:
    OrderedList() = default;
    ~OrderedList() = default;
    T &operator[](std::size_t i)
    {
        auto curr = begin();
        for (int j = 0; j < i; ++j)
            curr = curr->next;
        return curr->item;
    }
    bool isEmpty() const { return first == nullptr; }
    std::shared_ptr<Node<T>> begin() { return first; }
    std::shared_ptr<Node<T>> cbegin() const { return first; }
    std::shared_ptr<Node<T>> end() { return nullptr; }
    void add(const T &item);
    std::size_t size() { return sz; }
protected:
    std::size_t sz = 0;
    std::shared_ptr<Node<T>> first;
};

template <typename T>
void OrderedList<T>::add(const T &item)
{
    if (first == nullptr || item < first->item) {
        auto oldfirst = first;
        first = std::make_shared<Node<T>>(item);
        first->next = oldfirst;
        ++sz;
        return ;
    }
    auto curr = first->next;
    auto last = first;
    while (curr != nullptr && curr->item < item) {
        last = curr;
        curr = curr->next;
    }
    last->next = std::make_shared<Node<T>>(item);
    last->next->next = curr;
    ++sz;
}


#endif
