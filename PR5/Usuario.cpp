/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Usuario.cpp
 * @brief Declaración de la clase Usuario
 */

#include "Usuario.h"
#include <set>

Usuario::Usuario(std::string &nombre_, std::string &nif_) : nombre(nombre_), nif(nif_) {
    cochealquilado = nullptr;
    linkReanelcar_ = nullptr;
}

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
    return linkReanelcar_;
}

void Usuario::setLinkReanelcar(Reanelcar *linkReanelcar) {
    Usuario::linkReanelcar_ = linkReanelcar;
}

Coche *Usuario::cogecoche(int idprorigen, int idprdes, Fecha &fini) {
    if (linkReanelcar_ == nullptr) {
        std::cerr << "Error: linkReanelcar_ es nullptr." << std::endl;
        return nullptr;
    }

    Coche *cocheAlquilado;
    cocheAlquilado = linkReanelcar_->alquilar(*this, idprorigen, idprdes, fini);

    if (cocheAlquilado != nullptr) {
        setCochealquilado(cocheAlquilado);
        cocheAlquilado->circular();
    } else {
        std::cerr << "No hay coches disponibles en el punto de recarga." << std::endl;
    }

    return cocheAlquilado;
}

Trayecto *Usuario::crearTrayecto(PuntoRecarga *origin, PuntoRecarga *destination, Fecha &fechaInicio) {
    for (std::pair<const Fecha, Trayecto *> &entry: trayectos) {
        Trayecto *trayectoExistente = entry.second;
        if (trayectoExistente->getOrigin() == origin &&
            trayectoExistente->getDestination() == destination &&
            trayectoExistente->getfechaInicio().cadena() == fechaInicio.cadena()) {
            return trayectoExistente;
        }
    }
    Trayecto *nuevoTrayecto = new Trayecto(origin, destination, cochealquilado, fechaInicio);
    trayectos.insert(std::make_pair(fechaInicio, nuevoTrayecto));
    return nuevoTrayecto;
}


Coche *Usuario::iniciarTrayecto(PuntoRecarga *origin, int destino) {
    PuntoRecarga *destination = (PuntoRecarga *) linkReanelcar_->getPuntoRecargaID(destino);

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

void Usuario::aparcaCoche(Coche *coche, PuntoRecarga *destination, int retraso) {
    if (!cochealquilado) {
        std::cerr << "Error: No hay coche alquilado para aparcar." << std::endl;
        return;
    }

    if (coche->getPuntoRecarga() == destination) {
        std::cout << "El coche con matricula " << coche->getIdMatricula()
                  << " ya está aparcado en el punto de recarga." << std::endl;
        return;
    }

    if (retraso > 0) {
        std::cout << "Se detectaron: " << retraso << " horas de retraso." << std::endl;
        decrementarPuntos(retraso);
    }

    if (linkReanelcar_->colocarCochePR(cochealquilado, destination)) {
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
        : nif(nif_), clave(clave_), nombre(nombre_), direccion(direccion), linkReanelcar_(link_) {
    cochealquilado = nullptr;
}

Trayecto *Usuario::getUltimoTrayecto() {
    if (trayectos.empty()) {
        std::cerr << "No hay trayectos registrados para este usuario." << std::endl;
        return nullptr;
    }
    return trayectos.rbegin()->second;
}

void Usuario::eliminarTrayectos() {
    for (std::pair<const Fecha, Trayecto *> &trayecto: trayectos) {
        delete trayecto.second;
    }
    trayectos.clear();
    std::cout << " Todos los trayectos del usuario han sido eliminados. " << std::endl;
}

void Usuario::decrementarPuntos(int retraso) {
    int puntosPerdidos = retraso * 2;
    puntos -= puntosPerdidos;
    if (puntos < 0) puntos = 0;
    std::cout << " Puntos perdidos por retraso: " << puntosPerdidos << ". Puntos restantes: " << puntos << std::endl;
}

void Usuario::mostrarTrayectosConRetraso() {
    std::set<int> trayectosMostrados;

    for (std::pair<const Fecha, Trayecto *> &entry: trayectos) {
        Trayecto *trayecto = entry.second;

        if (trayectosMostrados.find(trayecto->getidTrayecto()) != trayectosMostrados.end()) {
            continue;
        }

        trayectosMostrados.insert(trayecto->getidTrayecto());

        std::cout << "Trayecto ID: " << trayecto->getidTrayecto() << std::endl;
        std::cout << "Fecha Inicio: " << trayecto->getfechaInicio().cadena() << std::endl;
        std::cout << "Fecha fin: " << trayecto->getfechaFin().cadena() << std::endl;
        std::cout << "Punto origen: " << trayecto->getOrigin()->getId() << std::endl;
        std::cout << "Punto de destino: " << trayecto->getDestination()->getId() << std::endl;
        std::cout << "Coche alquilado: " << cochealquilado->getIdMatricula()
                  << ", Marca: " << cochealquilado->getMarca()
                  << ", Modelo: " << cochealquilado->getModelo() << std::endl;
        std::cout << "Puntos acumulados: " << puntos << std::endl;
        std::cout << "------------------------------" << std::endl;
    }
}
