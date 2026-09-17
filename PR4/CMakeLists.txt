cmake_minimum_required(VERSION 3.26)
project(PR4STL)

set(CMAKE_CXX_STANDARD 17)

add_executable(PR4STL main.cpp
        fecha.h
        fecha.cpp
        Coche.h
        Coche.cpp
        Reanelcar.h
        Reanelcar.cpp
        Usuario.h
        Usuario.cpp
        PuntoRecarga.h
        PuntoRecarga.cpp
        Trayecto.h
        Trayecto.cpp
        UTM.h)
