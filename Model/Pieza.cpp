#include "Pieza.h"

Pieza::Pieza() {
    this->tipo = "Coraza";
    this->nombre = "Coraza";
    this->salud = 0;
    this->potencia = 0;
}

Pieza::Pieza(std::string tipo, std::string nombre, int salud, int potencia) {
    this->tipo = tipo;
    this->nombre = nombre;
    this->salud = salud;
    this->potencia = potencia;
}

std::string Pieza::getTipo() {
    return this->tipo;
}

std::string Pieza::getNombre() {
    return this->nombre;
}

int Pieza::getSalud() {
    return this->salud;
}

int Pieza::getPotencia() {
    return this->potencia;
}

void Pieza::setSalud(int salud) {
    this->salud = salud;
}

Pieza * Pieza::clone() {
    return new Pieza(this->tipo, this->nombre, this->salud, this->potencia);
}