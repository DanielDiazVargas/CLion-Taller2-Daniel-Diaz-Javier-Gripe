#include "Sistema.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>

Sistema::Sistema() {
    this->listaJugadores = new ListaCircularSimple();
    this->listaPiezas = new ListaSimple<Pieza>();
    this->listaBarco = new ListaSimple<Barco>();
    lecturaArchivos();
}

bool Sistema::verificadorArchivos(std::string nombreArchivo) {
    std::string ubicacion = "../Files/" + nombreArchivo + ".txt";
    std::ifstream archivo(ubicacion);
    if (!archivo.is_open()) {
        std::cout << "Advertencia: No se encontro el archivo \"" << nombreArchivo << ".txt\". Asegurese que se encuentre en \"" << ubicacion << "\".\n";
        archivo.close();
        return false;
    }
    archivo.close();
    return true;
}

void Sistema::lecturaArchivos() {
    std::cout << "Leyendo archivos...\n";

    std::ifstream archivo;
    std::string linea;

    if (verificadorArchivos("jugadores")) {
        archivo.open("../Files/jugadores.txt");   //Lee jugadores.txt

        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string numeros;

            //Variables para crear un jugador
            std::string nombre;
            int cantidadVictorias;
            int cantidadDerrotas;

            std::getline(ss, nombre, ',');
            std::getline(ss, numeros, ',');
            cantidadVictorias = std::stoi(numeros);
            std::getline(ss, numeros, ',');
            cantidadDerrotas = std::stoi(numeros);

            if (listaJugadores->buscar(nombre) != nullptr) {
                continue;
            }

            if (!listaJugadores->agregar(new Jugador(nombre, cantidadVictorias, cantidadDerrotas))) {
                std::cout << "Advertencia: Un jugador no pudo ser agregado.\n";
            }
        }
        std::cout << "Jugadores cargados!\n";
        archivo.close();
    }

    if (verificadorArchivos("piezas")) {
        archivo.open("../Files/piezas.txt");   //Lee piezas.txt

        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string numeros;

            //Variables para crear una pieza
            std::string tipo;
            std::string nombre;
            int salud;
            int potencia;

            std::getline(ss, tipo, ',');
            std::getline(ss, nombre, ',');
            std::getline(ss, numeros, ',');
            salud = std::stoi(numeros);
            std::getline(ss, numeros, ',');
            potencia = std::stoi(numeros);

            if (listaPiezas->buscar(nombre) != nullptr) {
                continue;
            }

            if (!listaPiezas->agregar(new Pieza(tipo, nombre, salud, potencia))) {
                std::cout << "Advertencia: Una pieza no pudo ser agregada.\n";
            }
        }
        std::cout << "Piezas cargadas!\n";
        archivo.close();
    }

    if (verificadorArchivos("barcos")) {
        archivo.open("../Files/barcos.txt");   //Lee barcos.txt

        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string numeros;

            //Variables para crear un barco
            std::string nombre;
            int tamanio;
            std::string duenio;
            int cantidadPiezasEspeciales;

            std::getline(ss, nombre, ',');
            std::getline(ss, numeros, ',');
            tamanio = std::stoi(numeros);
            std::getline(ss, duenio, ',');
            std::getline(ss, numeros, ',');
            cantidadPiezasEspeciales = std::stoi(numeros);

            if (listaBarco->buscar(nombre) != nullptr) {
                continue;
            }

            Barco* barco = new Barco(nombre, tamanio, duenio, cantidadPiezasEspeciales);

            //Se agregan las piezas al barco
            for (int i = 0; i < cantidadPiezasEspeciales; ++i) {
                int slot;
                std::getline(archivo, linea);
                std::stringstream ss(linea);
                std::getline(ss, nombre, ',');
                std::getline(ss, numeros, ',');
                slot = std::stoi(numeros);

                if (listaPiezas->buscar(nombre) != nullptr) {
                    if (listaPiezas->buscar(nombre)->getDato()->getNombre() == nombre) {
                        agregarPieza(barco, nombre, slot);
                        barco->setCantidadPiezasEspeciales(barco->getCantidadPiezasEspeciales() -1);
                    }
                }
            }

            if (!listaBarco->agregar(barco)) {
                std::cout << "Advertencia: Un barco no pudo ser agregado.\n";
            }
        }
        std::cout << "Barcos cargados!\n";
        archivo.close();
    }

    std::cout << "Lectura finalizada con exito.\n";
}

void Sistema::escrituraArchivos() {
    //Se crea un flujo de salida para los archivos y borra el contenido de los mismos
    std::ofstream archivoJugadores("../Files/jugadores.txt", std::ios::trunc);
    std::ofstream archivoBarcos("../Files/barcos.txt", std::ios::trunc);
    std::ofstream archivoPiezas("../Files/piezas.txt", std::ios::trunc);

    //Guarda la listaPiezas en el archivo "piezas.txt"
    NodoSimple<Pieza>* auxPieza = listaPiezas->getHead();
    while (auxPieza != nullptr) {

        //Guarda los datos de las piezas
        Pieza* pieza = auxPieza->getDato();
        archivoPiezas << pieza->getTipo() << ","
                      << pieza->getNombre() << ","
                      << pieza->getSalud() << ","
                      << pieza->getPotencia() << "\n";
        auxPieza = auxPieza->getNext();
    }

    //Guarda la listaJugadores en el archivo "jugadores.txt"
    NodoSimple<Jugador>* auxJugador = listaJugadores->getHead();
    if (auxJugador != nullptr) {
        do {
            //Guarda los datos del jugador
            Jugador* jugador = auxJugador->getDato();
            archivoJugadores << jugador->getNombre() << ","
                             << jugador->getCantidadVictorias() << ","
                             << jugador->getCantidadDerrotas() << "\n";
            auxJugador = auxJugador->getNext();
        }while (auxJugador != listaJugadores->getHead());
    }

    //Guarda la listaBarcos en el archivo "barcos.txt"
    NodoSimple<Barco>* auxBarco = listaBarco->getHead();
    while (auxBarco != nullptr) {

        //Guarda los datos del barco
        Barco* barco = auxBarco->getDato();
        archivoBarcos << barco->getNombre() << ","
                      << barco->getTamanio() << ","
                      << barco->getDuenio() << ","
                      << barco->getCantidadPiezasEspeciales() << "\n";
        for (int slot = 0; slot < barco->getTamanio(); ++slot) {
            if (barco->getPiezasEspeciales()[slot] != "Coraza") {
                archivoBarcos << barco->getPiezasEspeciales()[slot] << ","
                              << slot << "\n";
            }
        }
        auxBarco = auxBarco->getNext();
    }

    archivoPiezas.close();
    archivoJugadores.close();
    archivoBarcos.close();
}

