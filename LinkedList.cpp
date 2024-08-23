#include "LinkedList.h"

void LinkedList::add(int value, LinkedList* head) {
    if (head->next == nullptr) {
        LinkedList* newNode = new LinkedList(value);
        head->next = newNode;
        newNode->previous = head;
    } else {
        add(value, head->next);
    }
}

void LinkedList::remove(int value, LinkedList*& head) {
    LinkedList* current = head;
    while (current != nullptr) {
        if (current->value == value) {
            if (current->previous != nullptr) {
                current->previous->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != nullptr) {
                current->next->previous = current->previous;
            }
            delete current;
            return;
        }
        current = current->next;
    }
}
