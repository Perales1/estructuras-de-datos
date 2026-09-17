/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Usuario.cpp
 * @brief Implementación de la clase Usuario
 */
#include "Usuario.h"

Usuario::Usuario(std::string &nif_, std::string &clave_, std::string &nombre_, std::string &direccion) :
        nif(nif_), clave(clave_), nombre(nombre_), direccion(direccion) {
    cochealquilado = nullptr;
    linkReanelcar = nullptr;
}

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

Coche *Usuario::getCochealquilado() const {
    return cochealquilado;
}

void Usuario::setCochealquilado(Coche *cochealquilado) {
    Usuario::cochealquilado = cochealquilado;
}

Reanelcar *Usuario::getLinkReanelcar() const {
    return linkReanelcar;
}

void Usuario::setLinkReanelcar(Reanelcar *linkReanelcar) {
    Usuario::linkReanelcar = linkReanelcar;
}

Coche *Usuario::cogecoche() {
    Coche *cochealquilado = linkReanelcar->alquila();
    if (cochealquilado != nullptr) {
        setCochealquilado(cochealquilado);

        cochealquilado->circular();

        std::cout << " Coche alquilado con matricula: " << cochealquilado->getIdMatricula() << std::endl;
    } else {
        std::cerr << " No hay coches dispopnibles en el punto de recarga. " << std::endl;
    }

    return cochealquilado;
}