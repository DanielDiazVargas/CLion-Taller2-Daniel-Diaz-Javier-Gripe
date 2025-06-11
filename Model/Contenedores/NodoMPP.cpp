#include "NodoMPP.h"

NodoMPP::NodoMPP() {
    this->left = nullptr;
    this->up = nullptr;
    this->fila = 0;
    this->columna = 0;
    this->pieza = nullptr;
}

NodoMPP::NodoMPP(int fila, int columna, Pieza* pieza) {
    this->left = nullptr;
    this->up = nullptr;
    this->fila = fila;
    this->columna = columna;
    this->pieza = pieza;
}

NodoMPP* NodoMPP::getLeft() {
    return this->left;
}

NodoMPP* NodoMPP::getUp() {
    return this->up;
}

int NodoMPP::getFila() {
    return this->fila;
}

int NodoMPP::getColumna() {
    return this->columna;
}

Pieza* NodoMPP::getPieza() {
    return this->pieza;
}

void NodoMPP::setLeft(NodoMPP* left) {
    this->left = left;
}

void NodoMPP::setUp(NodoMPP* up) {
    this->up = up;
}

void NodoMPP::setFila(int fila) {
    this->fila = fila;
}

void NodoMPP::setColumna(int columna) {
    this->columna = columna;
}

void NodoMPP::setPieza(Pieza* pieza) {
    this->pieza = pieza;
}

NodoMPP::~NodoMPP() {
    this->left = nullptr;
    this->up = nullptr;
    if (this->pieza != nullptr) {
        delete this->pieza;
        this->pieza = nullptr;
    }
}