void Sistema::menuPrincipal() {
    std::cout << "\nPreione ENTER para comenzar\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {
        std::cout
        << "\n***** MENU PRINCIPAL *****\n"
        << "[1] - Iniciar Juego\n"
        << "[2] - Menu de Barcos\n"
        << "[3] - Menu de Jugadores\n"
        << "[4] - Menu de Piezas\n"
        << "[5] - Iniciar Sesion\n"
        << "[6] - Ver Jugador con mas victorias\n"
        << "[7] - Salir\n"
        << "Ingrese una opcion\n"
        << "=> ";

        std::string entrada;
        std::getline(std::cin, entrada);

        try {
            int opcion;
            opcion = std::stoi(entrada);

            if (opcion >= 1 && opcion <= 7) {
                switch (opcion) {
                    case 1:
                        if (!iniciarJuego()) {
                            std::cout << "\nUn jugador es invalido\n";
                        }
                    break;
                    case 2:
                        menuBarcos();
                    break;
                    case 3:
                        menuJugadores();
                    break;
                    case 4:
                        menuPiezas();
                    break;
                    case 5:
                        iniciarSesion();
                    break;
                    case 6:
                        mayorGanador();
                    break;
                    case 7:
                        std::cout << "Finalizando Juego...\n";
                        escrituraArchivos();
                        std::cout << "Juego finalizado con exito!\n";
                    return;
                }

            }else {
                std::cout << "Opcion incorrecta.\n\n";
            }
        } catch (...) {
            std::cout << "Opcion invalida.\n\n";
        }
    }
}

void Sistema::menuBarcos() {
    while (true) {
        std::cout
        << "\n***** MENU BARCOS *****\n"
        << "[1] - Crear un Barco\n"
        << "[2] - Ver todos los Barcos\n"
        << "[3] - Eliminar un Barco\n"
        << "[4] - Volver\n"
        << "Ingrese una opcion\n"
        << "=> ";

        std::string entrada;
        std::getline(std::cin, entrada);

        try {
            int opcion;
            opcion = std::stoi(entrada);

            if (opcion >= 1 && opcion <= 4) {
                switch (opcion) {
                    case 1:
                        if (crearBarco()) {
                            std::cout << "\nBarco creado con exito!\n";
                        } else {
                            std::cout << "\nEl barco no se puedo crear\n";
                        }
                    break;
                    case 2:
                        verBarcos();
                    break;
                    case 3:
                        if (eliminarBarco()) {
                            std::cout << "\nBarco eliminado con exito!\n";
                        } else {
                            std::cout << "\nEl barco no se puedo eliminar\n";
                        }
                    break;
                    case 4:
                        std::cout << "\n";
                        return;
                }

            }else {
                std::cout << "Opcion incorrecta.\n\n";
            }
        } catch (...) {
            std::cout << "Opcion invalida.\n\n";
        }
    }
}

bool Sistema::crearBarco() {
    std::string entrada;

    std::string nombre;
    int tamanio;
    std::string duenio;

    while (true) {
        std::cout
        << "\n***** AGREGAR BARCO *****\n"
        << "Ingrese el nombre del barco\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        nombre = entrada;
        break;
    }

    while (true) {
        std::cout
        << "\n***** AGREGAR BARCO *****\n"
        << "Ingrese el tamanio del barco\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        int numero;
        try {
            numero = std::stoi(entrada);
            if (numero < 1) {
                std::cout << "El tamanio del barco no puede ser inferior a 1\n";
                continue;
            }
        } catch (...) {
            std::cout << "Valor ingresado es incorrecto.\n\n";
            continue;
        }

        tamanio = numero;
        break;
    }

    while (true) {
        std::cout
        << "\n***** AGREGAR BARCO *****\n"
        << "Ingrese el duenio del barco\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";


        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        duenio = entrada;
        break;
    }

    while (true) {
        std::cout << "\n " << std::string(29, '*') << " AGREGAR BARCO " << std::string(28, '*') << "\n"
              << "|          Nombre          |     Tamanio     |           Duenio          |\n"
              << std::string(74, '-') << "\n"
              << "| " << std::left << std::setw(25) << nombre
              << "| " << std::setw(16) << tamanio
              << "| " << std::setw(26) << duenio << "|\n"
              << std::string(74, '-') << "\n"
              << "Presione enter para confirmar el barco. O ingrese [-1] para cancelar el barco.\n"
              << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }
        break;
    }

    return listaBarco->agregar(new Barco(nombre, tamanio, duenio, 0));
}

void Sistema::verBarcos() {
    if (listaBarco->isVacia()) {
        std::cout << "\nNo hay barcos almacenados\n";
        return;
    }
    NodoSimple<Barco>* aux = listaBarco->getHead();
    std::cout << "\n " << std::string(47, '*') << " VER TODOS LOS BARCOS " << std::string(46, '*') << "\n"
              << "|          Nombre          |     Tamanio     |           Duenio          |     Piezas Especiales     |     Slot     |\n"
              << std::string(117, '-') << "\n";
    while (aux != nullptr) {
        infoBarco(aux->getDato());
        aux = aux->getNext();
    }
}

void Sistema::infoBarco(Barco* barco) {
    std::cout << "| " << std::left << std::setw(25) << barco->getNombre()
                  << "| " << std::setw(16) << barco->getTamanio()
                  << "| " << std::setw(26) << barco->getDuenio();
    bool primera = true;
    for (int slot = 0; slot < barco->getTamanio(); ++slot) {
        if  (primera) {
            std::cout << "| " << std::left << std::setw(26);
            if (barco->getPiezasEspeciales()[slot] == "Coraza") {
                std::cout << "Vacio";
            } else {
                std::cout << barco->getPiezasEspeciales()[slot];
            }
            std::cout << "| " << std::left << std::setw(13) << slot << "|\n";
            primera = false;
            continue;
        }
        std::cout << "| " << std::right << std::setw(73) << "| " << std::left << std::setw(26);
        if (barco->getPiezasEspeciales()[slot] == "Coraza") {
            std::cout << "Vacio";
        } else {
            std::cout << barco->getPiezasEspeciales()[slot];
        }
        std::cout << "| " << std::left << std::setw(13) << slot << "|\n";
    }
    std::cout << std::string(117, '-') << "\n";
}

bool Sistema::eliminarBarco() {
    std::string entrada;

    std::string nombre;
    Barco* barco;

    while (true) {
        std::cout
        << "\n***** ELIMINAR BARCO *****\n"
        << "Ingrese el nombre del barco\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        nombre = entrada;
        std::cout << "Buscando...\n";
        NodoSimple<Barco>* aux = listaBarco->buscar(nombre);
        if (aux == nullptr) {
            std::cout << "No se encontro ninguna coincidencia con el nombre ingresado\n";
            continue;
        }
        barco = aux->getDato();
        break;
    }

    std::cout << "\n " << std::string(58, '*') << " ELIMINAR BARCO " << std::string(57, '*') << "\n"
              << "|          Nombre          |     Tamanio     |           Duenio          |     Piezas Especiales     |     Slot     |\n"
              << std::string(117, '-') << "\n";
    infoBarco(barco);
    std::cout << "Presione enter para confirmar la eliminacion del barco. O ingrese [-1] para cancelar.\n"
              << "=> ";

    std::getline(std::cin, entrada);
    if (entrada == "-1") {
        return false;
    }

    return listaBarco->eliminar(nombre);
}

