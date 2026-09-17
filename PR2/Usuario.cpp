/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Usuario.h
 * @brief Implementación de la clase Usuario.
 */
#include "Usuario.h"

Usuario::Usuario(const std::string &nif, const std::string &clave, const std::string &nombre,
                 const std::string &direccion) : nif(nif), nombre(nombre), direccion(direccion),
                                                 cocheAlquilado(nullptr) {}

const std::string &Usuario::getNif() const {
    return nif;
}

void Usuario::setNif(const std::string &nif) {
    Usuario::nif = nif;
}

const std::string &Usuario::getClave() const {
    return clave;
}

void Usuario::setClave(const std::string &clave) {
    Usuario::clave = clave;
}

const std::string &Usuario::getNombre() const {
    return nombre;
}

void Usuario::setNombre(const std::string &nombre) {
    Usuario::nombre = nombre;
}

const std::string &Usuario::getDireccion() const {
    return direccion;
}

void Usuario::setDireccion(const std::string &direccion) {
    Usuario::direccion = direccion;
}

Coche *Usuario::getCocheAlquilado() const {
    return cocheAlquilado;
}

void Usuario::setCocheAlquilado(Coche *cocheAlquilado) {
    Usuario::cocheAlquilado = cocheAlquilado;
}
