#ifndef TRIENODE_H
#define TRIENODE_H

#include "AVLTreeDictionary.h"
#include "BSTreeDictionary.h"
#include "arrayList.h"

class TrieNode{
protected:
    bool isFinal;
    int prefixCount;
    AVLTreeDictionary<char, TrieNode*> children;
    ArrayList<int> *indices = nullptr;
public:
    TrieNode() : children() {
        isFinal = false;
        prefixCount = 0;
    }
    ~TrieNode() {}
    bool getIsFinal() {
        return isFinal;
    }
    void setIsFinal(bool isFinal) {
        this->isFinal = isFinal;
        if(indices == nullptr){
            indices = new ArrayList<int>(1024);
        }
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
        indices->append(index);
    }
    void printIndex(){
        indices->print();
    }
    ArrayList<int> *getIndex(){ //Retorna la lista de indices sin repetir números
        ArrayList<int> *lista = new ArrayList<int>();
        for(indices->goToStart(); !indices->atEnd(); indices->next()){
            if(!lista->contains(indices->getElement())){
                lista->append(indices->getElement());
            }
        }
        return lista;
    }
    int getIndexSize(){
       return indices->getSize();
    }

};

#endif // TRIENODE_H
