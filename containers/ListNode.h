#pragma once

#include "../common/list_err.h"

template <typename T>
class ListNode {
public:
    ListNode<T>* prev;
    ListNode<T>* next;
    ListNode<T>* head_node; // In our design, this points to the sentinel node
    T val;                 // The actual data in a node

    // Constructor
    ListNode() {
        prev = next = head_node = this; // Point to self
    }

    ListNode<T>* predecessor() {
        // Cannot go before the sentinel's next node (the first element)
        if (prev == head_node) return nullptr;
        return prev;
    }

    ListNode<T>* successor() {
        // Cannot go past the sentinel node
        if (next == head_node) return nullptr;
        return next;
    }

    bool singleton() {
        return (prev == this);
    }

    void insert_before(ListNode<T>* new_node) {
        if (!new_node->singleton())
            throw list_err("attempt to insert node already on list");
        prev->next = new_node;
        new_node->prev = prev;
        new_node->next = this;
        prev = new_node;
        new_node->head_node = head_node;
    }

    void remove() {
        if (singleton())
            throw list_err("attempt to remove node not currently on list");
        prev->next = next;
        next->prev = prev;
        prev = next = head_node = this; // Point to self
    }

    ~ListNode() {
        if (!singleton())
            remove(); // Automatically remove from list if destroyed
    }
};
