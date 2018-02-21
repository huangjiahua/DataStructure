#ifndef _Stack_h_
#define _Stack_h_

#include <memory>
#include "Node.h"

namespace ADT {
    using std::shared_ptr;
    using std::make_shared;

    template <typename T>
    class Stack {
        class st_iterator;
    public:
        Stack() = default;
        bool isEmpty() const { return first == nullptr; }
        using iterator = st_iterator;

        void push(T item)
        {
            auto oldfirst = first;
            first = make_shared<Node<T>>(item);
            first->next = oldfirst;
            ++sz;
        }

        T pop()
        {
            T ret = first->item;
            first = first->next;
            --sz;
            return ret;
        }

        const T &top() const
        {
            return first->item;
        }

        iterator begin() { return iterator(first); }
        iterator end() { return iterator(nullptr); }
        iterator begin() const { return iterator(first); }
        iterator end() const { return iterator(nullptr); }
        int size() const { return sz; }
    private:
        shared_ptr<Node<T>> first;
        int sz = 0;
        class st_iterator {
        friend class Stack;
        public:
            T& operator*() { return curr->item; }
            st_iterator& operator++()
            {
                curr = curr->next;
                return *this;
            }
            st_iterator operator++(int)
            {
                auto ret = *this;
                curr = curr->next;
                return ret;
            }
            bool operator==(const st_iterator& rhs)
            {
                return curr == rhs.curr;
            }
            bool operator!=(const st_iterator& rhs)
            {
                return !(*this == rhs);
            }
        private:
            shared_ptr<Node<T>> curr;
            st_iterator(shared_ptr<Node<T>> p): curr(p) { }
        };
    };


}

#endif
