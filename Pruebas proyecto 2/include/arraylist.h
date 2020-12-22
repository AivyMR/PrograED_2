#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#define DEFAULT_MAX_SIZE 1024

#include "list.h"
#include <stdexcept>

//Clase creada por Mauricio Avilés
//Se encarga de crear una lista de elementos tipo E utilizando un array.

using std::runtime_error;

template <typename E>
class ArrayList : public List<E> {
protected:
    E *elements;
    int max;
    int size;
    int pos;

public:
    ArrayList(int max = DEFAULT_MAX_SIZE) {
        elements = new E[max];
        this->max = max;
        size = 0;
        pos = 0;
    }
    ~ArrayList() {
        delete [] elements;
    }
    void expand() {
        max*=2;
        E *nElements = new E[max];
        for(int x = 0; x<size; x++){
            nElements[x]=elements[x];
        }
        delete [] elements;
        elements = new E[max];
        for(int x = 0; x<size; x++){
            elements[x]=nElements[x];
        }
        delete [] nElements;
    }
    void insert(E element) {
        if (max == size) {
            expand();
        }
        for (int i = size; i > pos; i--) {
            elements[i] = elements[i - 1];
        }
        elements[pos] = element;
        size++;
    }
    void append(E element) {
        if (max == size) {
            expand();
        }
        elements[size] = element;
        size++;
    }
    E remove() {
        if (size == 0) {
            throw runtime_error("List is empty.");
        }
        if (pos < 0 || pos >= size) {
            throw runtime_error("No current element.");
        }
        E res = elements[pos];
        for (int i = pos; i < size - 1; i++) {
            elements[i] = elements[i + 1];
        }
        size--;
        return res;
    }
    void clear() {
        size = pos = 0;
        delete [] elements;
        elements = new E[max];
    }
    E getElement() {
        if (size == 0) {
            throw runtime_error("List is empty.");
        }
        if (pos < 0 || pos > size) {
            throw runtime_error("No current element.");
        }
        return elements[pos];
    }
    void goToStart() {
        pos = 0;
    }
    void goToEnd() {
        pos = size;
    }
    void goToPos(int pos) {
        if (pos < 0 || pos > size) {
            throw runtime_error("Index out of bounds.");
        }
        this->pos = pos;
    }
    void next() {
        if (pos < size) {
            pos++;
        }
    }
    void previous() {
        if (pos > 0) {
            pos--;
        }
    }
    bool atStart() {
        return pos == 0;
    }
    bool atEnd() {
        return pos == size;
    }
    int getPos() {
        return pos;
    }
    int getSize() {
        return size;
    }
    int getMax() {
        return max;
    }
    bool contains(E element) {
        for (goToStart(); !atEnd(); next()) {
            if (getElement() == element) {
                return true;
            }
        }
        return false;
    }
    int indexOf(E element){
        for (goToStart(); !atEnd(); next()) {
            if (getElement() == element) {
                return pos;
            }
        }
        return -1;
    }
    void extend(List<E>* L){
        if (L->getSize()+size>=max){
            expand();
        }
        for (int x=0; x<L->getSize(); x++){
            L->goToPos(x);
            append(L->getElement());
        }
    }
};

#endif // ARRAYLIST_H
