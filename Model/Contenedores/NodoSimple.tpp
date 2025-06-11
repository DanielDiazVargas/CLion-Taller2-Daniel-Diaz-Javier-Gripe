template<typename T>
NodoSimple<T>::NodoSimple() {
    this->next = nullptr;
    this->dato = nullptr;
}

template<typename T>
NodoSimple<T>::NodoSimple(T* dato) {
    this->next = nullptr;
    this->dato = dato;
}

template<typename T>
NodoSimple<T> * NodoSimple<T>::getNext() {
    return this->next;
}

template<typename T>
T* NodoSimple<T>::getDato() {
    return this->dato;
}

template<typename T>
void NodoSimple<T>::setNext(NodoSimple *next) {
    this->next = next;
}

template<typename T>
NodoSimple<T>::~NodoSimple() {
    delete this->dato;
}