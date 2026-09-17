/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file PuntoRecarga.cpp
 * @brief Implementación de la clase PuntoRecarga
 */
#include "PuntoRecarga.h"

PuntoRecarga::PuntoRecarga(int id_, const Coordenadas &posicion_, unsigned int max_) :
        id(id_), posicion(posicion_), max(max_), coches(0) {}


PuntoRecarga::PuntoRecarga(int id_) : id(id_), max(50), coches(0) {}

unsigned int PuntoRecarga::getId() const {
    return id;
}

void PuntoRecarga::setId(unsigned int id_) {
    PuntoRecarga::id = id_;
}

unsigned int PuntoRecarga::getMax() const {
    return max;
}

void PuntoRecarga::setMax(unsigned int max_) {
    PuntoRecarga::max = max_;
}

const Coordenadas &PuntoRecarga::getPosicion() const {
    return posicion;
}

void PuntoRecarga::setPosicion(const Coordenadas &posicion_) {
    PuntoRecarga::posicion = posicion_;
}

Coche *PuntoRecarga::getMaxBateria() {
    if (coches.tamlog() == 0) return nullptr;

    Coche *macpcoche = coches[0];
    for (unsigned i = 1; i < coches.tamlog(); ++i) {
        if (coches[i]->getBateria() > macpcoche->getBateria()) {
            macpcoche = coches[i];
        }
    }
    return macpcoche;
}

bool PuntoRecarga::addCoche(Coche &coche) {
    if (coches.tamlog() >= max) {
        std::cerr << " No se puede anadir el coche: punto de recarga lleno. " << std::endl;
        return false;
    }
    coches.insertar(&coche);
    coche.setPuntoRecarga(this);
    std::cout << " Coche con matricula: " << coche.getIdMatricula() << " anadido al punto de recarga. " << std::endl;
    return true;
}

void PuntoRecarga::borrarCoche(Coche &coche) {
    for (unsigned int i = 0; i < coches.tamlog(); ++i) {
        if (coches[i] == &coche) {
            coches.borrar(i);
            std::cout << " Coche con matricula: " << coche.getIdMatricula() << " retirado del punto de carga. "
                      << std::endl;
            coche.setPuntoRecarga(nullptr);
            return;
        }
    }
    std::cerr << " Coche con matricula: " << coche.getIdMatricula() << " no se encuentra en el punto de carga. "
              << std::endl;
}

const VDinamico<Coche *> &PuntoRecarga::getCoches() const {
    return coches;
}

void PuntoRecarga::setCoches(const VDinamico<Coche *> &coches_) {
    PuntoRecarga::coches = coches_;
}

PuntoRecarga::PuntoRecarga(int i, Coordenadas coordenadas) {

}
