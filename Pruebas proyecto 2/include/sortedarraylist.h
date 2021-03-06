#ifndef SORTEDARRAYLIST_H
#define SORTEDARRAYLIST_H

#include "arraylist.h"

//Clase creada por ???
//Se encarga de implementar una arraylist que acomoda de manera autom�tica los elementos
//que se ingresan de menor a mayor.
//Adem�s implementa busqueda binaria para encontrar elementos dentro de la arraylist.

template <typename E>
class SortedArrayList : public ArrayList<E> {
public:
    SortedArrayList(int max = DEFAULT_MAX_SIZE) : ArrayList<E>(max) {}
    void insert(E element) {
        ArrayList<E>::goToStart();
        while (!ArrayList<E>::atEnd() && element >= ArrayList<E>::getElement()) {
            ArrayList<E>::next();
        }
        ArrayList<E>::insert(element);
    }
    void append(E element) {
        insert(element);
    }
    int indexOf(E element) {
        int min = 0;
        int max = ArrayList<E>::size - 1;
        while (min <= max) {
            int mid = (min + max) / 2;
            if (element == ArrayList<E>::elements[mid]) {
                return mid;
            } else if (element < ArrayList<E>::elements[mid]) {
                max = mid - 1;
            } else {
                min = mid + 1;
            }
        }
        return -1;
    }
    bool contains(E element) {
        return indexOf(element) != -1;
    }
};

#endif // SORTEDARRAYLIST_H