void Sistema::menuJugadores() {
    while (true) {
        std::cout
        << "\n***** MENU JUGADORES *****\n"
        << "[1] - Crear un Jugador\n"
        << "[2] - Ver todos los Jugadores\n"
        << "[3] - Eliminar un Jugador\n"
        << "[4] - Volver\n"
        << "Ingrese una opcion\n"
        << "=> ";

        std::string entrada;
        std::getline(std::cin, entrada);

        try {
            int opcion;
            opcion = std::stoi(entrada);

            if (opcion >= 1 && opcion <= 4) {
                switch (opcion) {
                    case 1:
                        if (crearJugador()) {
                            std::cout << "\nJugador creado con exito!\n";
                        } else {
                            std::cout << "\nEl jugador no se puedo crear\n";
                        }
                    break;
                    case 2:
                        verJugadores();
                    break;
                    case 3:
                        if (eliminarJugador()) {
                            std::cout << "\nJugador eliminado con exito!\n";
                        } else {
                            std::cout << "\nEl jugador no se puedo eliminar\n";
                        }
                    break;
                    case 4:
                        std::cout << "\n";
                    return;
                }

            }else {
                std::cout << "Opcion incorrecta.\n\n";
            }
        } catch (...) {
            std::cout << "Opcion invalida.\n\n";
        }
    }
}

bool Sistema::crearJugador() {
    std::string entrada;

    std::string nombre;

    while (true) {
        std::cout
        << "\n***** CREAR JUGADOR *****\n"
        << "Ingrese el nombre del jugador\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        nombre = entrada;
        break;
    }

    return listaJugadores->agregar(new Jugador(nombre));
}

void Sistema::verJugadores() {
    if (listaJugadores->isVacia()) {
        std::cout << "\nNo hay jugadores almacenados\n";
        return;
    }
    NodoSimple<Jugador>* aux = listaJugadores->getHead();
    std::cout << "\n " << std::string(21, '*') << " VER TODOS LOS JUGADORES " << std::string(21, '*') << "\n"
              << "|          Nombre          |     Victorias     |     Derrotas     |\n"
              << std::string(67, '-') << "\n";
    do {
        infoJugador(aux->getDato());
        aux = aux->getNext();
    } while (aux != listaJugadores->getHead());
}

void Sistema::infoJugador(Jugador* jugador) {
    std::cout << "| " << std::left << std::setw(25) << jugador->getNombre()
                  << "| " << std::setw(18) << jugador->getCantidadVictorias()
                  << "| " << std::setw(17) << jugador->getCantidadDerrotas() << "|\n"
                  << std::string(67,'-') << "\n";
}

bool Sistema::eliminarJugador() {
    std::string entrada;

    std::string nombre;
    Jugador* jugador;

    while (true) {
        std::cout
        << "\n***** ELIMINAR JUGADOR *****\n"
        << "Ingrese el nombre del jugador\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";


        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        nombre = entrada;
        std::cout << "Buscando...\n";
        NodoSimple<Jugador>* aux = listaJugadores->buscar(nombre);
        if (aux == nullptr) {
            std::cout << "No se encontro ninguna coincidencia con el nombre ingresado\n";
            continue;
        }
        jugador = aux->getDato();
        break;
    }


    std::cout << "\n " << std::string(24, '*') << " ELIMINAR JUGADOR " << std::string(23, '*') << "\n"
              << "|          Nombre          |     Victorias     |     Derrotas     |\n"
              << std::string(67, '-') << "\n";
    infoJugador(jugador);
    std::cout << "Presione enter para confirmar la eliminacion del jugador. O ingrese [-1] para cancelar.\n"
              << "=> ";

    std::getline(std::cin, entrada);
    if (entrada == "-1") {
        return false;
    }

    return listaJugadores->eliminar(nombre);
}

void Sistema::menuPiezas() {
    while (true) {
        std::cout
        << "\n***** MENU PIEZAS *****\n"
        << "[1] - Crear una Pieza\n"
        << "[2] - Ver todas las Piezas\n"
        << "[3] - Eliminar una Pieza\n"
        << "[4] - Volver\n"
        << "Ingrese una opcion\n"
        << "=> ";

        std::string entrada;
        std::getline(std::cin, entrada);

        try {
            int opcion;
            opcion = std::stoi(entrada);

            if (opcion >= 1 && opcion <= 4) {
                switch (opcion) {
                    case 1:
                        if (crearPieza()) {
                            std::cout << "\nPieza creada con exito!\n";
                        } else {
                            std::cout << "\nLa pieza no se puedo crear\n";
                        }
                    break;
                    case 2:
                        verPiezas();
                    break;
                    case 3:
                        if (eliminarPieza()) {
                            std::cout << "\nPieza eliminado con exito!\n";
                        } else {
                            std::cout << "\nLa pieza no se puedo eliminar\n";
                        }
                    break;
                    case 4:
                        std::cout << "\n";
                    return;
                }

            }else {
                std::cout << "Opcion incorrecta.\n\n";
            }
        } catch (...) {
            std::cout << "Opcion invalida.\n\n";
        }
    }
}

bool Sistema::crearPieza() {
    std::string entrada;

    std::string tipo;
    std::string nombre;
    int salud;
    int potencia;

    while (true) {
        std::cout
        << "\n***** CREAR PIEZA *****\n"
        << "Seleccione el tipo de pieza ah crear\n"
        << "[1] - Misil Balistico\n"
        << "[2] - Metralla de alto calibre\n"
        << "[3] - Propulsor\n"
        << "[4] - Volver\n"
        << "Ingrese una opcion\n"
        << "=> ";

        std::getline(std::cin, entrada);

        try {
            int opcion;
            opcion = std::stoi(entrada);

            if (opcion >= 1 && opcion <= 4) {
                switch (opcion) {
                    case 1:
                        tipo = "Misil";
                    break;
                    case 2:
                        tipo = "Metralla";
                    break;
                    case 3:
                        tipo = "Propulsor";
                    break;
                    case 4:
                        return false;
                }
                break;
            }else {
                std::cout << "Opcion incorrecta.\n\n";
            }
        } catch (...) {
            std::cout << "Opcion invalida.\n\n";
        }
    }

    while (true) {
        std::cout
        << "\n***** CREAR PIEZA *****\n"
        << "Ingrese el nombre de la pieza\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        nombre = entrada;
        break;
    }

    while (true) {
        std::cout
        << "\n***** CREAR PIEZA *****\n"
        << "Ingrese la salud de la pieza\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        int numero;
        try {
            numero = std::stoi(entrada);
            if (numero < 1) {
                std::cout << "La salud de la pieza no puede ser inferior a 1\n";
                continue;
            }
        } catch (...) {
            std::cout << "Valor ingresado es incorrecto.\n\n";
            continue;
        }

        salud = numero;
        break;
    }

    while (true) {
        std::cout
        << "\n***** CREAR PIEZA *****\n"
        << "Ingrese la potencia de la pieza\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        int numero;
        try {
            numero = std::stoi(entrada);
            if (numero < 1) {
                std::cout << "La potencia de la pieza no puede ser inferior a 1\n";
                continue;
            }
        } catch (...) {
            std::cout << "Valor ingresado es incorrecto.\n\n";
            continue;
        }

        potencia = numero;
        break;
    }

    while (true) {
        std::cout << "\n " << std::string(36, '*') << " AGREGAR PIEZA " << std::string(35, '*') << "\n"
              << "|          Tipo          |          Nombre          |     Salud     |     Potencia     |\n"
              << std::string(88, '-') << "\n"
              << "| " << std::left << std::setw(23) << tipo
              << "| " << std::setw(25) << nombre
              << "| " << std::setw(14) << salud
              << "| " << std::setw(17) << potencia << "|\n"
              << std::string(88, '-') << "\n"
              << "Presione enter para confirmar la pieza. O ingrese [-1] para cancelar la pieza.\n"
              << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }
        break;
    }

    return listaPiezas->agregar(new Pieza(tipo, nombre, salud, potencia));
}

