#ifndef SORTEDARRAYDICTIONARY_H
#define SORTEDARRAYDICTIONARY_H

#include <iostream>
#include "sortedarraylist.h"
#include "Dictionary.h"
#include "KVPair.h"

//Clase creada por David Pastor
//Se encarga de crear un diccionario usando un sortedArrayList para almacenar los pares llave, valor de tipo K, V.

using namespace std;

template <typename K, typename V>

class SortedArrayDictionary : public Dictionary<K, V>{
private:
    SortedArrayList<KVPair<K, V> > * ordenada;
    int size;

public:
    SortedArrayDictionary() {
        ordenada = new SortedArrayList<KVPair<K, V> >();
        size = 0;
    }
    ~SortedArrayDictionary() {
        clear();
        delete ordenada;
    }
    void insert(K key, V value){
        ordenada->insert(KVPair<K, V>(key, value));
        size++;
    }
    V remove(K key){
        ordenada->goToPos(ordenada->indexOf(KVPair<K, V>(key)));
        KVPair<K, V> result = ordenada->remove();
        size--;
        return result.getValue();
    }
    V getValue(K key){
        ordenada->goToPos(ordenada->indexOf(KVPair<K, V>(key)));
        return ordenada->getElement().getValue();
    }
    void setValue(K key, V value){
        ordenada->goToPos(ordenada->indexOf(KVPair<K, V>(key)));
        KVPair<K, V> * result = new KVPair<K, V>(key, value);
        ordenada->remove();
        ordenada->insert(*result);
        delete result;
    }
    void clear(){
        ordenada->clear();
        size = 0;
    }
    bool contains(K key){
        return ordenada->contains(KVPair<K, V>(key));
    }
    List<K> * getKeys(){
        List<K> * llaves = new DLinkedList<K>();
        for (ordenada->goToStart(); !ordenada->atEnd(); ordenada->next()){
            llaves->append(ordenada->getElement().getKey());
        }
        return llaves;
    }
    List<V> * getValues(){
        List<V> * valores = new DLinkedList<V>();
        for (ordenada->goToStart(); !ordenada->atEnd(); ordenada->next()){
            valores->append(ordenada->getElement().getValue());
        }
        return valores;
    }
    int getSize(){
        return size;
    }
    KVPair<K, V> getPair(int index){
        ordenada->goToPos(index);
        return ordenada->getElement();
    }
};

#endif // SORTEDARRAYDICTIONARY_H
