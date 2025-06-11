#include "ListaCircularSimple.h"

ListaCircularSimple::ListaCircularSimple() {
    this->head = nullptr;
}

NodoSimple<Jugador>* ListaCircularSimple::getHead() {
    return this->head;
}

void ListaCircularSimple::setHead(NodoSimple<Jugador>* head) {
    this->head = head;
}

NodoSimple<Jugador>* ListaCircularSimple::buscar(std::string nombre) {
    if (isVacia()) {
        return nullptr;
    }

    NodoSimple<Jugador>* aux = this->head;
    do {
        if (aux->getDato()->getNombre() == nombre) {
            return aux;
        }
        aux = aux->getNext();
    }while (aux != this->head);
    return nullptr;
}

bool ListaCircularSimple::agregar(Jugador* jugador) {
    if (buscar(jugador->getNombre()) != nullptr) {
        return false;
    }

    NodoSimple<Jugador>* nuevoNodo = new NodoSimple(jugador);

    if (isVacia()) {
        this->head = nuevoNodo;
        nuevoNodo->setNext(nuevoNodo);
    } else {
        NodoSimple<Jugador>* aux = this->head;
        while (aux->getNext() != this->head) {
            aux = aux->getNext();
        }
        aux->setNext(nuevoNodo);
        nuevoNodo->setNext(this->head);
    }

    return true;
}


bool ListaCircularSimple::eliminar(std::string nombre) {
    if (isVacia()) {
        return false;
    }

    NodoSimple<Jugador>* aux = this->head;
    if (aux->getDato()->getNombre() == nombre) {
        if (aux->getNext() == aux) {
            delete aux;
            this->head = nullptr;
        } else {
            NodoSimple<Jugador>* temp = this->head;
            while (aux->getNext() != this->head) {
                aux = aux->getNext();
            }
            aux->setNext(this->head->getNext());
            this->head = this->head->getNext();
            temp->setNext(nullptr);
            delete temp;
        }
        return true;
    }

    aux = aux->getNext();
    do {
        if (aux->getNext()->getDato()->getNombre() == nombre) {
            NodoSimple<Jugador>* temp = aux->getNext();
            aux->setNext(temp->getNext());
            temp->setNext(nullptr);
            delete temp;
            return true;
        }
        aux = aux->getNext();
    } while (aux != this->head);

    return false;
}

bool ListaCircularSimple::isVacia() {
    if (this->head == nullptr) {
        return true;
    }
    return false;
}


ListaCircularSimple::~ListaCircularSimple() {
    if (this->head == nullptr) return;

    NodoSimple<Jugador>* actual = this->head->getNext();
    while (actual != this->head) {
        NodoSimple<Jugador>* temp = actual;
        actual = actual->getNext();
        delete temp;
    }
    delete this->head;
    this->head = nullptr;
}