void Sistema::verPiezas() {
    if (listaPiezas->isVacia()) {
        std::cout << "\nNo hay piezas almacenadas\n";
        return;
    }
    NodoSimple<Pieza>* aux = listaPiezas->getHead();
    std::cout << "\n " << std::string(32, '*') << " VER TODAS LAS PIEZAS " << std::string(32, '*') << "\n"
              << "|          Tipo          |          Nombre          |     Salud     |     Potencia     |\n"
              << std::string(88, '-') << "\n";
    while (aux != nullptr) {
        infoPieza(aux->getDato());
        aux = aux->getNext();
    }
}

void Sistema::infoPieza(Pieza* pieza) {
    std::cout << "| " << std::left << std::setw(23) << pieza->getTipo()
                  << "| " << std::setw(25) << pieza->getNombre()
                  << "| " << std::setw(14) << pieza->getSalud()
                  << "| " << std::setw(17) << pieza->getPotencia() << "|\n"
                  << std::string(88, '-') << "\n";
}

bool Sistema::eliminarPieza() {
    std::string entrada;

    std::string nombre;
    Pieza* pieza;

    while (true) {
        std::cout
        << "\n***** ELIMINAR PIEZA *****\n"
        << "Ingrese el nombre de la pieza\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        nombre = entrada;
        std::cout << "Buscando...\n";
        NodoSimple<Pieza>* aux = listaPiezas->buscar(nombre);
        if (aux == nullptr) {
            std::cout << "No se encontro ninguna coincidencia con el nombre ingresado\n";
            continue;
        }
        pieza = aux->getDato();
        break;
    }

    std::cout << "\n " << std::string(35, '*') << " ELIMINAR PIEZA " << std::string(35, '*') << "\n"
              << "|          Tipo          |          Nombre          |     Salud     |     Potencia     |\n"
              << std::string(88, '-') << "\n";
    infoPieza(pieza);
    std::cout << "Presione enter para confirmar la eliminacion de la pieza. O ingrese [-1] para cancelar.\n"
              << "=> ";

    std::getline(std::cin, entrada);
    if (entrada == "-1") {
        return false;
    }

    NodoSimple<Barco>* aux = listaBarco->getHead();
    while (aux != nullptr) {
        Barco* barco = aux->getDato();
        for (int slot = 0; slot < barco->getTamanio(); ++slot) {
            if (barco->getPiezasEspeciales()[slot] == pieza->getNombre()) {
                quitarPieza(barco, slot);
            }
        }
        aux = aux->getNext();
    }

    return listaPiezas->eliminar(nombre);
}

void Sistema::iniciarSesion() {
    if (listaJugadores->isVacia()) {
        std::cout << "\nNo hay jugadores almacenados\n";
        return;
    }

    std::string entrada;
    Jugador* jugador = nullptr;
    NodoSimple<Barco>* aux = listaBarco->getHead();
    Barco* barco;
    while (true) {
        std::cout
        << "\n***** INICIAR SESION *****\n"
        << "Ingrese el nombre del jugador\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return;
        }

        NodoSimple<Jugador>* aux = listaJugadores->getHead();

        do {
            if (aux->getDato()->getNombre() == entrada) {
                jugador = aux->getDato();
                break;
            }
            aux = aux->getNext();
        }while (aux != listaJugadores->getHead());

        if (jugador == nullptr) {
            std::cout << "El jugador ingresado no existe.\n";
            continue;
        }

        break;
    }

    while (true) {
        std::cout
        << "\n***** BIENVENIDO " << jugador->getNombre() <<" *****\n"
        << "[1] - Ver mis barcos\n"
        << "[2] - Modificar un barco\n"
        << "[3] - Ver mis estadisticas\n"
        << "[4] - Salir\n"
        << "Ingrese una opcion\n"
        << "=> ";

        std::getline(std::cin, entrada);

        try {
            int opcion;
            opcion = std::stoi(entrada);

            if (opcion >= 1 && opcion <= 4) {
                switch (opcion) {
                    case 1: {
                        if (listaBarco->isVacia()) {
                            std::cout << "\nNo hay barcos almacenados\n";
                            return;
                        }

                        std::cout << "\n " << std::string(47, '*') << " VER TODOS LOS BARCOS " << std::string(46, '*') << "\n"
                                  << "|          Nombre          |     Tamanio     |           Duenio          |     Piezas Especiales     |     Slot     |\n"
                                  << std::string(117, '-') << "\n";
                        bool tieneBarco = false;
                        while (aux != nullptr) {
                            if (aux->getDato()->getDuenio() == jugador->getNombre()) {
                                infoBarco(aux->getDato());
                                tieneBarco = true;
                            }
                            aux = aux->getNext();
                        }

                        if (!tieneBarco) {
                            std::cout << "\nUsted no posee ningun barco\n";
                        }
                        break;
                    }
                    case 2: {
                        while (true) {
                            std::cout
                            << "\n***** MODIFICAR BARCO *****\n"
                            << "Ingrese el nombre del barco"
                            << "o ingrese [-1] para volver\n"
                            << "=> ";

                            std::getline(std::cin, entrada);
                            if (entrada == "-1") {
                                break;;
                            }

                            aux = listaBarco->buscar(entrada);
                            if (aux == nullptr) {
                                std::cout << "El barco ingresado no existe\n";
                                continue;
                            }

                            if (aux->getDato()->getDuenio() != jugador->getNombre()) {
                                std::cout << "Usted no es el duenio del barco\n";
                                continue;
                            }

                            barco = aux->getDato();
                            modificarBarco(barco);
                            break;
                        }
                        break;
                    }
                    case 3: {
                        std::cout
                        << "\n***** ESTADISTICAS *****\n"
                        << "Victorias: " << jugador->getCantidadVictorias() << ".\n"
                        << "Derrotas : " << jugador->getCantidadDerrotas() << ".\n";
                        break;
                    }
                    case 4: {
                        std::cout << "\n";
                        return;
                    }
                }

            }else {
                std::cout << "Opcion incorrecta.\n\n";
            }
        } catch (...) {
            std::cout << "Opcion invalida.\n\n";
        }
    }
}

