#ifndef TRIENODE_H
#define TRIENODE_H

#include "AVLTreeDictionary.h"

//Clase creada por el profesor Mauricio Avil�s
//Se encarga de crear un nodo Trie, el cual contiene un contador, un caracter y un diccionario con hijos.
//Utiliza un diccionario AVLTree para almacenar a sus hijos.

class TrieNode {
private:
    bool isFinal;
    int prefixCount;
    AVLTreeDictionary<char, TrieNode*> children;

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
    void add(char c) {
        children.insert(c, new TrieNode());
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
};

#endif // TRIENODE_H
