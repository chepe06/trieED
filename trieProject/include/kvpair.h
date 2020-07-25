#ifndef KVPAIR_H
#define KVPAIR_H

template <typename K, typename V>
class KVPair
{
    private:
        K key;
        V value;

    public:
        KVPair() {}

        KVPair(K key){
            this->key = key;
        }

        KVPair(K key, V value){
            this->key = key;
            this->value = value;
        }

        K getKey(){
            return key;
        }

        void setKey(K key){
            this->key = key;
        }

        V getValue(){
            return value;
        }

        void setValue(V value){
            this->value = value;
        }

        void operator= (const KVPair &other){ //Sobrescribir operador de asignación =
            key = other.key;
            value = other.value;
        }

        bool operator== (const KVPair &other){ //Sobrescribir operador de igualdad ==
            return key == other.key;
        }

        bool operator!= (const KVPair &other){ //Sobrescribir operador de diferencia !=
            return key != other.key;
        }

        bool operator< (const KVPair &other){ //Sobrescribir operador de menor que <
            return key < other.key;
        }

        bool operator<= (const KVPair &other){ //Sobrescribir operador de menor o igual <=
            return key <= other.key;
        }

        bool operator> (const KVPair &other){ //Sobrescribir operador de mayor que >
            return key > other.key;
        }

        bool operator>= (const KVPair &other){ //Sobrescribir operador de mayor o igual >=
            return key >= other.key;
        }
};

#endif // KVPAIR_H
