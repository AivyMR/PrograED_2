#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include "arraylist.h"
#include "SortedArrayDictionary.h"
#include <string>
#include <stdexcept>
#include <iostream>

//Clase creada por el profesor Mauricio Avilés y modificada por David Pastor
//Se encarga de implementar la estructura Trie, la cual almacena palabras utilizando nodos Trie.
//Estos nodos se encargan de almacenar los caracteres de las palabras y la cantidad de palabras
//en las que se utiliza cada caracter.
//Además de esto, se hicieron modificaciones para que se guarden en una arraylist la lista de lineas
//en las que aparece cada palabra en el texto.

using namespace std;

class Trie {
private:
    TrieNode* root;

    //######################################################
    //###############--Funciones del Trie--#################
    //######################################################

    TrieNode* find(string prefix) {
        TrieNode* current = root;
        for (unsigned int i = 0; i < prefix.size(); i++) {
            if (!current->contains(prefix[i]))
                return nullptr;
            current = current->getChild(prefix[i]);
        }
        return current;
    }
    void clearAux(TrieNode* current) {
        List<TrieNode*>* pointers = current->getChildrenPointers();
        pointers->goToStart();
        while (!pointers->atEnd()) {
            clearAux(pointers->getElement());
            pointers->next();
        }
        delete current;
    }
    void getMatchesAux(TrieNode* current, string prefix, List<string>* words) {
        if (current->getIsFinal())
            words->append(prefix);
        List<char>* children = current->getChildren();
        for (children->goToStart(); !children->atEnd(); children->next()) {
            char c = children->getElement();
            string newPrefix = prefix;
            newPrefix.append(1, c);
            getMatchesAux(current->getChild(c), newPrefix, words);
        }
        delete children;
    }

    //######################################################
    //###############--Funciones del LIST--#################
    //######################################################

    ArrayList<string> * palabras;
    ArrayList<ArrayList<int>* > * lineas;

    void nuevaPalabra(string word, int line){
        palabras->append(word);
        ArrayList<int> * lines = new ArrayList<int>();
        lines->append(line);
        lineas->append(lines);
    }

    void addLine(string word, int line){
        int index = palabras->indexOf(word);
        lineas->goToPos(index);
        lineas->getElement()->append(line);
    }

    SortedArrayDictionary<int, string> * getOcurrences(){
        ifstream * ignorar = new ifstream();
        ArrayList<string> * noUsar = new ArrayList<string>();
        ignorar->open("ignorar.txt", ifstream::in);
        char caracter[10];
        string palabra;
        while (ignorar->good()){
            ignorar->getline(caracter, 10, '\n');
            palabra = caracter;
            noUsar->append(palabra);
        }
        SortedArrayDictionary<int, string> * veces = new SortedArrayDictionary<int, string>();
        palabras->goToStart();
        for (lineas->goToStart(); !lineas->atEnd(); lineas->next()){
            veces->insert(lineas->getElement()->getSize(), palabras->getElement());
            palabras->next();
        }
        return veces;
    }

public:
    Trie() {
        root = new TrieNode();
        palabras = new ArrayList<string>(1048576);
        lineas = new ArrayList<ArrayList<int>* >(131072);
    }
    ~Trie() {
        clear();
        delete root;
        delete palabras;
        delete lineas;
    }
    void insert(string word, int line) {
        if (containsWord(word)){
            addLine(word, line);
            return;
        }
        TrieNode* current = root;
        for (unsigned int i = 0; i < word.size(); i++) {
            current->increaseCount();
            if (!current->contains(word[i]))
                current->add(word[i]);
            current = current->getChild(word[i]);
        }
        current->increaseCount();
        current->setIsFinal(true);
        nuevaPalabra(word, line);
    }
    bool containsWord(string word) {
        TrieNode* node = find(word);
        return (node == nullptr)? false : node->getIsFinal();
    }
    bool containsPrefix(string prefix) {
        TrieNode* node = find(prefix);
        return (node == nullptr)? false : true;
    }
    int prefixCount(string prefix) {
        TrieNode* node = find(prefix);
        return (node == nullptr)? 0 : node->getPrefixCount();
    }
    void remove(string word) {
        if (!containsWord(word))
            throw runtime_error("Word not found.");
        TrieNode* current = root;
        for (unsigned int i = 0; i < word.size(); i++) {
            current->decreaseCount();
            TrieNode* child = current->getChild(word[i]);
            if (current->getPrefixCount() == 0)
                delete current;
            else if (child->getPrefixCount() == 1)
                current->remove(word[i]);
            current = child;
        }
        current->decreaseCount();
        if (current->getPrefixCount() == 0)
            delete current;
        else
            current->setIsFinal(false);
    }
    void clear() {
        clearAux(root);
        root = new TrieNode();
    }
    List<string>* getMatches(string prefix) {
        List<string>* words = new DLinkedList<string>();
        TrieNode* current = find(prefix);
        getMatchesAux(current, prefix, words);
        return words;
    }
    void print() {
        List<string>* words = getMatches("");
        for (words->goToStart(); !words->atEnd(); words->next()) {
            cout << words->getElement() << endl;
        }
        delete words;
    }

    ArrayList<int> * getLines(string word){
        int index = palabras->indexOf(word);
        if (index < 0){
            cout << "Palabra no encontrada" << endl;
            return nullptr;
        }
        else {
            lineas->goToPos(index);
            return lineas->getElement();
        }
    }

    int getLine(string word){
        return palabras->indexOf(word);
    }

    AVLTreeDictionary<string, int> * searchByLen(unsigned int tamano){
        AVLTreeDictionary<string, int> * words = new AVLTreeDictionary<string, int>();
        for (palabras->goToStart(); !palabras->atEnd(); palabras->next()){
            string wort = palabras->getElement();
            if (wort.size() == tamano){
                int index = palabras->indexOf(wort);
                lineas->goToPos(index);
                int veces = lineas->getElement()->getSize();
                words->insert(wort, veces);
            }
        }
        return words;
    }

    SortedArrayDictionary<int, string> * mostUsed(int n){
        SortedArrayDictionary<int, string> * veces = getOcurrences();
        SortedArrayDictionary<int, string> * top = new SortedArrayDictionary<int, string>();
        for (int x = veces->getSize()-2; x >= veces->getSize()-n-1; x--){
            KVPair<int, string> par = veces->getPair(x);
            top->insert(par.getKey(), par.getValue());
        }
        delete veces;
        return top;
    }

    SortedArrayDictionary<int, string> * lessUsed(int n){
        SortedArrayDictionary<int, string> * veces = getOcurrences();
        SortedArrayDictionary<int, string> * top = new SortedArrayDictionary<int, string>();
        for (int x = 0; x < n; x++){
            KVPair<int, string> par = veces->getPair(x);
            top->insert(par.getKey(), par.getValue());
        }
        delete veces;
        return top;
    }
};

#endif // TRIE_H
