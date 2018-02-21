#ifndef _Node_h_
#define _Node_h_
#include <memory>

namespace ADT {
    template <typename Item>
    struct Node {
        Node(Item i): item(i)
        {
            next = nullptr;
        }
        Item item;
        std::shared_ptr<Node<Item>> next;
    };
}

#endif
