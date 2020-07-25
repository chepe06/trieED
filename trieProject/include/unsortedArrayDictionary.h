#ifndef UNSORTEDARRAYDICTIONARY_H
#define UNSORTEDARRAYDICTIONARY_H

#define DEFAULT_MAX_SIZE 1024
#include "Dictionary.h"
#include "kvpair.h"
#include "arrayList.h"

template <typename K, typename V>
class UnsortedArrayDictionary: public Dictionary<K, V>
{
private:
    //Memoria estática ArrayList<KVPair<K, V> > pairs;
    ArrayList<KVPair<K, V> > *pairs; //Se pone el puntero para memoria dinámica

    //Se encargan de verificar si existe o no existe (Se hacen métodos porque se van a usar varias veces)
    void checkNotExisting(K key) {
        if(contains(key)){
            throw runtime_error("Duplicated key");
        }
    }
    void checkExisting(K key){
        if(!contains(key)){
            throw runtime_error("Key not found");
        }
    }

public:
    //Memoria estática UnsortedArrayDictionary(int max = DEFAULT_MAX_SIZE) : pairs(max) {} //Constructor
    UnsortedArrayDictionary(int max = DEFAULT_MAX_SIZE) {
        pairs = new ArrayList<KVPair<K, V> >(max);
    }

    ~UnsortedArrayDictionary(){ //Destructor
        delete pairs;
    }

    void insert(K key, V value){
        checkNotExisting(key);
        KVPair<K, V> p(key, value);
        pairs->append(p);
    }

    V remove(K key){
        checkExisting(key);
        KVPair<K, V> p = pairs->remove();
        return p.getValue();
        //return pairs->getElement().getValue(); //train wrecks: Evitar esto ya que es más difícil identificar errores
    }

    V getValue(K key){
        checkExisting(key);
        KVPair<K, V> p = pairs->getElement();
        return p.getValue();
    }

    void setValue(K key, V value){
        checkExisting(key);
        KVPair<K, V> p(key, value);
        pairs->remove();
        pairs->append(p);
    }

    void clear(){
        pairs->clear();
    }

    bool contains(K key){
        KVPair<K, V> p(key);
        for(pairs->goToStart(); !pairs->atEnd(); pairs->next()){
            if(p == pairs -> getElement()){
                return true;
            }
        }
        return false; //Si no lo encontró
    }

    List<K> *getKeys(){
        List<K> *keys = new ArrayList<K> (); //Se puede usar una linked list normal
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()){
            KVPair<K, V> p = pairs->getElement();
            keys->append(p.getKey());
        }
        return keys;
    }

    List<V> *getValues(){
        List<V> *values = new ArrayList<V> (); //Se puede usar una linked list normal
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()){
            KVPair<K, V> p = pairs->getElement();
            values->append(p.getValue());
        }
        return values;
    }

    int getSize(){
        return pairs->getSize();
    }

    void print(){
        List<int> *keys = getKeys();
        List<string> *values = getValues();
        cout << "Diccionario\n";
        values->goToStart();
        for (keys->goToStart(); !keys->atEnd(); keys->next()){
            cout << keys->getElement() << " " << values->getElement() << "\n";
            values->next();
        }
    }

};

#endif // UNSORTEDARRAYDICTIONARY_H