void Sistema::modificarBarco(Barco* barco) {
    while (true) {
        std::cout << "\n " << std::string(54, '*') << " BARCO " << std::string(54, '*') << "\n"
              << "|          Nombre          |     Tamanio     |           Duenio          |     Piezas Especiales     |     Slot     |\n"
              << std::string(117, '-') << "\n";
    infoBarco(barco);
    std::cout
        << "[1] - Agregar Pieza\n"
        << "[2] - Quitar Pieza\n"
        << "[3] - Salir\n"
        << "Ingrese una opcion\n"
        << "=> ";

    std::string entrada;
    std::getline(std::cin, entrada);

    try {
            int opcion;
            opcion = std::stoi(entrada);

            if (opcion >= 1 && opcion <= 3) {
                std::string nombre;
                int slot;
                switch (opcion) {
                    case 1:
                        std::cout << "Ingrese el nombre de la pieza\n"
                                  << "=> ";

                        std::getline(std::cin, nombre);

                        while (true) {
                            std::cout << "Ingrese el slot para la pieza (debe seleccionar un slot Vacio)\n"
                                      << "=> ";

                            std::getline(std::cin, entrada);
                            try {
                                slot = std::stoi(entrada);
                                break;
                            }catch (...) {
                                std::cout << "Valor invalido!\n";
                            }
                        }

                        if (agregarPieza(barco, nombre, slot)) {
                            std::cout << "Pieza agregado con exito!\n";
                        } else {
                            std::cout << "El nombre de la pieza no existe o ingreso un slot invalido\n";
                        }
                    break;
                    case 2:
                        while (true) {
                            std::cout << "Ingrese el slot de la pieza\n"
                                      << "=> ";
                            std::getline(std::cin, entrada);
                            try {
                                slot = std::stoi(entrada);
                                break;
                            }catch (...) {
                                std::cout << "Valor invalido!\n";
                            }
                        }

                        if (quitarPieza(barco, slot)) {
                            std::cout << "Pieza quitada con exito!\n";
                        } else {
                            std::cout << "Slot invalido o ya se encuentra vacio\n";
                        }
                    break;
                    case 3:
                        std::cout << "\n";
                        return;
                }

            }else {
                std::cout << "Opcion incorrecta.\n\n";
            }
        } catch (...) {
            std::cout << "Opcion invalida.\n\n";
        }
    }
}

bool Sistema::agregarPieza(Barco* barco, std::string nombrePieza, int slot) {
    if (slot >= barco->getTamanio()) {
        return false;
    }
    if (barco->getPiezasEspeciales()[slot] != "Coraza") {
        return false;
    }
    NodoSimple<Pieza>* aux = listaPiezas->buscar(nombrePieza);
    if (aux == nullptr) {
        return false;
    }

    barco->getPiezasEspeciales()[slot] = nombrePieza;
    barco->setCantidadPiezasEspeciales(barco->getCantidadPiezasEspeciales() +1);
    return true;
}

bool Sistema::quitarPieza(Barco *barco, int slot) {
    if (slot >= barco->getTamanio()) {
        return false;
    }
    if (barco->getPiezasEspeciales()[slot] == "Coraza") {
        return false;
    }

    barco->getPiezasEspeciales()[slot] = "Coraza";
    barco->setCantidadPiezasEspeciales(barco->getCantidadPiezasEspeciales() -1);
    return true;
}

bool Sistema::iniciarJuego() {
    std::string entrada;

    std::string nombre;
    NodoSimple<Jugador>* aux;

    while (true) {
        std::cout
        << "\n***** INICIAR JUEGO *****\n"
        << "Ingrese el nombre del primer jugador\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";


        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        nombre = entrada;
        aux = listaJugadores->buscar(nombre);
        if (aux == nullptr) {
            return false;
        }
        jugador1 = aux->getDato();
        break;
    }

    while (true) {
        std::cout
        << "\n***** INICIAR JUEGO *****\n"
        << "Ingrese el nombre del segundo jugador\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";


        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        nombre = entrada;
        aux = listaJugadores->buscar(nombre);
        if (aux == nullptr) {
            return false;
        }

        if (jugador1->getNombre() == nombre) {
            std::cout << "El jugador ya fue elejido\n";
            continue;
        }
        jugador2 = aux->getDato();
        break;
    }

    menuJuego(jugador1, jugador2);
    return true;
}

void Sistema::menuJuego(Jugador* jugador1, Jugador* jugador2) {
    Barco* barco1;
    bool barcoJugador1 = false;
    Barco* barco2;
    bool barcoJugador2 = false;
    while (true) {
        std::cout
        << "\n***** MENU JUEGO *****\n"
        << "[1] - Iniciar Partida\n"
        << "[2] - Seleccionar Barcos Jugador 1\n"
        << "[3] - Seleccionar Barcos Jugador 2\n"
        << "[4] - Salir\n"
        << "Ingrese una opcion\n"
        << "=> ";

        std::string entrada;
        std::getline(std::cin, entrada);

        try {
            int opcion;
            opcion = std::stoi(entrada);

            if (opcion >= 1 && opcion <= 4) {
                switch (opcion) {
                    case 1:
                        if (barcoJugador1 && barcoJugador2) {
                            while (true) {
                                std::cout << "Ingrese el tamanio del tablero (Solo se puede numeros impares y superiores a 5)\n"
                                          << "o ingrese [-1] para volver\n"
                                          << "=> ";
                                std::getline(std::cin, entrada);
                                if (entrada == "-1") {
                                    break;
                                }
                                int tamanio = std::stoi(entrada);
                                if (tamanio >= 5 && tamanio % 3 != 0) {
                                    iniciarPartida(tamanio, barco1, barco2);
                                    break;
                                } else {
                                    std::cout << "Tamanio del tablero incorrecto\n";
                                }
                            }
                        } else {
                            if (!barcoJugador1) {
                                std::cout << "No ah selecionado el barco para el Jugador 1!\n";
                            }
                            if (!barcoJugador2) {
                                std::cout << "No ah selecionado el barco para el Jugador 2!\n";
                            }
                        }
                    break;
                    case 2:
                        barco1 = seleccionarBarco(jugador1);
                        if (barco1 != nullptr) {
                            barcoJugador1 = true;
                        }
                    break;
                    case 3:
                        barco2 = seleccionarBarco(jugador2);
                    if (barco2 != nullptr) {
                        barcoJugador2 = true;
                    }
                    break;
                    case 4:
                        std::cout << "\n";
                    return;
                }

            }else {
                std::cout << "Opcion incorrecta.\n\n";
            }
        } catch (...) {
            std::cout << "Opcion invalida.\n\n";
        }
    }
}

Barco* Sistema::seleccionarBarco(Jugador* jugador) {
    if (listaBarco->isVacia()) {
        std::cout << "\nNo hay barcos almacenados\n";
        return nullptr;
    }

    std::cout << "\nCargando...\n";
    NodoSimple<Barco>* aux = listaBarco->getHead();
    std::cout << "\n " << std::string(54, '*') << " BARCOS " << std::string(53, '*') << "\n"
              << "|          Nombre          |     Tamanio     |           Duenio          |     Piezas Especiales     |     Slot     |\n"
              << std::string(117, '-') << "\n";
    bool poseeBarco = false;
    while (aux != nullptr) {
        if (aux->getDato()->getDuenio() == jugador->getNombre()) {
            infoBarco(aux->getDato());
            poseeBarco = true;
        }
        aux = aux->getNext();
    }
    if (!poseeBarco) {
        std::cout << "\nEl jugador [" << jugador->getNombre() << "] no posee barcos.\n";
        return nullptr;
    }

    while (true) {
        std::cout
        << "Ingrese el nombre del barco a seleccionar\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::string entrada;
        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return nullptr;
        }

        std::cout << "Buscando...\n";
        NodoSimple<Barco>* aux = listaBarco->buscar(entrada);
        if (aux == nullptr) {
            std::cout << "No se encontro ninguna coincidencia con el nombre ingresado\n\n";
            continue;
        }
        std::cout << "Barco seleccionado con exito!\n";
        return aux->getDato();
    }
}

