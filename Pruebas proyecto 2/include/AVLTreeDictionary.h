#ifndef AVLTREEDICTIONARY_H
#define AVLTREEDICTIONARY_H

#include <iostream>
#include "AVLTree.h"
#include "Dictionary.h"
#include "KVPair.h"

//Clase creada por David Pastor
//Se encarga de crear un diccionario utilizando un arbol AVL para almacenar los pares llave, valor de tipo K, V.

using namespace std;

template <typename K, typename V>

class AVLTreeDictionary : public Dictionary<K, V>{
private:
    AVLTree<KVPair<K, V> > * Arbol;
    int size;

public:
    AVLTreeDictionary() {
        Arbol = new AVLTree<KVPair<K, V> >();
        size = 0;
    }
    ~AVLTreeDictionary() {
        clear();
        delete Arbol;
    }
    void insert(K key, V value){
        Arbol->insert(KVPair<K, V>(key, value));
        size++;
    }
    V remove(K key){
        KVPair<K, V> result = Arbol->remove(KVPair<K, V>(key));
        size--;
        return result.getValue();
    }
    V getValue(K key){
        return Arbol->find(KVPair<K, V>(key)).getValue();
    }
    void setValue(K key, V value){
        KVPair<K, V> * result = new KVPair<K, V>(key, value);
        Arbol->remove(*result);
        Arbol->insert(*result);
        delete result;
    }
    void clear(){
        Arbol->clear();
        size = 0;
    }
    bool contains(K key){
        return Arbol->contains(KVPair<K, V>(key));
    }
    List<K> * getKeys(){
        List<K> * llaves = new DLinkedList<K>();
        List<KVPair<K, V> > * pares = Arbol->getElements();
        for (pares->goToStart(); !pares->atEnd(); pares->next()){
            llaves->insert(pares->getElement().getKey());
        }
        delete pares;
        return llaves;
    }
    List<V> * getValues(){
        List<V> * valores = new DLinkedList<V>();
        List<KVPair<K, V> > * pares = Arbol->getElements();
        for (pares->goToStart(); !pares->atEnd(); pares->next()){
            valores->insert(pares->getElement().getValue());
        }
        delete pares;
        return valores;
    }
    int getSize(){
        return size;
    }
};

#endif // AVLTREEDICTIONARY_H
