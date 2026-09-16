cmake_minimum_required(VERSION 3.26)
project(PR6)

set(CMAKE_CXX_STANDARD 17)

add_executable(PR6 main.cpp
    Coche.cpp
    Coche.h
    EntradaUsuario.h
    EntradaUsuario.cpp
    fecha.h
    fecha.cpp
    Hash.h
    Hash.cpp
    PuntoRecarga.h
    PuntoRecarga.cpp
    Reanelcar.h
    Reanelcar.cpp
    Usuario.h
    Usuario.cpp
    UTM.h
    Trayecto.h
    Trayecto.cpp
        UTM.cpp
        MallaRegular.h
        Casilla.h
        img.h
        img.cpp
)
