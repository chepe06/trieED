#ifndef BSTNODE_H
#define BSTNODE_H

using namespace std;

template <typename E>
class BSTNode
{
private:
    E element;
    BSTNode<E>* left;
    BSTNode<E>* right;

public:
    BSTNode(E element, BSTNode<E>* left = nullptr, BSTNode<E>* right = nullptr) {
        this->element = element;
        this->left = left;
        this->right = right;
    }
    ~BSTNode() {}
    E getElement() {
        return element;
    }
    void setElement(E element) {
        this->element = element;
    }
    BSTNode<E>* getLeft() {
        return left;
    }
    void setLeft(BSTNode<E>* left) {
        this->left = left;
    }
    BSTNode<E>* getRight() {
        return right;
    }
    void setRight(BSTNode<E>* right) {
        this->right = right;
    }
    bool isLeaf() {
        return (left == nullptr) && (right == nullptr);
    }
    int childrenCount() {
        return (left == nullptr? 0 : 1) + (right == nullptr? 0 : 1);
    }
    BSTNode<E>* getUniqueChild() {
        return (left == nullptr? right : left);
    }
    BSTNode<E>* getSuccessorAux(BSTNode<E>* pRoot) {
        if (pRoot == NULL) {
            return NULL;
        }
        if (pRoot->left == NULL) {
            return pRoot;
        } else {
            return getSuccessorAux(pRoot->left);
        }
    }
    BSTNode<E>* getSuccessor() {
        return getSuccessorAux(right);
    }
};

#endif // BSTNODE_H
