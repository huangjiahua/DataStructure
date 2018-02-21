#ifndef _Queue_h_
#define _Queue_h_

#include <memory>
#include "Node.h"

namespace ADT {
    using std::shared_ptr;
    using std::make_shared;
    template <typename Item> struct Node;

    template <typename T>
    class Queue {
    public:
        Queue() = default;
        bool isEmpty() const { return first == nullptr; }
        void enQueue(T item);
        T deQueue();
        const T& first_item() { return first->item; }
        std::size_t size() { return N; }
    private:
        shared_ptr<Node<T>> first, last;
        int N = 0;
    };

    template <typename T>
    void Queue<T>::enQueue(T item)
    {
        shared_ptr<Node<T>> oldlast = last;
        last = make_shared<Node<T>>(item);
        if (isEmpty())
            first = last;
        else
            oldlast->next = last;
        ++N;
    }

    template <typename T>
    T Queue<T>::deQueue()
    {
        T ret = first->item;
        first = first->next;
        if (isEmpty())
            last = nullptr;
        --N;
        return ret;
    }

}

#endif
