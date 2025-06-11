#pragma once
#include "NodoMPP.h"

#include "../Pieza.h"

/**
 * @brief Clase que representa una Matriz Poco Poblada (MPP).
 *
 * Esta clase implementa una matriz dispersa donde solo se almacenan los elementos no nulos
 * en nodos dinámicos.
 */
class MPP {
private:
    int largo;                // Cantidad de columnas de la matriz.
    int alto;                 // Cantidad de filas de la matriz.
    NodoMPP** AROW;           // Arreglo de punteros a nodos cabecera por fila.
    NodoMPP** ACOL;           // Arreglo de punteros a nodos cabecera por columna.

public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa los atributos a valores por defecto.
     */
    MPP();

    /**
     * @brief Constructor con dimensiones de la matriz.
     *
     * @param largo Cantidad de columnas.
     * @param alto Cantidad de filas.
     */
    MPP(int largo, int alto);

    /**
     * @brief Obtiene el largo de la matriz.
     * @return Valor entero del largo.
     */
    int getLargo();

    /**
     * @brief Obtiene el alto de la matriz.
     * @return Valor entero del alto.
     */
    int getAlto();

    /**
     * @brief Busca un nodo en la posición dada.
     *
     * @param fila Posición de la fila.
     * @param columna Posición de la columna.
     * @return Puntero al nodo si existe, nullptr en caso contrario.
     */
    NodoMPP* buscar(int fila, int columna);

    /**
     * @brief Agrega un nodo con pieza en la posición dada.
     *
     * Si ya existe un nodo en esa posición, no se agrega uno nuevo.
     *
     * @param fila Posición de la fila.
     * @param columna Posición de la columna.
     * @param pieza Pieza del barco.
     * @return 0 si se agregó correctamente, 1 si las coordenadas están fuera de rango de la matriz
     * o 2 si ya existe un nodo en las coordenadas.
     */
    int agregar(int fila, int columna, Pieza* pieza);

    /**
     * @brief Elimina un nodo de la posición dada.
     *
     * @param fila Posición de la fila.
     * @param columna Posición de la columna.
     * @return 0 si se eliminó correctamente, 1 si las coordenadas están fuera de rango de la matriz
     * o 2 si no existe un nodo en las coordenadas.
     */
    int eliminar(int fila, int columna);

    /**
     *@brief Muevo un nodo de la matriz a una nueva posicion
     *
     * @param fila
     * @param columna
     * @return 0 si se movio correctamente, 1 si las coordenadas están fuera de rango de la matriz,
     * 2 si no existe un nodo en las coordenadas o 3 si ya hay un nodo en las nueva coordenadas.
     */
    int mover(int fila, int columna, int nuevaFila, int nuevaColumna);

    /**
     * @brief Elimina todos los nodos no cabecera de la matriz
     */
    void vaciarMatriz();

    /**
    * @brief Destructor de la matriz.
    */
    ~MPP();
};