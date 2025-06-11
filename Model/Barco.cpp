#include "Barco.h"

Barco::Barco() {
    this->nombre = "";
    this->tamanio = 0;
    this->duenio = "";
    this->cantidadPiezasEspeciales = 0;
    this->piezasEspeciales = nullptr;

}

Barco::Barco(std::string nombre, int tamanio, std::string duenio, int cantidadPiezasEspeciales) {
    this->nombre = nombre;
    this->tamanio = tamanio;
    this->duenio = duenio;
    this->cantidadPiezasEspeciales = cantidadPiezasEspeciales;
    this->piezasEspeciales = new std::string[tamanio];
    for (int i = 0; i < tamanio; i++) {
        piezasEspeciales[i] = "Coraza";
    }
}

std::string Barco::getNombre() {
    return this->nombre;
}

int Barco::getTamanio() {
    return this->tamanio;
}

std::string Barco::getDuenio() {
    return this->duenio;
}

int Barco::getCantidadPiezasEspeciales() {
    return this->cantidadPiezasEspeciales;
}

std::string * Barco::getPiezasEspeciales() {
    return this->piezasEspeciales;
}

void Barco::setCantidadPiezasEspeciales(int cantidadPiezasEspeciales) {
    this->cantidadPiezasEspeciales = cantidadPiezasEspeciales;
}

void Barco::agregarPieza(std::string nombrePieza, int slot) {
    this->piezasEspeciales[slot] = nombrePieza;
}

void Barco::quitarPieza(int slot) {
    this->piezasEspeciales[slot] = "Coraza";
}

Barco::~Barco() {
    delete[] piezasEspeciales;
}