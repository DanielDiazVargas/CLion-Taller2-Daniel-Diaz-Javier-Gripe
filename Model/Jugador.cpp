#include "Jugador.h"

Jugador::Jugador() {
    this->nombre = "";
    this->cantidadVictorias = 0;
    this->cantidadDerrotas = 0;
}

Jugador::Jugador(std::string nombre) {
    this->nombre = nombre;
    this->cantidadVictorias = 0;
    this->cantidadDerrotas = 0;
}

Jugador::Jugador(std::string nombre, int cantidadVictorias, int cantidadDerrotas) {
    this->nombre = nombre;
    this->cantidadVictorias = cantidadVictorias;
    this->cantidadDerrotas = cantidadDerrotas;
}

std::string Jugador::getNombre() {
    return this->nombre;
}

int Jugador::getCantidadVictorias() {
    return this->cantidadVictorias;
}

int Jugador::getCantidadDerrotas() {
    return this->cantidadDerrotas;
}

void Jugador::sumarVictoria() {
    this->cantidadVictorias ++;
}

void Jugador::sumarDerrota() {
    this->cantidadDerrotas ++;
}