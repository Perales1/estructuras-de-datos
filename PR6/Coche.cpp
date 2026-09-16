/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Coche.cpp
 * @brief Implementación de la clase Coche que representa un vehículo eléctrico con atributos como matrícula, marca, modelo,
 * y métodos para simular su funcionamiento y gestionar su estado de carga.
 */

#include "Coche.h"

Coche::Coche() : id_matricula(""), marca(""), modelo(""), puntoRecarga(nullptr) {
    bateria = 20 + (rand() % 81);
}

Coche::Coche(std::string &id_matricula, std::string &marca, std::string &modelo) :
        modelo(modelo), id_matricula(id_matricula), marca(marca), puntoRecarga(nullptr) {
    bateria = 20 + (rand() % 81);
}

std::string &Coche::getIdMatricula() {
    return id_matricula;
}

void Coche::setIdMatricula(std::string &idMatricula) {
    id_matricula = idMatricula;
}

std::string &Coche::getMarca() {
    return marca;
}

void Coche::setMarca(std::string &_marca) {
    Coche::marca = _marca;
}

std::string &Coche::getModelo() {
    return modelo;
}

void Coche::setModelo(std::string &modelo_) {
    Coche::modelo = modelo_;
}

PuntoRecarga *Coche::getPuntoRecarga() {
    return puntoRecarga;
}

void Coche::setPuntoRecarga(PuntoRecarga *puntoRecarga_) {
    Coche::puntoRecarga = puntoRecarga_;
}

float Coche::getBateria() {
    return bateria;
}

void Coche::setBateria(double bateria_) {
    Coche::bateria = bateria_;
}

bool Coche::operator>(Coche &rhs) {
    return this->id_matricula > rhs.id_matricula;
}

bool Coche::operator<(Coche &rhs) {
    return this->id_matricula < rhs.id_matricula;
}

bool Coche::operator<=(Coche &rhs) {
    return this->id_matricula <= rhs.id_matricula;
}

bool Coche::operator>=(Coche &rhs) {
    return this->id_matricula >= rhs.id_matricula;
}

bool Coche::operator==(Coche &rhs) {
    return this->id_matricula == rhs.id_matricula;
}

bool Coche::operator!=(Coche &rhs) {
    return this->id_matricula != rhs.id_matricula;
}


std::ostream &operator<<(std::ostream &os, Coche &coche) {
    os << "id_matricula: " << coche.id_matricula << " marca: " << coche.marca << " modelo: " << coche.modelo
       << " puntoRecarga: " << coche.puntoRecarga << " bateria: " << coche.bateria;
    return os;
}

void Coche::circular() {
    if (puntoRecarga != nullptr) {
        puntoRecarga->borrarCoche(this);
        puntoRecarga = nullptr;
    } else {
        std::cerr << " El coche con matricula: " << id_matricula << " no esta en un punto de carga. " << std::endl;
    }
}

void Coche::aparcar(PuntoRecarga *puntoRecarga1) {
    if (puntoRecarga1 == nullptr) {
        std::cerr << "Error: Punto de recarga invalido." << std::endl;
        return;
    }

    puntoRecarga = puntoRecarga1;
    this->setPuntoRecarga(puntoRecarga1);

}


Coche &Coche::operator=(Coche &rhs) {
    if (this != &rhs) {
        this->id_matricula = rhs.id_matricula;
        this->marca = rhs.marca;
        this->modelo = rhs.modelo;
        this->bateria = rhs.bateria;

        this->puntoRecarga = rhs.puntoRecarga;
    }
    return *this;
}
