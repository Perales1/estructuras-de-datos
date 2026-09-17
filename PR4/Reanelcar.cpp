/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Reanelcar.cpp
 * @brief Implementación de la clase Reanelcar
 */
#include "Reanelcar.h"
#include <limits>

Reanelcar::Reanelcar() {}

Reanelcar::Reanelcar(std::map<std::string, Coche> &coches) : coches(coches) {}

Reanelcar::Reanelcar(std::map<std::string, Coche> &coches, std::list<Usuario> &usuarios,
                     std::vector<PuntoRecarga> &puntoRecarga) : coches(coches), usuarios(usuarios),
                                                                sitios(puntoRecarga) {
    for (Usuario &usuario: this->usuarios) {
        usuario.setLinkReanelcar(this);
    }
}

Reanelcar::Reanelcar(std::map<std::string, Coche> &coches, std::list<Usuario> &usuarios) : coches(coches),
                                                                                           usuarios(
                                                                                                   usuarios) {}


Reanelcar::~Reanelcar() {

}

std::list<Usuario> Reanelcar::buscarUsuarioPorNombre(std::string &nombre) {
    std::list<Usuario> resultado;
    std::list<Usuario>::iterator iterador = usuarios.begin();
    while (iterador != usuarios.end()) {
        Usuario &usuario = *iterador;
        if (usuario.getNombre() == nombre) {
            resultado.push_back(usuario);
        }
        ++iterador;
    }
    return resultado;
}

Usuario *Reanelcar::buscarUsuarioPorNif(std::string &nif) {
    std::list<Usuario>::iterator iterador = usuarios.begin();
    while (iterador != usuarios.end()) {
        Usuario &usuario = *iterador;
        if (usuario.getNif() == nif) {
            return &usuario;
        }
        ++iterador;
    }
    return nullptr;
}

Coche *Reanelcar::buscarCochePorMatricula(std::string &matricula) {
    std::map<std::string, Coche>::iterator iterador = coches.find(matricula);
    return iterador != coches.end() ? &iterador->second : nullptr;
}

bool Reanelcar::colocarCochePR(Coche *coche_, PuntoRecarga *pr) {
    if (!pr || !coche_) {
        std::cerr << "Error: Punto de carga o coche invalido." << std::endl;
        return false;
    }

    if (pr->getNumCoches() >= pr->getMax()) {
        std::cerr << "Error: Punto de recarga lleno para el coche con matricula " << coche_->getIdMatricula()
                  << std::endl;
        return false;
    }

    coche_->aparcar(pr);

    if (pr->addCoche(coche_)) {
        return true;
    } else {
        std::cerr << "Error: No se pudo añadir el coche " << coche_->getIdMatricula() << " al punto de recarga."
                  << std::endl;
        return false;
    }
}

std::map<std::string, Coche> &Reanelcar::getCoches() {
    return coches;
}

void Reanelcar::insertacoche(Coche &coche) {
    coches[coche.getIdMatricula()] = coche;
}

void Reanelcar::insertausuario(Usuario &usuario) {
    usuarios.push_back(usuario);
}

Coche *Reanelcar::alquilar(Usuario &u, int idprorigen, int idprdes, Fecha &fini) {
    std::cout << "Alquilando coche a usuario: " << u.getNombre() << std::endl;

    if (idprorigen < 0 || idprdes < 0) {
        std::cerr << "Error: IDs de punto de recarga inválidos" << std::endl;
        return nullptr;
    }

    PuntoRecarga *puntoSalida = nullptr;
    for (PuntoRecarga &punto: sitios) {
        if (punto.getId() == idprorigen) {
            puntoSalida = &punto;
            break;
        }
    }

    if (!puntoSalida) {
        std::cerr << "Error: Punto de recarga de origen no encontrado." << std::endl;
        return nullptr;
    }

    if (puntoSalida->getNumCoches() == 0) {
        std::cerr << "Error: No hay coches disponibles en el punto de origen." << std::endl;
        return nullptr;
    }

    Coche *cocheAlquilado = puntoSalida->getMaxBateria();
    if (!cocheAlquilado) {
        std::cerr << "Error: No se pudo obtener un coche del punto de recarga." << std::endl;
        return nullptr;
    }

    if (cocheAlquilado->getIdMatricula().empty()) {
        std::cerr << "Error: El coche seleccionado no tiene una matrícula valida." << std::endl;
        return nullptr;
    }

    u.setCochealquilado(cocheAlquilado);

    Trayecto *nuevoTrayecto = u.crearTrayecto(puntoSalida, getPuntoRecargaID(idprdes), fini);
    if (!nuevoTrayecto) {
        std::cerr << "Error al crear trayecto para el usuario: " << u.getNombre() << std::endl;
    }

    std::cout << "Coche alquilado exitosamente - Matricula: " << cocheAlquilado->getIdMatricula() << std::endl;
    return cocheAlquilado;
}

