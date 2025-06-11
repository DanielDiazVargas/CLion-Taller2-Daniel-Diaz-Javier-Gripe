#pragma once
#include <string>

/**
 * @class Barco
 * @brief Representa un barco.
 *
 * Esta clase permite crear, acceder y modificar las piezas del barco.
 */
class Barco {
private:
    std::string nombre;              // Nombre unico del barco
    int tamanio;                     // Tamnio que posee el barcoi
    std::string duenio;              // Nombre del duenio del barco
    int cantidadPiezasEspeciales;    // Cantidad de piezas especiales que posee el barco
    std::string* piezasEspeciales;   // Array que almacena los nombres las piezas que posee el barco
public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa los atributos con valores por defecto.
     */
    Barco();

    /**
     * @brief Constructor parametrizado.
     *
     * @param nombre Nombre del barco.
     * @param tamanio Tamanio del barco.
     * @param duenio Nombre del duenio del barco.
     * @param cantidadPiezasEspeciales Cantidad de piezas especiales del barco.
     */
    Barco(std::string nombre, int tamanio, std::string duenio, int cantidadPiezasEspeciales);

    /**
     * @brief Obtiene el nombre del barco.
     * @return Nombre como una cadena de texto.
     */
    std::string getNombre();

    /**
     * @brief Obtiene el tamanio del barco.
     * @return Valor entero del tamanio.
     */
    int getTamanio();

    /**
     * @brief Obtiene el nombre del duenio del barco.
     * @return Nombre como una cadena de texto.
     */
    std::string getDuenio();

    /**
     * @brief Obtiene la cantidad de piezas especiales del barco.
     * @return Valor entero del tamanio.
     */
    int getCantidadPiezasEspeciales();

    /**
     * @brief Obtiene el array de piezas especiales del barco.
     * @return Puntero al array de las piezas especuiales.
     */
    std::string* getPiezasEspeciales();

    /**
     * @brief Modifica la cantidad de piezas especiales del barco.
     * @param cantidadPiezasEspeciales Nuevo valor para la cantidad de piezas espéciales.
     */
    void setCantidadPiezasEspeciales(int cantidadPiezasEspeciales);

    /**
     * @brief Agregar una nueva pieza especial al barco.
     * @param nombrePieza Nombre de la nueva pieza.
     * @param slot Ubicacion en el array de la nueva pieza.
     */
    void agregarPieza(std::string nombrePieza, int slot);

    /**
     * @brief Quita pieza especial al barco.
     * @param slot Ubicacion en el array de la pieza a quitar.
     */
    void quitarPieza(int slot);

    /**
    * @brief Destructor del barco.
    */
    ~Barco();
};