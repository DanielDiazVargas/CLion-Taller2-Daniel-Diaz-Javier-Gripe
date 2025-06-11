#pragma once
#include "NodoSimple.h"
#include "../Jugador.h"

class ListaCircularSimple {
private:
    NodoSimple<Jugador>* head;
public:
    ListaCircularSimple();

    NodoSimple<Jugador>* getHead();

    void setHead(NodoSimple<Jugador>* head);

    NodoSimple<Jugador>* buscar(std::string nombre);

    bool agregar(Jugador* jugador);

    bool eliminar(std::string nombre);

    bool isVacia();

    ~ListaCircularSimple();
};