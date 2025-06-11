#pragma once
#include "../Pieza.h"

/**
 * @class NodoMPP
 * @brief Representa un nodo dentro de una matriz poco poblada (MPP) que almacena una pieza de un barco.
 */
class NodoMPP {
private:
    NodoMPP* left;      // Puntero al nodo a la izquierda.
    NodoMPP* up;        // Puntero al nodo superior.
    int fila;           // Fila en la que se encuentra el nodo.
    int columna;        // Columna en la que se encuentra el nodo.
    Pieza* pieza;       // Pieza del barco que almacena el nodo.

public:
    /**
     * @brief Constructor por defecto del nodo.
     */
    NodoMPP();

    /**
     * @brief Constructor con inicialización completa.
     * @param fila Número de fila.
     * @param columna Número de columna.
     * @param pieza Pieza del barco.
     */
    NodoMPP(int fila, int columna, Pieza* pieza);

    /**
     * @brief Obtiene el puntero al nodo izquierdo.
     * @return NodoMPP* Puntero al nodo izquierdo.
     */
    NodoMPP* getLeft();

    /**
     * @brief Obtiene el puntero al nodo superior.
     * @return NodoMPP* Puntero al nodo superior.
     */
    NodoMPP* getUp();

    /**
     * @brief Obtiene la fila del nodo.
     * @return int Fila.
     */
    int getFila();

    /**
     * @brief Obtiene la columna del nodo.
     * @return int Columna.
     */
    int getColumna();

    /**
     * @brief Obtiene la pieza almacenada en el nodo.
     * @return Pieza* pieza.
     */
    Pieza* getPieza();

    /**
     * @brief Establece el puntero al nodo izquierdo.
     * @param left Puntero al nodo izquierdo.
     */
    void setLeft(NodoMPP* left);

    /**
     * @brief Establece el puntero al nodo superior.
     * @param up Puntero al nodo superior.
     */
    void setUp(NodoMPP* up);

    /**
     * @brief Establece la fila del nodo.
     * @param fila Número de fila.
     */
    void setFila(int fila);

    /**
     * @brief Establece la columna del nodo.
     * @param columna Número de columna.
     */
    void setColumna(int columna);

    /**
     * @brief Establece la coraza del nodo.
     * @param pieza Pieza del barco.
     */
    void setPieza(Pieza* pieza);

    /**
     * @brief Destructor del nodo.
     */
    ~NodoMPP();
};