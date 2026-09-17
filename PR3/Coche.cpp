/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Coche.cpp
 * @brief Implementación de la clase Coche
 */
#include "Coche.h"

Coche::Coche() : id_matricula(""), marca(""), modelo(""), puntoRecarga(nullptr) {
    bateria = 20 + (rand() % 81);
}

Coche::Coche(const std::string &id_matricula, const std::string &marca, const std::string &modelo) :
        modelo(modelo), id_matricula(id_matricula), marca(marca), puntoRecarga(nullptr) {
    bateria = 20 + (rand() % 81);
}

const std::string &Coche::getIdMatricula() const {
    return id_matricula;
}

void Coche::setIdMatricula(const std::string &idMatricula) {
    id_matricula = idMatricula;
}

const std::string &Coche::getMarca() const {
    return marca;
}

void Coche::setMarca(const std::string &_marca) {
    Coche::marca = _marca;
}

const std::string &Coche::getModelo() const {
    return modelo;
}

void Coche::setModelo(const std::string &modelo_) {
    Coche::modelo = modelo_;
}

PuntoRecarga *Coche::getPuntoRecarga() const {
    return puntoRecarga;
}

void Coche::setPuntoRecarga(PuntoRecarga *puntoRecarga_) {
    Coche::puntoRecarga = puntoRecarga_;
}

double Coche::getBateria() const {
    return bateria;
}

void Coche::setBateria(double bateria_) {
    Coche::bateria = bateria_;
}

bool Coche::operator>(const Coche &rhs) const {
    return this->id_matricula > rhs.id_matricula;
}

bool Coche::operator<(const Coche &rhs) const {
    return this->id_matricula < rhs.id_matricula;
}

bool Coche::operator<=(const Coche &rhs) const {
    return this->id_matricula < rhs.id_matricula || id_matricula == rhs.id_matricula;
}

bool Coche::operator>=(const Coche &rhs) const {
    return this->id_matricula > rhs.id_matricula || id_matricula == rhs.id_matricula;
}

bool Coche::operator==(const Coche &rhs) const {
    return id_matricula == rhs.id_matricula;
}

bool Coche::operator!=(const Coche &rhs) const {
    return this->id_matricula != rhs.id_matricula;
}

std::ostream &operator<<(std::ostream &os, const Coche &coche) {
    os << "id_matricula: " << coche.id_matricula << " marca: " << coche.marca << " modelo: " << coche.modelo
       << " puntoRecarga: " << coche.puntoRecarga << " bateria: " << coche.bateria;
    return os;
}

void Coche::circular() {
    if (puntoRecarga != nullptr) {
        puntoRecarga->borrarCoche(*this);
        puntoRecarga = nullptr;
        std::cout << " Coche con matricula: " << id_matricula << " esta en movimiento. " << std::endl;
    } else {
        std::cerr << " El coche con matricula: " << id_matricula << " no esta en un punto de carga. " << std::endl;
    }
}