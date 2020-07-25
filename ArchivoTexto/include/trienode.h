#ifndef TRIENODE_H
#define TRIENODE_H

#include "bstreedictionary.h"
#include "arrayList.h"

class TrieNode {
private:
    bool isFinal;
    int prefixCount;
    BSTreeDictionary<char, TrieNode*> children;
    ArrayList<int> indices;// = new ArrayList<int>();

public:
    TrieNode() : children() {
        isFinal = false;
        prefixCount = 0;
//        indices = new ArrayList<int>();
    }
    ~TrieNode() {}
    bool getIsFinal() {
        return isFinal;
    }
    void setIsFinal(bool isFinal) {
        this->isFinal = isFinal;
    }
    int getPrefixCount() {
        return prefixCount;
    }
    void setPrefixCount(int prefixCount) {
        this->prefixCount = prefixCount;
    }
    void increaseCount() {
        prefixCount++;
    }
    void decreaseCount() {
        prefixCount--;
    }
    bool contains(char c) {
        return children.contains(c);
    }
    void add(char c, TrieNode *newNode) {
        children.insert(c, newNode);
    }
    void remove(char c) {
        children.remove(c);
    }
    TrieNode* getChild(char c) {
        return children.getValue(c);
    }
    List<char>* getChildren() {
        return children.getKeys();
    }
    List<TrieNode*>* getChildrenPointers() {
        return children.getValues();
    }
    void setIndex(int index){
        indices.append(index);
    }
    void getIndex(){
        indices.print();
    }

};

#endif // TRIENODE_H