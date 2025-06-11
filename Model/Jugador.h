#pragma once
#include <string>

#include "Barco.h"

/**
 * @class Jugador
 * @brief Representa al jugador.
 *
 * Esta clase permite crear, acceder y modificar un jugador.
 */
class Jugador {
private:
    std::string nombre;      // Nombre unico del jugador
    int cantidadVictorias;   // Cantidad de victorias con las que cuenta el jugador
    int cantidadDerrotas;    // Cantidad de derrotas con las que cuenta el jugador
public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa los atributos con valores por defecto.
     */
    Jugador();

    /**
     * @brief Constructor parametrizado.
     *
     * @param nombre Nombre del jugador.
     */
    Jugador(std::string nombre);

    /**
     * @brief Constructor parametrizado.
     *
     * @param nombre Nombre del jugador.
     * @param cantidadVictorias Cantidad de veces que el jugador gano.
     * @param cantidadDerrotas Cantidad de veces que el jugador perdio.
     */
    Jugador(std::string nombre, int cantidadVictorias, int cantidadDerrotas);

    /**
     * @brief Obtiene el nombre del jugador.
     * @return Nombre como una cadena de texto.
     */
    std::string getNombre();

    /**
     * @brief Obtiene la cantidad de victorias del jugador.
     * @return Valor entero de las victorias.
     */
    int getCantidadVictorias();

    /**
     * @brief Obtiene la cantidad de derrotas del jugador.
     * @return Valor entero de las derrotas.
     */
    int getCantidadDerrotas();

    /**
     * @brief Aumenta en 1 las victorias del jugador.
     */
    void sumarVictoria();

    /**
     * @brief Aumenta en 1 las derrotas del jugador.
     */
    void sumarDerrota();
};