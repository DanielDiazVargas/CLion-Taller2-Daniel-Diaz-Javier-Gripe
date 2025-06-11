#pragma once
#include <string>

#include "NodoSimple.h"

template <typename T>
class ListaSimple {
private:
    NodoSimple<T>* head;
public:
    ListaSimple();

    NodoSimple<T>* getHead();

    void setHead(NodoSimple<T>* head);

    NodoSimple<T>* buscar(std::string nombre);

    bool agregar(T* dato);

    bool eliminar(std::string nombre);

    bool isVacia();

    ~ListaSimple();
};

#include "ListaSimple.tpp"