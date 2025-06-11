#pragma once
#include "../Model/Contenedores/ListaCircularSimple.h"
#include "../Model/Contenedores/ListaSimple.h"
#include "../Model/Contenedores/MPP.h"
#include "../Model/Barco.h"
#include "../Model/Jugador.h"
#include "../Model/Pieza.h"

/**
 * @class Sistema
 *
 * @brief Contiene la logica del juego, incluyendo la gestion de jugadores, barcos, piezas y la dinamica de juego.
 */
class Sistema {
private:
    ListaCircularSimple* listaJugadores;      // Lista circular de jugadores.
    ListaSimple<Pieza>* listaPiezas;          // Lista simple de piezas disponibles.
    ListaSimple<Barco>* listaBarco;           // Lista simple de barcos.
    MPP* mpp;                                 // Matriz principal del juego.
    Jugador* jugador1;                        // Jugador 1.
    Barco* barco1;                            // Barco seleccionado por el jugador 1.
    int cabezeraXJugador1, cabezeraYJugador1; // Coordenadas iniciales del barco del jugador 1.
    Jugador* jugador2;                        // Jugador 2.
    Barco* barco2;                            // Barco seleccionado por el jugador 2.
    int cabezeraXJugador2, cabezeraYJugador2; // Coordenadas iniciales del barco del jugador 2.

public:
    /**
     * @brief Constructor por defecto. Inicializa el sistema.
     */
    Sistema();

    /**
     * @brief Verifica si un archivo existe y esta accesible.
     *
     * @param nombreArchivo Nombre del archivo.
     *
     * @return true Si el archivo es valido.
     * @return false Si el archivo no existe o no puede abrirse.
     */
    bool verificadorArchivos(std::string nombreArchivo);

    /**
     * @brief Lee los datos desde los archivos.
     *
     * Almacena los datos leidos en sus respectivas listas.
     */
    void lecturaArchivos();

    /**
     * @brief Escribe los datos a los archivos.
     *
     * Sobreescribe los archivos existentes con los nuevos datos almacenados en las listas.
     */
    void escrituraArchivos();

    /**
     * @brief Muestra el menu principal del sistema.
     */
    void menuPrincipal();

    /**
     * @brief Muestra el menu para gestionar los barcos.
     */
    void menuBarcos();

    /**
     * @brief Crea un nuevo barco.
     *
     * @return true Si se creo correctamente.
     * @return false Si hubo un error.
     */
    bool crearBarco();

    /**
     * @brief Muestra todos los barcos almacenados.
     */
    void verBarcos();

    /**
     * @brief Muestra la informacion de un barco.
     *
     * @param barco Puntero al barco a mostrar.
     */
    void infoBarco(Barco* barco);

    /**
     * @brief Elimina un barco por nombre.
     *
     * @return true Si se elimino correctamente.
     * @return false Si no se encontro el barco.
     */
    bool eliminarBarco();

    /**
     * @brief Muestra el menu para gestionar los jugadores.
     */
    void menuJugadores();

    /**
     * @brief Crea un nuevo jugador.
     *
     * @return true Si se creo correctamente.
     * @return false Si hubo un error.
     */
    bool crearJugador();

    /**
     * @brief Muestra todos los jugadores.
     */
    void verJugadores();

    /**
     * @brief Muestra la informacion de un jugador.
     *
     * @param jugador Puntero al jugador.
     */
    void infoJugador(Jugador* jugador);

    /**
     * @brief Elimina un jugador por nombre.
     *
     * @return true Si se elimino correctamente.
     * @return false Si no se encontro el jugador.
     */
    bool eliminarJugador();

    /**
     * @brief Muestra el menu para gestionar las piezas.
     */
    void menuPiezas();

    /**
     * @brief Crea una nueva pieza.
     *
     * @return true Si se creo correctamente.
     * @return false Si hubo un error.
     */
    bool crearPieza();

    /**
     * @brief Muestra todas las piezas.
     */
    void verPiezas();

    /**
     * @brief Muestra la informacion de una pieza.
     *
     * @param pieza Puntero a la pieza.
     */
    void infoPieza(Pieza* pieza);

    /**
     * @brief Elimina una pieza por nombre.
     *
     * @return true Si se elimino correctamente.
     * @return false Si no se encontro la pieza.
     */
    bool eliminarPieza();

    /**
     * @brief Inicia sesion con un jugador.
     */
    void iniciarSesion();

    /**
     * @brief Permite modificar un barco existente.
     *
     * @param barco Puntero al barco a modificar.
     */
    void modificarBarco(Barco* barco);

    /**
     * @brief Agrega una pieza a un barco.
     *
     * @param barco Barco al cual se agrega.
     * @param nombrePieza Nombre de la pieza a agregar.
     * @param slot Posicion en el array donde se colocara la pieza.
     *
     * @return true Si se agrego correctamente.
     * @return false Si hubo un error.
     */
    bool agregarPieza(Barco* barco, std::string nombrePieza, int slot);

