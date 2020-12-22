#ifndef NODE_H
#define NODE_H
#include <cstdlib>

//Clase creada por Mauricio Avilés
//Se encarga de crear un nodo de tipo E con un puntero a otro nodo de tipo E

template <typename E>
class Node {
public:
    E element;
    Node<E>* next;

    Node(E element, Node<E>* next = nullptr) {
        this->element = element;
        this->next = next;
    }
    Node(Node<E>* next = nullptr) {
        this->next = next;
    }
    ~Node() {}
};

#endif // NODE_H
