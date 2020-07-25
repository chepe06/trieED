#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <stdexcept>
#include "DNode.h"

using std::runtime_error;

template <typename E>
class DLinkedList : public List<E> {
private:
    DNode<E>* head;
    DNode<E>* tail;
    DNode<E>* current;
    int size;

    void init() {
        head = new DNode<E>();
        tail = new DNode<E>();
        head->next = tail;
        tail->previous = head;
        current = head;
        size = 0;
    }
public:
    DLinkedList() {
        init();
    }
    ~DLinkedList() {
        clear();
        delete head;
        delete tail;
    }
    void insert(E element) {
        current->next->previous = new DNode<E>(element, current->next, current);
        current->next = current->next->previous;
        size++;
    }
    void append(E element) {
        tail->previous->next = new DNode<E>(element, tail, tail->previous);
        tail->previous = tail->previous->next;
        size++;
    }
    E remove() throw(runtime_error) {
        if (current->next == tail) {
            throw runtime_error("No element to remove.");
        }
        E res = current->next->element;
        DNode<E>* temp = current->next;
        current->next = current->next->next;
        current->next->previous = current;
        delete temp;
        size--;
        return res;
    }
    void clear() {
        while (head != nullptr) {
            current = head;
            head = head->next;
            delete current;
        }
        init();
    }
    E getElement() throw(runtime_error) {
        if (current->next == tail) {
            throw runtime_error("No element to get.");
        }
        return current->next->element;
    }
    void goToStart() {
        current = head;
    }
    void goToEnd() {
        current = tail->previous;
    }
    void goToPos(int newPos) throw(runtime_error) {
        if (newPos < 0 || newPos >= size) {
            throw runtime_error("Index out of bounds.");
        }
        current = head;
        for (int i = 0; i < newPos; i++) {
            current = current->next;
        }
    }
    void next() {
        if (current != tail->previous) {
            current = current->next;
        }
    }
    bool atEnd() {
        return current->next == tail;
    }
    void previous() {
        if (current != head) {
            current = current->previous;
        }
    }
    bool atStart() {
        return current == head;
    }
    int getPos() {
        int pos = 0;
        DNode<E>* temp = head;
        while (temp != current) {
            temp = temp->next;
            pos++;
        }
        return pos;
    }
    int getSize() {
        return size;
    }
    bool contains(E element) {
        for (goToStart(); !atEnd(); next()) {
            if (getElement() == element) {
                return true;
            }
        }
        return false;
    }
    int indexOf(E element) {
        if (contains(element)) {
            return getPos();
        }
        return -1;
    }
    void extend(List<E> &L) {
        int oldPos = L.getPos();
        L.goToStart();
        while (!L.atEnd()) {
            append(L.getElement());
        }
        L.goToPos(oldPos);
    }
};

#endif // DLINKEDLIST_H
