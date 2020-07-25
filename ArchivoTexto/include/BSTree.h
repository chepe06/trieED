#ifndef BSTREE_H
#define BSTREE_H

#include "BSTNode.h"
#include <stdexcept>
#include "DLinkedList.h"

using namespace std;

template <typename E>
class BSTree {
private:
    BSTNode<E>* root;

    BSTNode<E>* insertAux(BSTNode<E>* pRoot, E element) {
        if (pRoot == nullptr) return new BSTNode<E>(element);
        if (element < pRoot->getElement()) {
            pRoot->setLeft(insertAux(pRoot->getLeft(), element));
            return pRoot;
        } else {
            pRoot->setRight(insertAux(pRoot->getRight(), element));
            return pRoot;
        }
    }

    E findAux(BSTNode<E>* pRoot, E element) throw (runtime_error) {
        if (pRoot == nullptr) {
            throw runtime_error("Key not found.");
        }
        if (element == pRoot->getElement()) {
            return pRoot->getElement();
        }
        if (element < pRoot->getElement()) {
            return findAux(pRoot->getLeft(), element);
        } else {
            return findAux(pRoot->getRight(), element);
        }
    }

    BSTNode<E>* removeAux(BSTNode<E>* pRoot, E element) throw (runtime_error) {
        if (pRoot == nullptr) throw runtime_error("Key not found.");
        if (element < pRoot->getElement()) {
            pRoot->setLeft(removeAux(pRoot->getLeft(), element));
            return pRoot;
        }
        if (element > pRoot->getElement()) {
            pRoot->setRight(removeAux(pRoot->getRight(), element));
            return pRoot;
        } else {
            if (pRoot->isLeaf()) {
                delete pRoot;
                return nullptr;
            }
            if (pRoot->childrenCount() == 1) {
                BSTNode<E>* temp = pRoot->getUniqueChild();
                delete pRoot;
                return temp;
            } else {
                BSTNode<E>* successor = getSuccessor(pRoot);
                swap(pRoot, successor);
                pRoot->setRight(removeAux(pRoot->getRight(), element));
                return pRoot;
            }
        }
    }

    void swap(BSTNode<E>* node1, BSTNode<E>* node2) {
        E temp = node1->getElement();
        node1->setElement(node2->getElement());
        node2->setElement(temp);
    }

    bool containsAux(BSTNode<E> *pRoot, E element) {
        if (pRoot == nullptr) {
            return false;
        }
        if (element == pRoot->getElement()) {
            return true;
        }
        if (element < pRoot->getElement()) {
            return containsAux(pRoot->getLeft(), element);
        } else {
            return containsAux(pRoot->getRight(), element);
        }
    }

    void clearAux(BSTNode<E> *pRoot) {
        if (pRoot == nullptr) return;
        clearAux(pRoot->getLeft());
        clearAux(pRoot->getRight());
        delete pRoot;
    }

    void printAux(BSTNode<E>* pRoot, int depth) {
        if (pRoot == nullptr) {
            return;
        }
        for (int i = 0; i < depth; i++) {
            cout << "  ";
        }
        cout << "+-" << pRoot->getElement() << endl;
        printAux(pRoot->getLeft(), depth + 1);
        printAux(pRoot->getRight(), depth + 1);
    }

    void getElementsAux(BSTNode<E> *pRoot, List<E> *elements) {
        if (pRoot == nullptr) return;
        getElementsAux(pRoot->getLeft(), elements);
        elements->append(pRoot->getElement());
        getElementsAux(pRoot->getRight(), elements);
    }

    int getSizeAux(BSTNode<E>* pRoot) {
        if (pRoot == nullptr) return 0;
        return 1 + getSizeAux(pRoot->getLeft())
                 + getSizeAux(pRoot->getRight());
    }

    BSTNode<E>* getSuccessorAux(BSTNode<E>* pRoot) {
        if (pRoot == nullptr) {
            return nullptr;
        }
        if (pRoot->getLeft() == nullptr) {
            return pRoot;
        } else {
            return getSuccessorAux(pRoot->getLeft());
        }
    }

    BSTNode<E>* getSuccessor(BSTNode<E>* pRoot) {
        return getSuccessorAux(pRoot->getRight());
    }

public:
    BSTree() {
        root = nullptr;
    }
    ~BSTree() {
        clear();
    }
    void insert(E element) {
        root = insertAux(root, element);
    }
    E find(E element) {
        return findAux(root, element);
    }
    E remove(E element) {
        E result = find(element);
        root = removeAux(root, element);
        return result;
    }
    bool contains(E element) {
        return containsAux(root, element);
    }
    void clear() {
        clearAux(root);
        root = nullptr;
    }
    List<E>* getElements() {
        List<E> *elements = new DLinkedList<E>();
        getElementsAux(root, elements);
        return elements;
    }
    int getSize() {
        return getSizeAux(root);
    }
    void print() {
        printAux(root, 0);
    }
};

#endif // BSTREE_H
