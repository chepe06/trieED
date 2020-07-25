#ifndef DNODE_H
#define DNODE_H

template <typename E>
class DNode {
public:
    E element;
    DNode<E>* next;
    DNode<E>* previous;

    DNode(E element, DNode<E>* next = nullptr, DNode<E>* previous = nullptr) {
        this->element = element;
        this->next = next;
        this->previous = previous;
    }

    DNode(DNode<E>* next = nullptr, DNode<E>* previous = nullptr) {
        this->next = next;
        this->previous = previous;
    }
};

#endif // DNODE_H
