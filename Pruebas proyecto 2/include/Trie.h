#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include "arraylist.h"
#include <string>
#include <stdexcept>
#include <iostream>

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
        if (index < 0)
            cout << "Palabra no encontrada" << endl;
        else {
            lineas->goToPos(index);
            lineas->getElement()->append(line);
        }
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
        if (index < 0)
            cout << "Palabra no encontrada" << endl;
        else {
            lineas->goToPos(index);
            return lineas->getElement();
        }
    }
};

#endif // TRIE_H
