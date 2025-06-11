#include "MPP.h"

/**
 * @brief Constructor por defecto.
 */
MPP::MPP() {
    this->alto = 0;
    this->largo = 0;
    this->ACOL = nullptr;
    this->AROW = nullptr;
}

/**
 * @brief Constructor con tamaño definido.
 * @param largo Número de columnas.
 * @param alto Número de filas.
 */
MPP::MPP(int largo, int alto) {
    this->alto = alto;
    this->largo = largo;

    // Inicializar columnas (cabeceras)
    this->ACOL = new NodoMPP*[largo + 1];
    for (int i = 1; i <= largo; i++) {
        this->ACOL[i] = new NodoMPP();
        this->ACOL[i]->setFila(0);
        this->ACOL[i]->setColumna(i);
        this->ACOL[i]->setUp(this->ACOL[i]);
    }

    // Inicializar filas (cabeceras)
    this->AROW = new NodoMPP*[alto + 1];
    for (int i = 1; i <= alto; i++) {
        this->AROW[i] = new NodoMPP();
        this->AROW[i]->setFila(i);
        this->AROW[i]->setColumna(0);
        this->AROW[i]->setLeft(this->AROW[i]);
    }
}

/**
* @brief Obtiene el largo de la matriz.
* @return Valor entero del largo.
*/
int MPP::getLargo() {
    return this->largo;
}

/**
* @brief Obtiene el largo de la matriz.
* @return Valor entero del largo.
*/
int MPP::getAlto() {
    return this->alto;
}

/**
 * @brief Busca un nodo en la posición indicada.
 * @return Puntero al nodo encontrado o nullptr si no existe.
 */
NodoMPP* MPP::buscar(int fila, int columna) {
    if (columna < 1 || columna > this->largo || fila < 1 || fila > this->alto) {
        return nullptr;
    }

    NodoMPP* aux = this->AROW[fila]->getLeft();
    while (aux != this->AROW[fila]) {
        if (aux->getColumna() == columna) {
            return aux;
        }
        aux = aux->getLeft();
    }
    return nullptr;
}

/**
 * @brief Agrega un nuevo nodo en una posición dada.
 * @return 0 si éxito, 1 si fuera de rango, 2 si ya existe.
 */
int MPP::agregar(int fila, int columna, Pieza* pieza) {
    if (columna < 1 || columna > this->largo || fila < 1 || fila > this->alto) {
        return 1;
    }

    if (buscar(fila, columna) != nullptr) {
        return 2;
    }

    NodoMPP* nuevoNodo = new NodoMPP(fila, columna, pieza);

    // Insertar en la fila
    NodoMPP* aux = this->AROW[fila];
    while (aux->getLeft() != this->AROW[fila] && aux->getLeft()->getColumna() > columna) {
        aux = aux->getLeft();
    }
    nuevoNodo->setLeft(aux->getLeft());
    aux->setLeft(nuevoNodo);

    // Insertar en la columna
    aux = this->ACOL[columna];
    while (aux->getUp() != this->ACOL[columna] && aux->getUp()->getFila() > fila) {
        aux = aux->getUp();
    }
    nuevoNodo->setUp(aux->getUp());
    aux->setUp(nuevoNodo);

    return 0;
}

/**
 * @brief Elimina el nodo en la posición dada.
 * @return 0 si éxito, 1 si fuera de rango, 2 si no existe.
 */
int MPP::eliminar(int fila, int columna) {
    if (columna < 1 || columna > this->largo || fila < 1 || fila > this->alto) {
        return 1;
    }

    NodoMPP* nodoEliminar = buscar(fila, columna);
    if (nodoEliminar == nullptr) {
        return 2;
    }

    // Buscar y actualizar enlaces izquierda
    NodoMPP* aux = this->AROW[fila];
    while (aux->getLeft() != nodoEliminar) {
        aux = aux->getLeft();
    }
    aux->setLeft(nodoEliminar->getLeft());

    // Buscar y actualizar enlaces arriba
    aux = this->ACOL[columna];
    while (aux->getUp() != nodoEliminar) {
        aux = aux->getUp();
    }
    aux->setUp(nodoEliminar->getUp());

    delete nodoEliminar;
    return 0;
}

/**
 * @brief Cambia la posicion de un nodo de la matriz.
 * @return 0 si éxito, 1 si fuera de rango, 2 si no existe, 3 si ya esta ocupada.
 */
int MPP::mover(int fila, int columna, int nuevaFila, int nuevaColumna) {
    if (columna < 1 || columna > this->largo || fila < 1 || fila > this->alto) {
        return 1;
    }

    NodoMPP* nodoMover = buscar(fila, columna);
    if (nodoMover == nullptr) {
        return 2;
    }

    if (buscar(nuevaFila, columna) != nullptr) {
        return 3;
    }

    // Actualiza los enlaces y aisla el nodo a mover
    NodoMPP* aux = this->AROW[fila];
    while (aux->getLeft() != nodoMover) {
        aux = aux->getLeft();
    }
    aux->setLeft(nodoMover->getLeft());

    aux = this->ACOL[columna];
    while (aux->getUp() != nodoMover) {
        aux = aux->getUp();
    }
    aux->setUp(nodoMover->getUp());

    // Agrega el nodo a la nueva posicion.
    aux = this->AROW[nuevaFila];
    while (aux->getLeft() != this->AROW[fila] && aux->getLeft()->getColumna() > columna) {
        aux = aux->getLeft();
    }
    nodoMover->setLeft(aux->getLeft());
    aux->setLeft(nodoMover);

    aux = this->ACOL[columna];
    while (aux->getUp() != this->ACOL[columna] && aux->getUp()->getFila() > fila) {
        aux = aux->getUp();
    }
    nodoMover->setUp(aux->getUp());
    aux->setUp(nodoMover);

    nodoMover->setFila(nuevaFila);
    nodoMover->setColumna(nuevaColumna);
    return 0;
}

/**
 * @brief Elimina todos los nodos de la matriz excepto los nodos cabecera.
 */
void MPP::vaciarMatriz() {
    for (int i = 1; i <= alto; ++i) {
        NodoMPP* fila = AROW[i]->getLeft();
        while (fila != AROW[i]) {
            NodoMPP* temp = fila;
            fila = fila->getLeft();
            delete temp;
        }
    }
}

/**
 * @brief Destructor de la clase. Libera todos los nodos y memoria dinámica.
 */
MPP::~MPP() {
    // Elimina todos los nodos
    vaciarMatriz();

    // Eliminar cabeceras de fila
    for (int j = 1; j <= this->alto; ++j) {
        delete this->AROW[j];
    }

    // Eliminar cabeceras de columna
    for (int j = 1; j <= this->largo; ++j) {
        delete this->ACOL[j];
    }

    delete[] this->AROW;
    delete[] this->ACOL;
}