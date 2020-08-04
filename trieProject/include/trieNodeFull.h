#ifndef TRIENODEFULL_H
#define TRIENODEFULL_H

#include "bstreedictionary.h"
#include "arrayList.h"

class TrieNodeFull : public TrieNode{
private:
    ArrayList<int> *indices = new ArrayList<int>(20000);

public:
    TrieNodeFull() : TrieNode() {
    }
    ~TrieNodeFull() {}

    void setIndex(int index){
        cout << "Hola SetIndex";
        indices->append(index);//SE CAE AQUÍ
        cout << "Adiós SetIndex";
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

#endif // TRIENODEFULL_H
