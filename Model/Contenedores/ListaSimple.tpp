#include "ListaSimple.h"

template <typename T>
ListaSimple<T>::ListaSimple() {
    this->head = nullptr;
}

template <typename T>
NodoSimple<T>* ListaSimple<T>::getHead() {
    return this->head;
}

template <typename T>
void ListaSimple<T>::setHead(NodoSimple<T>* head) {
    this->head = head;
}

template <typename T>
NodoSimple<T>* ListaSimple<T>::buscar(std::string nombre) {
    if (isVacia()) {
        return nullptr;
    }

    NodoSimple<T>* aux = this->head;
    while (aux != nullptr) {
        if (aux->getDato()->getNombre() == nombre) {
            return aux;
        }
        aux = aux->getNext();
    }
    return nullptr;
}

template <typename T>
bool ListaSimple<T>::agregar(T* dato) {
    if (buscar(dato->getNombre()) != nullptr) {
        return false;
    }

    NodoSimple<T>* nuevoNodo = new NodoSimple<T>(dato);
    if (isVacia()) {
        this->head = nuevoNodo;
    } else {
        NodoSimple<T>* aux = this->head;
        while (aux->getNext() != nullptr) {
            aux = aux->getNext();
        }
        aux->setNext(nuevoNodo);
    }

    return true;
}

template <typename T>
bool ListaSimple<T>::eliminar(std::string nombre) {
    if (isVacia()) {
        return false;
    }

    NodoSimple<T>* aux = this->head;
    if (aux->getDato()->getNombre() == nombre) {
        this->head = this->head->getNext();
        aux->setNext(nullptr);
        delete aux;
        return true;
    }

    while (aux->getNext() != nullptr) {
        if (aux->getNext()->getDato()->getNombre() == nombre) {
            NodoSimple<T>* temp = aux->getNext();
            aux->setNext(temp->getNext());
            temp->setNext(nullptr);
            delete temp;
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}

template<typename T>
bool ListaSimple<T>::isVacia() {
    if (this->head == nullptr) {
        return true;
    }
    return false;
}

template <typename T>
ListaSimple<T>::~ListaSimple() {
    NodoSimple<T>* aux = this->head;
    while (aux != nullptr) {
        NodoSimple<T>* temp = aux;
        aux = aux->getNext();
        delete temp;
    }
}