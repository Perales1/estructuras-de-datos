#include "PuntoRecarga.h"
#include <iostream>
#include <map>
#include <algorithm>

PuntoRecarga::PuntoRecarga(int id_, UTM &posicion_, unsigned int max_) :
        id(id_), posicion(posicion_), max(max_) {}

PuntoRecarga::PuntoRecarga(int id_) : id(id_), max(50) {}

unsigned int PuntoRecarga::getId() {
    return id;
}

void PuntoRecarga::setId(unsigned int id_) {
    id = id_;
}

unsigned int PuntoRecarga::getMax() {
    return max;
}

void PuntoRecarga::setMax(unsigned int max_) {
    max = max_;
}

UTM &PuntoRecarga::getPosicion() {
    return posicion;
}

void PuntoRecarga::setPosicion(UTM &posicion_) {
    posicion = posicion_;
}

Coche *PuntoRecarga::getMaxBateria() {
    if (!coches.empty()) {
        auto maxIt = coches.rbegin();
        Coche *cocheMaxBateria = maxIt->second;

        return cocheMaxBateria;
    } else {
        std::cerr << "No hay coches en este punto de recarga." << std::endl;
        return nullptr;
    }
}


bool PuntoRecarga::addCoche(Coche *coche) {
    if (coche == nullptr) {
        std::cerr << "Error: Intentando agregar un puntero nulo al punto de recarga." << std::endl;
        return false;
    }

    if (coches.size() >= max) {
        std::cerr << "No se puede aniadir el coche: punto de recarga lleno." << std::endl;
        return false;
    }

    double bateria = coche->getBateria();
    if (bateria < 0) {
        std::cerr << "Error: Bateria invalida (" << bateria << ") para el coche "
                  << coche->getIdMatricula() << std::endl;
        return false;
    }

    auto range = coches.equal_range(bateria);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == coche) {
            std::cerr << "Error: El coche ya esta en este punto de recarga" << std::endl;
            return false;
        }
    }

    coches.insert(std::make_pair(bateria, coche));
    coche->setPuntoRecarga(this);

    std::cout << "Coche aniadido - Matricula: " << coche->getIdMatricula()
              << ", Bateria: " << bateria
              << ", Total coches: " << coches.size() << std::endl;
    return true;
}

void PuntoRecarga::borrarCoche(Coche *coche) {
    if (coche == nullptr) {
        std::cerr << "Error: Coche nulo proporcionado para borrar." << std::endl;
        return;
    }

    auto range = coches.equal_range(coche->getBateria());

    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == coche) {
            coches.erase(it);
            std::cout << "Coche con matricula: " << coche->getIdMatricula() << " retirado del punto de carga."
                      << std::endl;
            coche->setPuntoRecarga(nullptr);
            return;
        }
    }

    std::cerr << "Coche con bateria: " << coche->getBateria() << " no se encuentra en el punto de carga." << std::endl;
}


std::multimap<float, Coche *> &PuntoRecarga::getCoches() {
    return coches;
}

void PuntoRecarga::setCoches(std::multimap<float, Coche *> &coches_) {
    coches = coches_;
}

PuntoRecarga::PuntoRecarga(int i, UTM coordenadas) {
    id = i;
    posicion = coordenadas;
}

int PuntoRecarga::getNumCoches() {
    return coches.size();
}