PuntoRecarga *Reanelcar::obtenerPRmenosCoches() {
    if (sitios.empty()) {
        return nullptr;
    }

    PuntoRecarga *puntoConMenosCoches = &sitios[0];
    int minCoches = puntoConMenosCoches->getNumCoches();

    for (PuntoRecarga &punto: sitios) {
        if (punto.getNumCoches() < minCoches) {
            puntoConMenosCoches = &punto;
            minCoches = punto.getNumCoches();
        }
    }

    return puntoConMenosCoches;
}


void Reanelcar::setCoches(std::map<std::string, Coche> &coches) {
    Reanelcar::coches = coches;
}

std::list<Usuario> &Reanelcar::getUsuarios() {
    return usuarios;
}

void Reanelcar::setUsuarios(std::list<Usuario> &usuarios) {
    Reanelcar::usuarios = usuarios;
}

std::vector<PuntoRecarga> &Reanelcar::getSitios() {
    return sitios;
}

void Reanelcar::setSitios(std::vector<PuntoRecarga> &sitios) {
    Reanelcar::sitios = sitios;
}

PuntoRecarga *Reanelcar::getPuntoRecargaID(int id) {
    for (size_t i = 0; i < sitios.size(); ++i) {
        if (sitios[i].getId() == id) {
            return &sitios[i];
        }
    }
    return nullptr;
}

void Reanelcar::agregarPuntosRecarga(PuntoRecarga &punto) {
    sitios.push_back(punto);
}

void Reanelcar::mostrarDatosCoche(std::string &matriculaObjetivo) {
    Coche *cocheEncontrado = buscarCochePorMatricula(matriculaObjetivo);

    if (cocheEncontrado == nullptr) {
        std::cout << "Coche con matrícula " << matriculaObjetivo << " no encontrado." << std::endl;
        return;
    }

    std::cout << "Datos del coche:" << std::endl;
    std::cout << "Matricula: " << cocheEncontrado->getIdMatricula() << std::endl;
    std::cout << "Modelo: " << cocheEncontrado->getModelo() << std::endl;
    std::cout << "Marca: " << cocheEncontrado->getMarca() << std::endl;
    std::cout << "Bateria: " << cocheEncontrado->getBateria() << std::endl;

    if (cocheEncontrado->getPuntoRecarga()) {
        int idPuntoRecarga = cocheEncontrado->getPuntoRecarga()->getId();
        std::cout << "El coche se encuentra cargando en el punto de recarga ID: " << idPuntoRecarga << std::endl;

        PuntoRecarga *puntoRecarga = getPuntoRecargaID(idPuntoRecarga);

        if (puntoRecarga) {
            std::cout << "Otros coches en el mismo punto de recarga:" << std::endl;
            for (std::pair<const float, Coche *> coche: puntoRecarga->getCoches()) {
                if (coche.second->getIdMatricula() != cocheEncontrado->getIdMatricula()) {
                    std::cout << "- Matrícula: " << coche.second->getIdMatricula() << ", Modelo: "
                              << coche.second->getModelo() << "Marca: " << coche.second->getMarca() << "Bateria: "
                              << coche.second->getBateria() << std::endl;
                }
            }
        } else {
            std::cout << "Error: No se encontro el punto de recarga con ID " << idPuntoRecarga << "." << std::endl;
        }
    } else {
        std::cout << "El coche no se encuentra cargando en ningun punto de recarga." << std::endl;
    }
}

std::vector<std::pair<Usuario, Trayecto>> Reanelcar::trayectosEnFecha(Fecha f) {
    std::vector<std::pair<Usuario, Trayecto>> trayectosEnFecha;

    for (Usuario &usuario: usuarios) {
        for (auto &parTrayecto: usuario.getTrayectos()) {
            Trayecto *trayecto = parTrayecto.second;

            if (trayecto->getfechaInicio().verDia() == f.verDia() &&
                trayecto->getfechaInicio().verMes() == f.verMes() &&
                trayecto->getfechaInicio().verAnio() == f.verAnio()) {

                trayectosEnFecha.push_back(std::make_pair(usuario, *trayecto));
            }
        }
    }

    return trayectosEnFecha;
}
