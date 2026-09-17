/**
* @author David Fernández Espejo dfe00004@red.ujaen.es
* @author David Lorente Wagner dlw00001@red.ujaen.es
* @file Usuario.h
* @brief Implementación de la clase Reanelcar.
*/
#include "Reanelcar.h"

Usuario *Reanelcar::buscarUsuarioPorNif(const std::string &nif) {
    Iterador<Usuario> iterador = usuarios.iterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato().getNif() == nif) {
            return &iterador.dato();
        }
        iterador.siguiente();
    }
    return nullptr;
}

ListaDEnlazada<Usuario> Reanelcar::buscarUsuarioPorNombre(const std::string &nombre) {
    ListaDEnlazada<Usuario> usuariosEncontrados;
    Iterador<Usuario> iterador = usuarios.iterador();
    while (iterador.haySiguiente()) {
        std::string nombreusuario = iterador.dato().getNombre();
        if (nombreusuario.size() >= nombre.size() && nombreusuario.substr(0, nombre.size()) == nombre) {
            usuariosEncontrados.insertaFin(iterador.dato());
        }
        iterador.siguiente();
    }
    return usuariosEncontrados;
}

Coche *Reanelcar::buscarCochePorMatricula(const std::string &matricula) {
    for (unsigned i = 0; i < coches.tamlog(); ++i) {
        if (coches[i].getIdMatricula() == matricula) {
            return &coches[i];
        }
    }
    return nullptr;
}

VDinamico<Coche> *Reanelcar::buscarCochePorModelo(const std::string &modelo) {
    VDinamico<Coche> *cochesencontrados = new VDinamico<Coche>();
    for (unsigned int i = 0; i < coches.tamlog(); ++i) {
        if (coches[i].getModelo() == modelo) {
            cochesencontrados->insertar(coches[i]);
        }
    }
    return cochesencontrados;
}

void Reanelcar::alquilar(const std::string &nif, const std::string &matricula) {
    Usuario *usuario = buscarUsuarioPorNif(nif);
    if (usuario == nullptr) {
        throw std::runtime_error(" No se encuentra el usuario. ");
    }
    Coche *coche = buscarCochePorMatricula(matricula);
    if (coche == nullptr) {
        throw std::runtime_error(" No se encuentra el coche. ");
    }
    usuario->setCocheAlquilado(coche);
}