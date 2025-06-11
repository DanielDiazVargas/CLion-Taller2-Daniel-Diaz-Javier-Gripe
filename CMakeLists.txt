cmake_minimum_required(VERSION 3.30)
project(Taller_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taller_2 main.cpp
        Service/Sistema.cpp
        Service/Sistema.h
        Model/Pieza.cpp
        Model/Pieza.h
        Model/Jugador.cpp
        Model/Jugador.h
        Model/Barco.cpp
        Model/Barco.h
        Model/Contenedores/NodoSimple.tpp
        Model/Contenedores/NodoSimple.h
        Model/Contenedores/NodoMPP.cpp
        Model/Contenedores/NodoMPP.h
        Model/Contenedores/MPP.cpp
        Model/Contenedores/MPP.h
        Model/Contenedores/ListaSimple.tpp
        Model/Contenedores/ListaSimple.h
        Model/Contenedores/ListaCircularSimple.cpp
        Model/Contenedores/ListaCircularSimple.h)
