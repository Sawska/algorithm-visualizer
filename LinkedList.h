#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class LinkedList {
public:
    int value;
    LinkedList* previous;
    LinkedList* next;

    LinkedList(int val) : value(val), previous(nullptr), next(nullptr) {}

    void add(int value, LinkedList* head);
    void remove(int value, LinkedList* head);
};

#endif // LINKEDLIST_H