    /**
     * @brief Quita una pieza de un barco.
     *
     * @param barco Barco al cual se le quitara la pieza.
     * @param slot Posicion en el array de la pieza a quitar.
     *
     * @return true Si se quito correctamente.
     * @return false Si no habia pieza en ese slot.
     */
    bool quitarPieza(Barco* barco, int slot);

    /**
     * @brief Inicia una nueva partida.
     *
     * @return true Si se inicio correctamente.
     * @return false Si hubo un error.
     */
    bool iniciarJuego();

    /**
     * @brief Muestra el menu previo al juego.
     *
     * Se debe seleccionar los 2 jugadores que jugaran.
     *
     * @param jugador1 Primer jugador.
     * @param jugador2 Segundo jugador.
     */
    void menuJuego(Jugador* jugador1, Jugador* jugador2);

    /**
     * @brief Permite seleccionar un barco de un jugador.
     *
     * @param jugador Puntero al jugador.
     *
     * @return Barco* Puntero al barco seleccionado.
     */
    Barco* seleccionarBarco(Jugador* jugador);

    /**
     * @brief Verifica si las coordenadas ingresadas tienen el formato correcto.
     *
     * @param coordenadas Cadena con el formato "X,Y".
     * @param pX Puntero donde se guardara la coordenada X.
     * @param pY Puntero donde se guardara la coordenada Y.
     *
     * @return true Si el formato es correcto.
     * @return false Si el formato es incorrecto.
     */
    bool verificadorCoordenadas(std::string coordenadas, int* pX, int* pY);

    /**
     * @brief Agrega un barco a la matriz en la posicion dada.
     *
     * @param barco Barco a colocar.
     * @param coordenadaX Fila de inicio.
     * @param coordenadaY Columna de inicio.
     */
    void agregarBarco(Barco* barco, int coordenadaX, int coordenadaY);

    /**
     * @brief Inicializa la partida y la matriz de juego.
     *
     * @param tamanio Tamanio de la matriz.
     * @param barco1 Barco del jugador 1.
     * @param barco2 Barco del jugador 2.
     */
    void iniciarPartida(int tamanio, Barco* barco1, Barco* barco2);

    /**
     * @brief Ejecuta el ciclo principal del juego.
     */
    void juego();

    /**
     * @brief Verifica si el barco de un jugador sigue funcional.
     *
     * @param turno true si es el turno del jugador 1, false si es del jugador 2.
     *
     * @return true Si aun tiene piezas funcionales.
     * @return false Si todas sus piezas fueron destruidas.
     */
    bool verificarEstadoPiezas(bool turno);

    /**
     * @brief Verifica si el alcance de la potencia permite moverse una coordenada.
     *
     * @param potencia Valor de potencia.
     * @param coordenadaX Fila actual.
     * @param coordenadaY Columna actual.
     * @param nuevaCoordenadaX Fila destino.
     * @param nuevaCoordenadaY Columna destino.
     *
     * @return true Si el destino esta dentro del alcance.
     * @return false Si esta fuera de alcance.
     */
    bool verificarPotencia(int potencia, int coordenadaX, int coordenadaY, int nuevaCoordenadaX, int nuevaCoordenadaY);

    /**
     * @brief Permite mover el barco durante el turno.
     *
     * @param turno true si es el turno del jugador 1, false si es del jugador 2.
     *
     * @return true Si el movimiento fue exitoso.
     * @return false Si el movimiento no fue posible.
     */
    bool mover(bool turno);

    /**
     * @brief Permite disparar un misil durante el turno.
     *
     * @param turno true si es el turno del jugador 1, false si es del jugador 2.
     *
     * @return true Si el disparo fue valido.
     * @return false Si hubo un error.
     */
    bool disparar(bool turno);

    /**
     * @brief Ejecuta un disparo de misil en coordenadas dadas.
     * 
     * @param coordenadaX Fila del objetivo.
     * @param CoordenadaY Columna del objetivo.
     * @param potencia Alcance o radio del misil.
     */
    void misil(int coordenadaX, int CoordenadaY, int potencia);

    /**
     * @brief Ejecuta un disparo de metralla segun un angulo dado.
     *
     * @param angulo Angulo con el que se dispara la metralla.
     * @param turno true si es el turno del jugador 1, false si es del jugador 2.
     */
    void metralla(bool turno, int angulo, int potencia, int coordenadaX, int coordenadaY);

    /**
     * @brief Busca y muestra el jugador con mas victorias
     */
    void mayorGanador();

    /**
     * @brief Destructor. Libera todos los recursos utilizados por el sistema.
     */
    ~Sistema();
};