bool Sistema::verificadorCoordenadas(std::string coordenadas, int* pX, int* pY) {
    size_t coma = coordenadas.find(',');
    if (coma == std::string::npos) {
        std::cout << "Formato incorrecto.\n";
        return false;
    }

    std::string parteX = coordenadas.substr(0, coma);
    std::string parteY = coordenadas.substr(coma + 1);

    try {
        *pX = std::stoi(parteX);
        *pY = std::stoi(parteY);
    } catch (...) {
        std::cout << "Formato incorrecto.\n";
        return false;
    }

    return true;
}

void Sistema::agregarBarco(Barco* barco, int coordenadaX, int coordenadaY) {
    for (int slot = 0; slot < barco->getTamanio(); ++slot) {
        if (barco->getPiezasEspeciales()[slot] == "Coraza") {
            mpp->agregar(coordenadaX + slot, coordenadaY, new Pieza());
            continue;
        }
        Pieza* pieza = listaPiezas->buscar(barco->getPiezasEspeciales()[slot])->getDato()->clone();
        mpp->agregar(coordenadaX + slot, coordenadaY, pieza);
    }
}

void Sistema::iniciarPartida(int tamanio, Barco* barco1, Barco* barco2) {
    std::string entrada;
    int coordenadaX;
    int coordenadaY;

    while (true) {
        std::cout
        << "\n***** JUEGO *****\n"
        << "Ingrese las coordenadas del barco para el jugador 1\n"
        << "Formato [X,Y] X=Longitud, Y=Latitud (Ejemplo: 3,2)"
        << "Y deben ser entre: [1,1] y [" << tamanio << "," << tamanio/2 << "]\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return;
        }

        if (verificadorCoordenadas(entrada, &coordenadaX, &coordenadaY)) {
            if (!(coordenadaX > 0 && coordenadaX <= tamanio && coordenadaY > 0 && coordenadaY <= tamanio/2)) {
                std::cout << "Las coordenadas ingresadas son invalidas dentro de su espacio del tablero. Deben ser entre: [1,1] y ["
                  << tamanio << "," << tamanio/2 << "]\n";
                continue;
            }

            if (coordenadaX - barco1->getTamanio() +1 < tamanio) {
                cabezeraXJugador1 = coordenadaX;
                cabezeraYJugador1 = coordenadaY;
                break;
            }

            std::cout << "La coordenada ingresada proboca que el barco salga de los limites del tablero.\n";
        }
    }

    while (true) {
        std::cout
        << "\n***** JUEGO *****\n"
        << "Ingrese las coordenadas del barco para el jugador 2\n"
        << "Formato [X,Y] X=Longitud, Y=Latitud (Ejemplo: 3,2)"
        << "Y Deben ser entre: [1," << (tamanio/2) +2 << "] y [" << tamanio << "," << tamanio << "]\n"
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return;
        }

        if (verificadorCoordenadas(entrada, &coordenadaX, &coordenadaY)) {
            if (!(coordenadaX > 0 && coordenadaX <= tamanio && coordenadaY > tamanio/2 +1 && coordenadaY <= tamanio)) {
                std::cout << "Las coordenadas ingresadas son invalidas dentro del espacio del tablero. Deben ser entre: [1,"
                          << (tamanio/2) +2 << "] y [" << tamanio << "," << tamanio << "]\n";
                continue;
            }

            if (coordenadaX - barco2->getTamanio() +1 < tamanio) {
                cabezeraXJugador2 = coordenadaX;
                cabezeraYJugador2 = coordenadaY;
                break;
            }

            std::cout << "La coordenada ingresada proboca que el barco salga de los limites del tablero.\n";
        }
    }
    this->mpp = new MPP(tamanio, tamanio);

    agregarBarco(barco1, cabezeraXJugador1, cabezeraYJugador1);
    this->barco1 = barco1;
    agregarBarco(barco2, cabezeraXJugador2, cabezeraYJugador2);
    this->barco2 = barco2;

    juego();
    delete this->mpp;
}

void Sistema::juego() {
    bool turno = true; // Si true jugador 1, si false jugador 2

    while (true) {
        if (turno) {
            if (!verificarEstadoPiezas(turno)) {
                std::cout << "El jugador 1 se a quedado sin piezas con salud. La victoria es para el jugador 2!\n";
                jugador1->sumarDerrota();
                jugador2->sumarVictoria();
                return;
            }
            while (true) {
                std::cout
                << "\n***** JUEGO *****\n"
                << "Jugador 1 seleccione su accion.\n"
                << "[1] - Disparar\n"
                << "[2] - Mover barco\n"
                << "[3] - Rendirse\n"
                << "Ingrese una opcion\n"
                << "=> ";

                std::string entrada;
                std::getline(std::cin, entrada);

                try {
                    int opcion;
                    opcion = std::stoi(entrada);

                    if (opcion >= 1 && opcion <= 3) {
                        switch (opcion) {
                            case 1:
                                if (!disparar(turno)) {
                                    continue;
                                }
                                turno = false;
                            break;
                            case 2:
                                if (!mover(turno)) {
                                    continue;
                                }
                                turno = false;
                            break;
                            case 3:
                                std::cout << "El jugador 1 se a rendido. La victoria es para el jugador 2!\n";
                                jugador1->sumarDerrota();
                                jugador2->sumarVictoria();
                            return;
                        }

                    }else {
                        std::cout << "Opcion incorrecta.\n\n";
                    }
                } catch (...) {
                    std::cout << "Opcion invalida.\n\n";
                }
                break;
            }
        } else {
            if (!verificarEstadoPiezas(turno)) {
                std::cout << "El jugador 2 se a quedado sin piezas con salud. La victoria es para el jugador 1!\n";
                jugador2->sumarDerrota();
                jugador1->sumarVictoria();
                return;
            }
            while (true) {
                std::cout
                << "\n***** JUEGO *****\n"
                << "Jugador 2 seleccione su accion.\n"
                << "[1] - Disparar\n"
                << "[2] - Mover barco\n"
                << "[3] - Rendirse\n"
                << "Ingrese una opcion\n"
                << "=> ";

                std::string entrada;
                std::getline(std::cin, entrada);

                try {
                    int opcion;
                    opcion = std::stoi(entrada);

                    if (opcion >= 1 && opcion <= 3) {
                        switch (opcion) {
                            case 1:
                                if (!disparar(turno)) {
                                    continue;
                                }
                                turno = true;
                            break;
                            case 2:
                                if (!mover(turno)) {
                                    continue;
                                }
                                turno = true;
                            break;
                            case 3:
                                std::cout << "El jugador 2 se a rendido. La victoria es para el jugador 1!\n";
                            jugador2->sumarDerrota();
                            jugador1->sumarVictoria();
                            return;
                        }

                    }else {
                        std::cout << "Opcion incorrecta.\n\n";
                    }
                } catch (...) {
                    std::cout << "Opcion invalida.\n\n";
                }
                break;
            }
        }
    }
}

