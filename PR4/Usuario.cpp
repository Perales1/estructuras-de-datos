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
}

std::string &Usuario::getNif() {
    return nif;
}

void Usuario::setNif(std::string &nif) {
    Usuario::nif = nif;
}

std::string &Usuario::getClave() {
    return clave;
}

void Usuario::setClave(std::string &clave) {
    Usuario::clave = clave;
}

std::string &Usuario::getNombre() {
    return nombre;
}

void Usuario::setNombre(std::string &nombre) {
    Usuario::nombre = nombre;
}

std::string &Usuario::getDireccion() {
    return direccion;
}

void Usuario::setDireccion(std::string &direccion) {
    Usuario::direccion = direccion;
}

Coche *Usuario::getCochealquilado() {
    return cochealquilado;
}

void Usuario::setCochealquilado(Coche *cochealquilado) {
    Usuario::cochealquilado = cochealquilado;
}

Reanelcar *Usuario::getLinkReanelcar() {
    return linkReanelcar;
}

void Usuario::setLinkReanelcar(Reanelcar *linkReanelcar) {
    Usuario::linkReanelcar = linkReanelcar;
}

Coche *Usuario::cogecoche(int idprorigen, int idprdes, Fecha &fini) {
    if (linkReanelcar == nullptr) {
        std::cerr << "Error: linkReanelcar es nullptr." << std::endl;
        return nullptr;
    }

    Coche *cocheAlquilado = linkReanelcar->alquilar(*this, idprorigen, idprdes, fini);

    if (cocheAlquilado != nullptr) {
        setCochealquilado(cocheAlquilado);
        cocheAlquilado->circular();

        std::cout << "Coche alquilado con matricula: " << cocheAlquilado->getIdMatricula() << std::endl;
    } else {
        std::cerr << "No hay coches disponibles en el punto de recarga." << std::endl;
    }

    return cocheAlquilado;
}

Trayecto *Usuario::crearTrayecto(PuntoRecarga *origin, PuntoRecarga *destination, Fecha &fechaInicio) {
    Trayecto *nuevoTrayecto = new Trayecto(origin, destination, cochealquilado, fechaInicio);

    trayectos.insert(std::make_pair(fechaInicio, nuevoTrayecto));

    return nuevoTrayecto;
}

Coche *Usuario::iniciarTrayecto(PuntoRecarga *origin, int destino) {
    PuntoRecarga *destination = (PuntoRecarga *) linkReanelcar->getPuntoRecargaID(destino);

    if (!destination) {
        std::cerr << " Error: Punto de recarga de destino no encontrado. " << std::endl;
        return nullptr;
    }

    Fecha fechaInicio;
    Trayecto *nuevoTrayecto = crearTrayecto(origin, destination, fechaInicio);
    if (nuevoTrayecto) {
        nuevoTrayecto->finalizarTrayecto(fechaInicio);
    }
    return cochealquilado;
}

void Usuario::aparcaCoche(PuntoRecarga *destination) {
    if (!cochealquilado) {
        std::cerr << "Error: No hay coche alquilado para aparcar." << std::endl;
        return;
    }

    if (linkReanelcar->colocarCochePR(cochealquilado, destination)) {
        std::cout << "Coche con matricula " << cochealquilado->getIdMatricula() << " aparcado en el punto de recarga."
                  << std::endl;
    } else {
        std::cerr << "No se pudo aparcar el coche en el punto de recarga de destino." << std::endl;
    }
}


std::list<Trayecto *> Usuario::getTrayectosFecha(Fecha &fecha) {
    std::list<Trayecto *> resultados;
    std::pair<std::multimap<Fecha, Trayecto *>::iterator, std::multimap<Fecha, Trayecto *>::iterator> rango;
    rango = trayectos.equal_range(fecha);

    for (std::multimap<Fecha, Trayecto *>::iterator iterador = rango.first; iterador != rango.second; ++iterador) {
        resultados.push_back(iterador->second);
    }
    return resultados;
}

std::multimap<Fecha, Trayecto *> Usuario::getTrayectos() {
    return trayectos;
}

void Usuario::setTrayectos(std::multimap<Fecha, Trayecto *> &trayectos) {
    Usuario::trayectos = trayectos;
}

Usuario::Usuario(std::string &nif_, std::string &clave_, std::string &nombre_, std::string &direccion, Reanelcar *link_)
        : nif(nif_), clave(clave_), nombre(nombre_), direccion(direccion), linkReanelcar(link_) {
    cochealquilado = nullptr;
}

Trayecto *Usuario::getUltimoTrayecto() {
    if (trayectos.empty()) {
        std::cerr << "No hay trayectos registrados para este usuario." << std::endl;
        return nullptr;
    }
    return trayectos.rbegin()->second;
}
