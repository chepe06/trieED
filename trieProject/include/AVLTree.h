#ifndef AVLTREE_H
#define AVLTREE_H

#include "BSTNode.h"
#include <stdexcept>
#include <cmath>
#include "DLinkedList.h"

using namespace std;

template <typename E>
class AVLTree {
private:
    BSTNode<E>* root;

    void inOrderAux(BSTNode<E>* pRoot) {
        if (pRoot == NULL) {
            return;
        }
        inOrderAux(pRoot->getLeft());
        cout << pRoot->getElement() << " ";
        inOrderAux(pRoot->getRight());
    }
    void preOrderAux(BSTNode<E>* pRoot) {
        if (pRoot == NULL) {
            return;
        }
        cout << pRoot->getElement() << " ";
        preOrderAux(pRoot->getLeft());
        preOrderAux(pRoot->getRight());
    }
    void printAux(BSTNode<E>* pRoot, int depth) {
        if (pRoot == NULL) {
            return;
        }
        for (int i = 0; i < depth; i++) {
            cout << "  ";
        }
        cout << "+-" << pRoot->getElement() << endl;
        printAux(pRoot->getLeft(), depth + 1);
        printAux(pRoot->getRight(), depth + 1);
    }
    BSTNode<E>* insertAux(BSTNode<E>* pRoot, E element) throw(runtime_error) {
        if (pRoot == NULL) {
            return new BSTNode<E>(element);
        }
        if (element < pRoot->getElement()) {
            pRoot->setLeft(insertAux(pRoot->getLeft(), element));
            return rebalanceLeft(pRoot);
        } else {
            if (element > pRoot->getElement()) {
                pRoot->setRight(insertAux(pRoot->getRight(), element));
                return rebalanceRight(pRoot);
            } else {
                throw runtime_error("Key already exists. Duplicate values not allowed.");
            }
        }
    }
    BSTNode<E>* rebalanceLeft(BSTNode<E>* pRoot) {
        int leftHeight = height(pRoot->getLeft());
        int rightHeight = height(pRoot->getRight());
        if(leftHeight - rightHeight > 1){
            int leftLeftHeight = height(pRoot->getLeft()->getLeft());
            int leftRightHeight = height(pRoot->getLeft()->getRight());
            if(leftLeftHeight >= leftRightHeight){
                return rotateRight(pRoot);
            } else {
                pRoot->setLeft(rotateLeft(pRoot->getLeft()));
                return rotateRight(pRoot);
            }
        }
        return pRoot;
    }
    BSTNode<E>* rebalanceRight(BSTNode<E>* pRoot) {
        int leftHeight = height(pRoot->getLeft());
        int rightHeight = height(pRoot->getRight());
        if(rightHeight - leftHeight > 1){
            int rightRightHeight = height(pRoot->getRight()->getRight());
            int rightLeftHeight = height(pRoot->getRight()->getLeft());
            if(rightRightHeight >= rightLeftHeight){
                return rotateLeft(pRoot);
            } else {
                pRoot->setRight(rotateRight(pRoot->getRight()));
                return rotateLeft(pRoot);
            }
        }
        return pRoot;
    }
    E findAux(BSTNode<E>* pRoot, E element) throw (runtime_error) {
        if (pRoot == NULL) {
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
        if (pRoot == NULL) {
            throw runtime_error("Key not found.");
        }
        if (element < pRoot->getElement()) {
            pRoot->setLeft(removeAux(pRoot->getLeft(), element));
            //if (pRoot->getLeft() != NULL) { // probar sin esto
                pRoot = rebalanceRight(pRoot);
            //}
            return pRoot;
        }
        if (element > pRoot->getElement()) {
            pRoot->setRight(removeAux(pRoot->getRight(), element));
            //if (pRoot->getRight() != NULL) { // probar sin esto
                pRoot = rebalanceLeft(pRoot);
            //}
            return pRoot;
        } else {
            if (pRoot->isLeaf()) {
                delete pRoot;
                return NULL;
            }
            if (pRoot->childrenCount() == 1) {
                BSTNode<E>* temp = pRoot->getUniqueChild();
                delete pRoot;
                return temp;
            } else {
                BSTNode<E>* successor = pRoot->getSuccessor();
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
    BSTNode<E>* rotateRight(BSTNode<E>* pRoot) throw(runtime_error) {
        if(pRoot == nullptr) throw runtime_error("Can't rotate right on null");
        if(pRoot->getLeft() == nullptr) throw runtime_error("Can't rotate right with null left child");
        BSTNode<E>* newRoot = pRoot->getLeft();
        pRoot->setLeft(newRoot->getRight());
        newRoot->setRight(pRoot);
        return newRoot;
        //return pRoot;
    }
    BSTNode<E>* rotateLeft(BSTNode<E>* pRoot) throw(runtime_error) {
        if(pRoot == nullptr) throw runtime_error("Can't rotate left on null");
        if(pRoot->getRight() == nullptr) throw runtime_error("Can't rotate left with null right child");
        BSTNode<E>* newRoot = pRoot->getRight();
        pRoot->setRight(newRoot->getLeft());
        newRoot->setLeft(pRoot);
        return newRoot;
        //return pRoot;
    }
    int height(BSTNode<E>* pRoot) {
        if (pRoot == NULL) {
            return 0;
        }
        if (pRoot->isLeaf()) {
            return 1;
        }
        int leftHeight = height(pRoot->getLeft());
        int rightHeight = height(pRoot->getRight());
        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        } else {
            return rightHeight + 1;
        }
    }
    BSTNode<E>* clearAux(BSTNode<E>* pRoot) {
        if (pRoot == NULL) {
            return NULL;
        }
        if (pRoot->isLeaf()) {
            delete pRoot;
            return NULL;
        }
        pRoot->setLeft(clearAux(pRoot->getLeft()));
        pRoot->setRight(clearAux(pRoot->getRight()));
        delete pRoot;
        return NULL;
    }
    void getElementsAux(BSTNode<E> *pRoot, List<E> *elements) {
        if (pRoot == nullptr) return;
        getElementsAux(pRoot->getLeft(), elements);
        elements->append(pRoot->getElement());
        getElementsAux(pRoot->getRight(), elements);
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
    int getSizeAux(BSTNode<E>* pRoot) {
        if (pRoot == nullptr) return 0;
        return 1 + getSizeAux(pRoot->getLeft())
                 + getSizeAux(pRoot->getRight());
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

public:
    AVLTree() {
        root = NULL;
    }
    ~AVLTree() {
        root = clearAux(root);
    }
    void insert(E element) {
        root = insertAux(root, element);
    }
    void inOrder() {
        inOrderAux(root);
        cout << endl;
    }
    void preOrder() {
        preOrderAux(root);
        cout << endl;
    }
    E find(E element) {
        return findAux(root, element);
    }
    E remove(E element) {
        E result = find(element);
        root = removeAux(root, element);
        return result;
    }
    void print() {
        printAux(root, 0);
    }
    void clear() {
        root = clearAux(root);
    }
    bool contains(E element){
        return containsAux(root, element);
    }
    List<E>* getElements() {
        List<E> *elements = new DLinkedList<E>();
        getElementsAux(root, elements);
        return elements;
    }
    int getSize() {
        return getSizeAux(root);
    }

};

#endif // AVLTREE_H