bool Sistema::verificarEstadoPiezas(bool turno) {
    int x, y;
    if (turno) {
        x = cabezeraXJugador1;
        y = cabezeraYJugador1;
    } else {
        x = cabezeraXJugador2;
        y = cabezeraYJugador2;
    }

    NodoMPP* aux = mpp->buscar(x, y)->getUp()->getUp();
    do {
        if (aux->getPieza()->getSalud() != 0) {
            return true; //Aun hay piezas con salud
        }
        aux = aux->getUp();
    }while (aux->getUp()->getFila() == x);
    return false; //No quedan piezas con salud
}

bool Sistema::verificarPotencia(int potencia, int coordenadaX, int coordenadaY, int nuevaCoordenadaX, int nuevaCoordenadaY) {
    int x = coordenadaX - nuevaCoordenadaX;
    x *= x;
    int y = coordenadaY - nuevaCoordenadaY;
    y *= y;
    int raizEntera  = static_cast<int>(sqrt(x + y));
    if (potencia < raizEntera) {
        return false;
    }
    return true;
}

bool Sistema::mover(bool turno) {
    std::string entrada;
    int coordenadaX;
    int coordenadaY;

    while (true) {
        std::cout
        << "\n***** JUEGO *****\n"
        << "Ingrese las nuevas coordenadas para la posicion del barco\n"
        << "Formato [X,Y] X=Longitud, Y=Latitud (Ejemplo: 3,2)";
        if (turno) {
            std::cout << "Y deben ser entre: [1,1] y [" << mpp->getAlto() << "," << mpp->getLargo()/2 << "]\n";
        } else {
            std::cout << "Y deben ser entre: [1," << mpp->getLargo()/2+2 <<"] y [" << mpp->getAlto() << "," << mpp->getLargo() << "]\n";
        }
        std::cout
        << "o ingrese [-1] para volver\n"
        << "=> ";

        std::getline(std::cin, entrada);
        if (entrada == "-1") {
            return false;
        }

        if (verificadorCoordenadas(entrada, &coordenadaX, &coordenadaY)) {
            if (turno) {
                if (!(coordenadaX > 0 && coordenadaX <= mpp->getAlto() && coordenadaY > 0 && coordenadaY <= mpp->getLargo()/2)) {
                    std::cout << "Las coordenadas ingresadas son invalidas dentro de su espacio del tablero. Deben ser entre: [1,1] y ["
                              << mpp->getAlto() << "," << mpp->getLargo()/2 << "]\n";
                    continue;
                }

                if (coordenadaX - barco1->getTamanio() +1 < mpp->getAlto()) {
                    int potencia = 0;
                    NodoMPP* aux = mpp->buscar(cabezeraXJugador1, cabezeraYJugador1)->getUp()->getUp();
                    do {
                        if (aux->getPieza()->getTipo() == "Propulsor" && aux->getPieza()->getSalud() > 0) {
                            potencia += aux->getPieza()->getPotencia();
                        }
                        aux = aux->getUp();
                    } while (aux != mpp->buscar(cabezeraXJugador1, cabezeraYJugador1));
                    if (aux->getPieza()->getTipo() == "Propulsor" && aux->getPieza()->getSalud() > 0) {
                        potencia += aux->getPieza()->getPotencia();
                    }

                    if (!verificarPotencia(potencia, cabezeraXJugador1, cabezeraYJugador1, coordenadaX, coordenadaY)) {
                        std::cout << "La potencia no es suficiente para moverse a las nuevas coordenadas!\n";
                        continue;
                    }

                    aux = mpp->buscar(cabezeraXJugador1, cabezeraYJugador1)->getUp()->getUp(); //Obtiene el final del barco
                    for (int i = barco1->getTamanio()-1; i >= 0; --i) {
                        NodoMPP* temp = aux;
                        aux = aux->getUp();
                        mpp->mover(aux->getFila(), aux->getColumna(), coordenadaX+i, coordenadaY);
                    }

                    return true;
                }
            } else {
                if (!(coordenadaX > 0 && coordenadaX <= mpp->getAlto() && coordenadaY > mpp->getLargo()/2 +1 && coordenadaY <= mpp->getLargo())) {
                    std::cout << "Las coordenadas ingresadas son invalidas dentro de su espacio del tablero. Deben ser entre: [1,"
                      << mpp->getLargo()/2 +2 << "] y [" << mpp->getAlto() << ", " << mpp->getLargo() <<"]\n";
                    continue;
                }

                if (coordenadaX - barco2->getTamanio() +1 < mpp->getAlto()) {
                    int potencia = 0;
                    NodoMPP* aux = mpp->buscar(cabezeraXJugador2, cabezeraYJugador2)->getUp()->getUp();
                    do {
                        if (aux->getPieza()->getTipo() == "Propulsor" && aux->getPieza()->getSalud() > 0) {
                            potencia += aux->getPieza()->getPotencia();
                        }
                        aux = aux->getUp();
                    } while (aux != mpp->buscar(cabezeraXJugador2, cabezeraYJugador2));
                    if (aux->getPieza()->getTipo() == "Propulsor" && aux->getPieza()->getSalud() > 0) {
                        potencia += aux->getPieza()->getPotencia();
                    }

                    if (!verificarPotencia(potencia, cabezeraXJugador2, cabezeraYJugador2, coordenadaX, coordenadaY)) {
                        std::cout << "La potencia no es suficiente para moverse a las nuevas coordenadas!\n";
                        continue;
                    }

                    aux = mpp->buscar(cabezeraXJugador2, cabezeraYJugador2)->getUp()->getUp(); //Obtiene el final del barco
                    for (int i = barco2->getTamanio()-1; i >= 0; --i) {
                        NodoMPP* temp = aux;
                        aux = aux->getUp();
                        mpp->mover(aux->getFila(), aux->getColumna(), coordenadaX+i, coordenadaY);
                    }

                    return true;
                }
            }

            std::cout << "La coordenada ingresada proboca que el barco salga de los limites del tablero.\n";
        }
    }
}

