/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file EntradaUsuario.cpp
 * @brief Implementación de la clase EntradaUsuario, que representa el dato alamcenado en la tabla de
 * dispersión
 */

#include "EntradaUsuario.h"
#include "Usuario.h"

EntradaUsuario::EntradaUsuario() : claveHash(0), usuario(nullptr) {}

EntradaUsuario::EntradaUsuario(unsigned long clave, Usuario &usr)
        : claveHash(clave), usuario(std::make_unique<Usuario>(usr)) {}

EntradaUsuario::~EntradaUsuario() = default;

EntradaUsuario::EntradaUsuario(const EntradaUsuario &otro)
        : claveHash(otro.claveHash),
          usuario(otro.usuario ? std::make_unique<Usuario>(*otro.usuario) : nullptr) {}

EntradaUsuario &EntradaUsuario::operator=(const EntradaUsuario &otro) {
    if (this != &otro) {
        usuario.reset(otro.usuario ? new Usuario(*otro.usuario) : nullptr);
        claveHash = otro.claveHash;
    }
    return *this;
}

unsigned long EntradaUsuario::getClaveHash() const {
    return claveHash;
}

Usuario *EntradaUsuario::getUsuario() const {
    return usuario.get();
}

void EntradaUsuario::setClaveHash(unsigned long clave) {
    claveHash = clave;
}

void EntradaUsuario::setUsuario(Usuario &usr) {
    usuario = std::make_unique<Usuario>(usr);
}

bool EntradaUsuario::vacia() const {
    return !usuario;
}

void EntradaUsuario::vaciar() {
    usuario.reset();
    claveHash = 0;
}
