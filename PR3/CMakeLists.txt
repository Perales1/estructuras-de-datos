cmake_minimum_required(VERSION 3.26)
project(PR3AVL)

set(CMAKE_CXX_STANDARD 17)

add_executable(PR3AVL main.cpp
        VDinamico.h
        AVL.h
        Coche.h
        Coche.cpp
        PuntoRecarga.h
        PuntoRecarga.cpp
        ListaDEnlazada.h
        Iterador.h
        Usuario.h
        Usuario.cpp
        Reanelcar.h
        Reanelcar.cpp)
