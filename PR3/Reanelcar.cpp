/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Reanelcar.cpp
 * @brief Implementación de la clase Reanelcar
 */
#include "Reanelcar.h"

Reanelcar::Reanelcar() {}

Reanelcar::Reanelcar(const AVL<Coche> &coches, const ListaDEnlazada<Usuario> &usuarios,
                     const PuntoRecarga &puntoRecarga) : coches(coches), usuarios(usuarios),
                                                         puntoRecarga(puntoRecarga) {}

Reanelcar::Reanelcar(const AVL<Coche> &coches, const ListaDEnlazada<Usuario> &usuarios) : coches(coches),
                                                                                          usuarios(usuarios) {}

Reanelcar::Reanelcar(const AVL<Coche> &coches) : coches(coches) {}

Reanelcar::~Reanelcar() {

}

Coche *Reanelcar::alquila() {
    Coche *coche = puntoRecarga.getMaxBateria();

    if (coche != nullptr) {
        puntoRecarga.borrarCoche(*coche);
        return coche;
    }

    return nullptr;
}

ListaDEnlazada<Usuario> Reanelcar::buscarUsuarioPorNombre(const std::string &nombre) {
    ListaDEnlazada<Usuario> resultado;
    Iterador<Usuario> iterador = usuarios.iterador();
    while (iterador.nodo != nullptr) {
        Usuario &usuario = iterador.nodo->dato;
        if (usuario.getNombre() == nombre) {
            resultado.insertaFin(usuario);
        }
        iterador.nodo = iterador.nodo->sig;
    }
    return resultado;
}

Usuario *Reanelcar::buscarUsuarioPorNif(const std::string &nif) {
    Iterador<Usuario> iterador = usuarios.iterador();
    while (iterador.nodo != nullptr) {
        Usuario &usuario = iterador.nodo->dato;
        if (usuario.getNif() == nif) {
            return &usuario;
        }
        iterador.nodo = iterador.nodo->sig;
    }
    return nullptr;
}

Coche *Reanelcar::buscarCochePorMatricula(const std::string &matricula) {
    Coche otrocoche(matricula, "", "");
    return coches.buscaREC(otrocoche);
}

void Reanelcar::colocarCochePR(Coche &coche_) {
    if (!puntoRecarga.addCoche(coche_)){
        std::cerr << " Error al anadir coche: " << coche_.getIdMatricula() << " al punto de recarga. " << std::endl;
    }
}

AVL<Coche> Reanelcar::getCoches() {
    return coches;
}

void Reanelcar::insertacoche(Coche &coche) {
    coches.inserta(coche);
}

void Reanelcar::insertausuario(Usuario &usuario) {
    usuarios.insertaFin(usuario);
}

void Reanelcar::setPuntoRecarga(const PuntoRecarga &puntoRecarga) {
    Reanelcar::puntoRecarga = puntoRecarga;
}

const PuntoRecarga &Reanelcar::getPuntoRecarga() const {
    return puntoRecarga;
}

const ListaDEnlazada<Usuario> &Reanelcar::getUsuarios() const {
    return usuarios;
}

void Reanelcar::setUsuarios(const ListaDEnlazada<Usuario> &usuarios) {
    Reanelcar::usuarios = usuarios;
}
