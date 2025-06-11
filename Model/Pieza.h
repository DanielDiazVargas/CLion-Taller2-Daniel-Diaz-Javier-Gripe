#pragma once
#include <string>

/**
 * @class Pieza
 * @brief Representa una pieza de un barco.
 *
 * Esta clase permite crear, acceder y modificar una pieza, y también duplicarla mediante un metodo clone.
 */
class Pieza {
private:
    std::string tipo;    // Tipo de la pieza ((Propulsor, Metralla, Misil,Coraza(por defecto))
    std::string nombre;  // Nombre único de la pieza
    int salud;           // Salud actual de la pieza (puede disminuir con el daño)
    int potencia;        // Potencia de ataque o la potencia de movimiento del barco

public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa los atributos con valores por defecto.
     */
    Pieza();

    /**
     * @brief Constructor parametrizado.
     *
     * @param tipo Tipo de la pieza.
     * @param nombre Nombre de la pieza.
     * @param salud Salud inicial de la pieza.
     * @param potencia Potencia de la pieza.
     */
    Pieza(std::string tipo, std::string nombre, int salud, int potencia);

    /**
     * @brief Obtiene el tipo de la pieza.
     * @return Tipo como una cadena de texto.
     */
    std::string getTipo();

    /**
     * @brief Obtiene el nombre de la pieza.
     * @return Nombre como una cadena de texto.
     */
    std::string getNombre();

    /**
     * @brief Obtiene la salud actual de la pieza.
     * @return Valor entero de la salud.
     */
    int getSalud();

    /**
     * @brief Obtiene la potencia de ataque de la pieza.
     * @return Valor entero de la potencia.
     */
    int getPotencia();

    /**
     * @brief Modifica la salud actual de la pieza.
     * @param salud Nuevo valor para la salud.
     */
    void setSalud(int salud);

    /**
     * @brief Crea una copia profunda de la pieza actual.
     *
     * @return Puntero a una nueva instancia de Pieza con los mismos atributos.
     */
    Pieza* clone();
};