bool Sistema::disparar(bool turno) {
    while (true) {
        std::cout
            << "\n***** JUEGO *****\n"
            << "Ingrese el slot a disparar\n"
            << "o ingrese [-1] para volver.\n"
            << "=> ";

        std::string entrada;
        std::getline(std::cin, entrada);

        if (entrada == "-1") {
            return false;
        }

        int opcion = 0;
        try {
            opcion = std::stoi(entrada);
        } catch (...) {
            std::cout << "Opcion invalida.\n\n";
            continue;
        }

        NodoMPP* slot;
            if (turno) {
                opcion += cabezeraXJugador1;
                slot = mpp->buscar(opcion, cabezeraYJugador1);
            } else {
                opcion += cabezeraXJugador2;
                slot = mpp->buscar(opcion, cabezeraYJugador2);
            }

            if (!slot) {
                std::cout << "Slot invalido!\n";
                continue;
            }

            if (slot->getPieza()->getTipo() == "Coraza") {
                std::cout << "El slot esta vacio\n";
                continue;
            }

            if (slot->getPieza()->getTipo() == "Propulsor") {
                std::cout << "El slot es un propulsor\n";
                continue;
            }

            if (slot->getPieza()->getTipo() == "Misil") {
                if (slot->getPieza()->getSalud() <= 0) {
                    std::cout << "La pieza esta destruida\n";
                    continue;
                }
                while (true) {
                    std::cout
                    << "\n***** MISIL *****\n"
                    << "Ingrese las coordenadas para el impacto del misil\n"
                    << "Formato [X,Y] X=Longitud, Y=Latitud (Ejemplo: 3,2)\n"
                    << "o ingrese [-1] para volver\n"
                    << "=> ";

                    std::getline(std::cin, entrada);
                    if (entrada == "-1") {
                        break;
                    }

                    int coordenadaX, coordenadaY;

                    if (verificadorCoordenadas(entrada, &coordenadaX, &coordenadaY)) {
                        if (coordenadaX < 0 || coordenadaX > mpp->getAlto() ||
                            coordenadaY < 0 || coordenadaY > mpp->getLargo()) {
                            std::cout << "Las coordenadas se salen de los limites!\n";
                            continue;
                        }

                        misil(coordenadaX, coordenadaY, slot->getPieza()->getPotencia());
                        return true;
                    }
                }
            }

            if (slot->getPieza()->getTipo() == "Metralla") {
                if (slot->getPieza()->getSalud() <= 0) {
                    std::cout << "La pieza esta destruida\n";
                    continue;
                }
                while (true) {
                    std::cout
                    << "\n***** METRALLA *****\n"
                    << "Ingrese el angulo con el que se dispara la metralla\n"
                    << "Debe ser entre 0 y 90 grados\n"
                    << "o ingrese [-1] para volver\n"
                    << "=> ";

                    std::getline(std::cin, entrada);
                    if (entrada == "-1") {
                        break;
                    }

                    int angulo;
                    try {
                        angulo = std::stoi(entrada);
                    } catch (...) {
                        std::cout << "Opcion invalida.\n\n";
                        continue;
                    }

                    if (angulo < 0 || angulo > 90) {
                        std::cout << "El angulo incorrecto\n";
                        continue;
                    }
                    metralla(turno, angulo, slot->getPieza()->getPotencia(), slot->getFila(), slot->getColumna());
                    return true;
                    }
                }

        std::cout << "Slot invalido.\n\n";
    }
}

void Sistema::misil(int coordenadaX, int coordenadaY, int potencia) {
    std::set<NodoMPP*> nodoAfectados;

    //Comprueba si las coordenadas ingresadas están en los límites de la matriz
    if (coordenadaX < 0 || coordenadaY < 0 ||
        coordenadaX > mpp->getLargo() || coordenadaY > mpp->getAlto()) {
        std::cout << "Posicion fuera del rango.\n";
        return;
    }

    // Comprueba el nodo central
    NodoMPP* nodoCentral = mpp->buscar(coordenadaX, coordenadaY);
    if (nodoCentral) {
        nodoAfectados.insert(nodoCentral);
    }

    //Comprueba el resto de nodos en cruz segun la potencia
    for (int i = 1; i <= potencia; i++) {
        //Arriab
        if (coordenadaX - i >= 0) {
            NodoMPP* nodo = mpp->buscar(coordenadaX - i, coordenadaY);
            if (nodo) {
                nodoAfectados.insert(nodo);
            }
        }

        //Abajo
        if (coordenadaX + i < mpp->getLargo()) {
            NodoMPP* nodo = mpp->buscar(coordenadaX + i, coordenadaY);
            if (nodo) {
                nodoAfectados.insert(nodo);
            }
        }

        //Izquierda
        if (coordenadaY - i >= 0) {
            NodoMPP* nodo = mpp->buscar(coordenadaX, coordenadaY - i);
            if (nodo) {
                nodoAfectados.insert(nodo);
            }
        }

        //Derecha
        if (coordenadaY + i < mpp->getAlto()) {
            NodoMPP* nodo = mpp->buscar(coordenadaX, coordenadaY + i);
            if (nodo) {
                nodoAfectados.insert(nodo);
            }
        }

        //Aplica el danio a los nodos afectados
        for (NodoMPP* nodo : nodoAfectados) {
            std::cout << "Impacto en las coordenadas [" << nodo->getFila() << "," << nodo->getColumna() << "]!!!\n";
            nodo->getPieza()->setSalud(nodo->getPieza()->getSalud() - 1);
            if (nodo->getPieza()->getSalud() < 0) {
                nodo->getPieza()->setSalud(0);
            }
        }
    }
}

void Sistema::metralla(bool turno, int angulo, int potencia, int coordenadaX, int coordenadaY) {
    double radianes = angulo * M_PI / 180.0;
    double catetoBase = 0;
    double catetoAlto = 0;

    if (turno) {
        catetoBase = cabezeraYJugador2 - coordenadaY;
    } else {
        catetoBase = coordenadaY - cabezeraYJugador1;
    }

    catetoAlto = tan(radianes) * catetoBase;

    NodoMPP* aux;
    if (turno) {
        aux = mpp->buscar(cabezeraXJugador2, cabezeraYJugador2)->getUp()->getUp();
    } else {
        aux = mpp->buscar(cabezeraXJugador1, cabezeraYJugador1)->getUp()->getUp();
    }

    while (aux->getFila() != 0) {
        if (coordenadaX - catetoAlto <= aux->getFila() +0.5 && coordenadaX - catetoAlto > aux->getFila() -0.5) {
            if (catetoBase / cos(radianes) <= potencia) {
                aux->getPieza()->setSalud(aux->getPieza()->getSalud() - 1);
                std::cout << "Impacto en las coordenadas: [" << aux->getFila() << "," << aux->getColumna() << "]!!!\n";
                return;
            }
            break;
        }
        aux = aux->getUp();
    }
    std::cout << "El disparo fallo!\n";
}

void Sistema::mayorGanador() {
    NodoSimple<Jugador>* aux = listaJugadores->getHead();
    std::string nombreJugadorMasVictorias = "";
    int cantidadVictorias = 0;

    do {
        if (aux->getDato()->getCantidadVictorias() > cantidadVictorias) {
            nombreJugadorMasVictorias = aux->getDato()->getNombre();
            cantidadVictorias = aux->getDato()->getCantidadVictorias();
        }
        aux = aux->getNext();
    } while (aux != listaJugadores->getHead());

    std::cout
    << "***** JUGADOR CON MAS VICTORIAS *****\n"
    << nombreJugadorMasVictorias << ", con: " << cantidadVictorias << " victorias.\n";
}

Sistema::~Sistema() {
    delete this->listaPiezas;
    delete this->listaJugadores;
}