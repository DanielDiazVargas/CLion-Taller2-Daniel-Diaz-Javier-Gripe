#pragma once

template<typename T>
class NodoSimple {
private:
    NodoSimple* next;
    T* dato;
public:
    NodoSimple();

    NodoSimple(T* dato);

    NodoSimple* getNext();

    T* getDato();

    void setNext(NodoSimple* next);

    ~NodoSimple();
};

#include "NodoSimple.tpp"