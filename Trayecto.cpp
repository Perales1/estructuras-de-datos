/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Trayecto.cpp
 * @brief Implementación de la clase Trayecto
 */
#include "Trayecto.h"

int Trayecto::contadorTrayectos = 1;

Trayecto::Trayecto(PuntoRecarga *origin_, PuntoRecarga *destination_, Coche *inthecar_, Fecha &fechainicio_)
        : origin(origin_), destination(destination_), inthecar(inthecar_), fechainicio(fechainicio_) {
    idTrayecto = contadorTrayectos++;
    fechafin = fechainicio_;
    fechafin.anadirDias(1 + rand() % 2);
}


int Trayecto::getidTrayecto() {
    return idTrayecto;
}

PuntoRecarga *Trayecto::getOrigin() {
    return origin;
}

PuntoRecarga *Trayecto::getDestination() {
    return destination;
}

Coche *Trayecto::getinthecar() {
    return inthecar;
}

Fecha &Trayecto::getfechaInicio() {
    return fechainicio;
}

Fecha &Trayecto::getfechaFin() {
    return fechafin;
}

void Trayecto::finalizarTrayecto(Fecha &fechaFin) {
    this->fechafin = fechafin;
}