/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file main.cpp
 * @brief Programa de pruebas de la clase Reanelcar con la implementación de estructuras de datos
 * pertenecientes a la biblioteca externa STL
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <random>
#include "Reanelcar.h"

/**
 * @brief Abre un archivo en modo lectura.
 * @param archivo Referencia al flujo de archivo a abrir.
 * @param ruta Ruta del archivo a abrir.
 * @return `true` si el archivo se abre correctamente, `false` en caso de error.
 */
bool abrirArchivo(std::ifstream &archivo, const std::string &ruta) {
    archivo.open(ruta);
    if (!archivo.is_open()) {
        std::cerr << "Error de apertura en archivo: " << ruta << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Carga los datos de los usuarios desde un archivo CSV.
 *
 * Esta función lee un archivo CSV que contiene la información de los usuarios y los carga en el sistema.
 *
 * @param archivoRuta La ruta del archivo CSV que contiene los datos de los usuarios.
 * @param reanelcar Referencia a un objeto de tipo Reanelcar donde se almacenarán los usuarios cargados.
 */
void cargarUsuarios(const std::string &rutaArchivo, Reanelcar &r) {
    std::ifstream archivo;
    if (!abrirArchivo(archivo, rutaArchivo)) return;

    std::string fila;
    while (getline(archivo, fila)) {
        if (fila.empty()) continue;

        std::stringstream columnas(fila);
        std::string nif, clave, nombre, direccion;

        getline(columnas, nif, ',');
        getline(columnas, clave, ',');
        getline(columnas, nombre, ',');
        getline(columnas, direccion, ',');

        Usuario usuario(nif, clave, nombre, direccion);
        r.insertausuario(usuario);
    }

    archivo.close();
}

/**
 * @brief Carga los datos de los coches desde un archivo CSV.
 *
 * Esta función lee un archivo CSV que contiene la información de los coches y los carga en el sistema.
 *
 * @param archivoRuta La ruta del archivo CSV que contiene los datos de los coches.
 * @param reanelcar Referencia a un objeto de tipo Reanelcar donde se almacenarán los coches cargados.
 */
void cargarCoches(const std::string &rutaArchivo, Reanelcar &r) {
    std::ifstream archivo;
    if (!abrirArchivo(archivo, rutaArchivo)) return;

    std::string fila;
    while (getline(archivo, fila)) {
        if (fila.empty()) continue;

        std::stringstream columnas(fila);
        std::string id_matricula, marca, modelo, bateria_str;
        double bateria = 0.0;

        getline(columnas, id_matricula, ',');
        getline(columnas, marca, ',');
        getline(columnas, modelo, ',');
        getline(columnas, bateria_str, ',');

        bateria_str.erase(bateria_str.find_last_not_of(" \n\r\t") + 1);

        try {
            bateria = std::stod(bateria_str);
        } catch (const std::exception &e) {
            std::cerr << "Error al convertir batería: '" << bateria_str
                      << "' en coche con matrícula " << id_matricula << std::endl;
            continue;
        }

        Coche coche(id_matricula, marca, modelo);
        coche.setBateria(bateria);

        r.insertacoche(coche);
    }

    archivo.close();
}

/**
 * @brief Carga los puntos de recarga desde un archivo CSV.
 *
 * Esta función lee un archivo CSV que contiene la información de los puntos de recarga y los carga en el sistema.
 *
 * @param archivoRuta La ruta del archivo CSV que contiene los puntos de recarga.
 * @param reanelcar Referencia a un objeto de tipo Reanelcar donde se almacenarán los puntos de recarga cargados.
 */
void cargarPuntosRecarga(const std::string &rutaArchivo, Reanelcar &r) {
    std::ifstream archivo;
    if (!abrirArchivo(archivo, rutaArchivo)) return;

    std::string fila;
    bool primeraLinea = true;

    while (getline(archivo, fila)) {
        if (primeraLinea) {
            primeraLinea = false;
            continue;
        }

        if (fila.empty()) continue;

        std::stringstream columnas(fila);

        int id = 0;
        float lat = 0.0f, lon = 0.0f;
        unsigned int capacidadMaxima = 0;

        if (getline(columnas, fila, ',')) {
            try {
                id = std::stoi(fila);
            } catch (const std::exception &e) {
                std::cerr << "Error al convertir el id: " << fila << std::endl;
                continue;
            }
        }

        if (getline(columnas, fila, ',')) {
            try {
                lat = std::stof(fila);
            } catch (const std::exception &e) {
                std::cerr << "Error al convertir latitud: " << fila << std::endl;
                continue;
            }
        }

        if (getline(columnas, fila, ',')) {
            try {
                lon = std::stof(fila);
            } catch (const std::exception &e) {
                std::cerr << "Error al convertir longitud: " << fila << std::endl;
                continue;
            }
        }

        if (getline(columnas, fila, ',')) {
            try {
                capacidadMaxima = std::stoi(fila);
            } catch (const std::exception &e) {
                std::cerr << "Error al convertir capacidadMaxima: " << fila << std::endl;
                continue;
            }
        }

        UTM posicion(lat, lon);
        PuntoRecarga puntoRecarga(id, posicion, capacidadMaxima);

        r.agregarPuntosRecarga(puntoRecarga);
    }
    archivo.close();
}

/**
 * @brief Distribuye los coches por los puntos de recarga, priorizando los coches con mayor batería.
 * @param reanelcar Referencia al objeto de tipo Reanelcar donde se encuentran los coches y puntos de recarga.
 */
void distribuirCochesPorBateria(Reanelcar &reanelcar) {
    std::map<std::string, Coche> &coches = reanelcar.getCoches();
    std::vector<PuntoRecarga> &puntosRecarga = reanelcar.getSitios();

    if (coches.empty()) {
        std::cerr << "Error: No hay coches en el sistema para asignar." << std::endl;
        return;
    }
    if (puntosRecarga.empty()) {
        std::cerr << "Error: No hay puntos de recarga disponibles." << std::endl;
        return;
    }

    std::multimap<int, Coche *> cochesPorBateria;
    for (std::pair<const std::string, Coche> &parCoche: coches) {
        cochesPorBateria.insert({parCoche.second.getBateria(), &parCoche.second});
    }
    size_t indexPunto = 0;
    for (auto it = cochesPorBateria.rbegin(); it != cochesPorBateria.rend(); ++it) {
        Coche *coche = it->second;
        bool cocheAsignado = false;

        while (!cocheAsignado) {
            PuntoRecarga &puntoRecarga = puntosRecarga[indexPunto];

            if (puntoRecarga.getNumCoches() < puntoRecarga.getMax()) {
                if (puntoRecarga.addCoche(coche)) {
                    std::cout << "Coche con matricula " << coche->getIdMatricula()
                              << " (Bateria: " << coche->getBateria()
                              << "%) asignado al punto de recarga ID " << puntoRecarga.getId() << std::endl;
                    cocheAsignado = true;
                }
            }

            indexPunto = (indexPunto + 1) % puntosRecarga.size();

            if (!cocheAsignado && indexPunto == 0) {
                std::cerr << "No hay puntos de recarga con espacio disponible para el coche con matricula "
                          << coche->getIdMatricula() << std::endl;
                break;
            }
        }
    }
    std::cout << "Distribucion de coches completada." << std::endl;
}

/**
 * @brief Muestra la capacidad total de los puntos de recarga y los coches asignados a cada uno.
 * @param puntosRecarga Referencia a la lista de puntos de recarga.
 */
void contarCapacidadTotal(std::vector<PuntoRecarga> &puntosRecarga) {
    unsigned int capacidadMaximaTotal = 0;
    unsigned int cochesAsignadosTotal = 0;

    for (PuntoRecarga &puntoRecarga: puntosRecarga) {
        std::cout << "Punto de recarga ID: " << puntoRecarga.getId()
                  << " - Capacidad maxima: " << puntoRecarga.getMax()
                  << " - Coches asignados: " << puntoRecarga.getNumCoches() << std::endl;

        capacidadMaximaTotal += puntoRecarga.getMax();
        cochesAsignadosTotal += puntoRecarga.getNumCoches();
    }

    std::cout << "Capacidad maxima total de todos los puntos de recarga: " << capacidadMaximaTotal << std::endl;
    std::cout << "Numero total de coches asignados en los puntos de recarga: " << cochesAsignadosTotal << std::endl;

    if (cochesAsignadosTotal < capacidadMaximaTotal) {
        std::cout << "Aun hay espacio disponible en los puntos de recarga." << std::endl;
    } else {
        std::cout << "Todos los puntos de recarga estan ocupados al maximo de su capacidad." << std::endl;
    }
}

/**
 * @brief Asigna coches a los usuarios y crea trayectos de acuerdo a los puntos de recarga disponibles.
 * @param reanelcar Referencia al objeto de tipo Reanelcar con los usuarios y puntos de recarga.
 */
void asignarCochesYCrearTrayectos(Reanelcar &reanelcar) {
    std::list<Usuario> &usuarios = reanelcar.getUsuarios();
    std::vector<PuntoRecarga> &puntosRecarga = reanelcar.getSitios();

    if (puntosRecarga.empty()) {
        std::cerr << "Error: No hay puntos de recarga disponibles." << std::endl;
        return;
    }

    for (Usuario &usuario: usuarios) {
        usuario.setLinkReanelcar(&reanelcar);
    }

    Fecha fechaInicio(29, 10, 2024);
    int numPuntos = std::min(50, static_cast<int>(puntosRecarga.size()));
    int usuariosMostrados = 0;
    size_t indexPunto = 0;

    for (Usuario &usuario: usuarios) {
        if (usuario.getNombre().substr(0, 1) == "W") {
            std::cout << "Asignando coche a usuario: " << usuario.getNombre() << std::endl;
            bool cocheAsignado = false;
            Coche *cocheAlquilado = nullptr;
            PuntoRecarga *puntoOrigen = nullptr;

            for (int intentos = 0; intentos < numPuntos; ++intentos) {
                puntoOrigen = &puntosRecarga[indexPunto];
                indexPunto = (indexPunto + 1) % numPuntos;

                if (puntoOrigen->getNumCoches() > 0) {
                    PuntoRecarga *puntoDestino = &puntosRecarga[(puntoOrigen->getId() + 1)];
                    cocheAlquilado = usuario.cogecoche(puntoOrigen->getId(), puntoDestino->getId(), fechaInicio);

                    if (cocheAlquilado) {
                        cocheAsignado = true;
                        break;
                    }
                }
            }

            if (!cocheAsignado) {
                std::cerr << "No se pudo alquilar un coche para el usuario " << usuario.getNombre() << std::endl;
                continue;
            }

            PuntoRecarga *puntoDestino = &puntosRecarga[(puntoOrigen->getId() + 1 - 1) % numPuntos];
            Trayecto *trayecto = usuario.crearTrayecto(puntoOrigen, puntoDestino, fechaInicio);

            if (!trayecto) {
                std::cerr << "Error al crear trayecto para el usuario: " << usuario.getNombre() << std::endl;
                continue;
            }

            Fecha fechaFin = fechaInicio;
            fechaFin.anadirDias(2 + rand() % 3);
            trayecto->finalizarTrayecto(fechaFin);

            if (usuariosMostrados < 10) {
                std::cout << "Usuario: " << usuario.getNombre() << ", NIF: " << usuario.getNif() << std::endl;
                std::cout << "Coche alquilado: " << cocheAlquilado->getIdMatricula() << ", Marca: "
                          << cocheAlquilado->getMarca() << ", Modelo: " << cocheAlquilado->getModelo() << std::endl;
                std::cout << "Trayecto: ID " << trayecto->getidTrayecto() << ", Punto origen: " << puntoOrigen->getId()
                          << ", Punto destino: " << puntoDestino->getId() << std::endl;
                std::cout << "Fecha de inicio: " << fechaInicio.cadena() << ", Fecha de fin: " << fechaFin.cadena()
                          << std::endl;
                std::cout << "--------------------------------------------------" << std::endl;
                ++usuariosMostrados;
            }
        }
    }
}

/**
 * @brief Aparca los coches alquilados por los usuarios en los puntos de recarga.
 * @param reanelcar Referencia al objeto de tipo Reanelcar con los usuarios y puntos de recarga.
 */
void aparcarCochesUsuario(Reanelcar &reanelcar) {
    std::list<Usuario> &usuarios = reanelcar.getUsuarios();
    int usuariosmostrados = 0;

    for (Usuario &usuario: usuarios) {
        if (usuario.getNombre().substr(0, 2) == "Wa" && usuario.getCochealquilado()) {
            Trayecto *trayecto = usuario.getUltimoTrayecto();
            if (trayecto) {
                PuntoRecarga *destino = reanelcar.getPuntoRecargaID(trayecto->getDestination()->getId());
                if (destino) {
                    usuario.aparcaCoche(destino);

                    if (usuariosmostrados < 10) {
                        std::cout << " Usuario: " << usuario.getNombre() << " NIF: " << usuario.getNif() << std::endl;
                        std::cout << " Coche aparcado: " << usuario.getCochealquilado()->getIdMatricula() << std::endl;
                        std::cout << " Trayecto: ID: " << trayecto->getidTrayecto() << " Punto origen: "
                                  << trayecto->getOrigin()->getId() << " Punto de destino: "
                                  << trayecto->getDestination()->getId() << std::endl;
                        std::cout << "--------------------------------------------------" << std::endl;

                        ++usuariosmostrados;
                    }
                } else {
                    std::cerr << " Error: Punto de recarga de destino no encontrado para el trayecto. " << std::endl;
                }
            } else {
                std::cerr << " No se encontro el ultimo trayecto para el usuario: " << usuario.getNombre() << std::endl;
            }
        }
    }
}

/**
 * @brief Alquila coches a los usuarios cuyo nombre comienza con "Wa" y les asigna un trayecto.
 * @param reanelcar Referencia al objeto de tipo Reanelcar con los usuarios y puntos de recarga.
 */
void alquilarCochesUsuariosWa(Reanelcar &reanelcar) { // Los usuarios salen todos del mismo punto.
    std::list<Usuario> &usuarios = reanelcar.getUsuarios();
    std::vector<PuntoRecarga> &puntosRecarga = reanelcar.getSitios();
    int usuariosmostrados = 0;

    Fecha fechainicio(29, 10, 2024);

    for (Usuario &usuario: usuarios) {
        if (usuario.getNombre().substr(0, 2) == "Wa" && usuariosmostrados < 10) {
            std::cout << "Asignando coche a: " << usuario.getNombre() << std::endl;

            bool cocheasignado = false;
            Coche *cochealquilado = nullptr;
            PuntoRecarga *puntoOrigen = nullptr;

            for (PuntoRecarga &puntoRecarga: puntosRecarga) {
                if (puntoRecarga.getNumCoches() > 0) {
                    cochealquilado = usuario.cogecoche(puntoRecarga.getId(),
                                                       (puntoRecarga.getId() + 1 - 1) % puntosRecarga.size(),
                                                       fechainicio);
                    if (cochealquilado) {
                        cocheasignado = true;
                        puntoOrigen = &puntoRecarga;
                        break;
                    }
                }
            }
            if (cocheasignado && puntoOrigen) {
                PuntoRecarga *puntoDestino = &puntosRecarga[(puntoOrigen->getId() + 1) % puntosRecarga.size()];
                Trayecto *trayecto = usuario.crearTrayecto(puntoOrigen, puntoDestino, fechainicio);

                if (trayecto) {
                    Fecha fechaFin = fechainicio;
                    fechaFin.anadirDias(2 + rand() % 3);
                    trayecto->finalizarTrayecto(fechaFin);

                    std::cout << "Usuario: " << usuario.getNombre() << ", NIF: " << usuario.getNif() << std::endl;
                    std::cout << "Coche alquilado: " << cochealquilado->getIdMatricula() << ", Marca: "
                              << cochealquilado->getMarca() << ", Modelo: " << cochealquilado->getModelo() << std::endl;
                    std::cout << "Trayecto: ID " << trayecto->getidTrayecto() << ", Punto origen: "
                              << puntoOrigen->getId() << ", Punto destino: " << puntoDestino->getId() << std::endl;
                    std::cout << "Fecha de inicio: " << fechainicio.cadena() << ", Fecha de fin: " << fechaFin.cadena()
                              << std::endl;
                    std::cout << "--------------------------------------------------" << std::endl;

                    ++usuariosmostrados;
                } else {
                    std::cerr << "Error al crear trayecto para el usuario: " << usuario.getNombre() << std::endl;
                }
            } else {
                std::cerr << "No se pudo asignar un coche para el usuario: " << usuario.getNombre() << std::endl;
            }
        }
    }
}

/**
 * @brief Muestra el número de usuarios que han realizado más de un trayecto en la fecha actual.
 * @param reanelcar Referencia al objeto de tipo Reanelcar con los usuarios.
 */
void mostrarUsuariosConMultiplesTrayectos(Reanelcar &reanelcar) {
    Fecha fecha(29, 10, 2024);
    int usuarios = 0;

    for (Usuario &usuario: reanelcar.getUsuarios()) {
        int trayectos = 0;
        for (std::pair<const Fecha, Trayecto *> const &parTrayecto: usuario.getTrayectos()) {
            Trayecto *trayecto = parTrayecto.second;

            if (trayecto->getfechaInicio().verDia() == fecha.verDia() &&
                trayecto->getfechaInicio().verMes() == fecha.verMes() &&
                trayecto->getfechaInicio().verAnio() == fecha.verAnio()) {
                trayectos++;
            }
        }

        if (trayectos > 1) {
            usuarios++;
        }
    }
    std::cout << "Numero de usuarios que han realizado mas de un trayecto hoy: " << usuarios << std::endl;
}

/**
 * @brief Muestra los trayectos realizados en una fecha específica.
 * @param reanelcar Referencia al objeto de tipo Reanelcar con los trayectos y usuarios.
 * @param fechaConsulta La fecha para la cual se quieren mostrar los trayectos.
 */
void mostrarTrayectosEnFecha(Reanelcar &reanelcar, Fecha fechaConsulta) {
    std::vector<std::pair<Usuario, Trayecto>> trayectos = reanelcar.trayectosEnFecha(fechaConsulta);

    if (trayectos.empty()) {
        std::cout << "No se encontraron trayectos para la fecha " << fechaConsulta.cadena() << std::endl;
    } else {
        std::cout << "Trayectos realizados el " << fechaConsulta.cadena() << ":\n";
        for (std::pair<Usuario, Trayecto> &par: trayectos) {
            Usuario &usuario = par.first;
            Trayecto &trayecto = par.second;

            std::cout << "Usuario: " << usuario.getNombre() << ", NIF: " << usuario.getNif() << "\n";
            std::cout << "Trayecto ID: " << trayecto.getidTrayecto()
                      << ", Origen: " << trayecto.getOrigin()->getId()
                      << ", Destino: " << trayecto.getDestination()->getId() << "\n";
            std::cout << "Fecha de inicio: " << trayecto.getfechaInicio().cadena() << std::endl;
            std::cout << "-------------------------------------------\n";
        }
    }
}

int main() {
    Reanelcar reanelcar;

    std::cout << "Cargando datos de usuarios..." << std::endl;
    cargarUsuarios("../usuarios1.csv", reanelcar);
    std::cout << "Cargando datos de coches..." << std::endl;
    cargarCoches("../coches_v2.csv", reanelcar);
    std::cout << "Cargando datos de puntos de recarga..." << std::endl;
    cargarPuntosRecarga("../puntos_recarga.csv", reanelcar);

    distribuirCochesPorBateria(reanelcar);

    contarCapacidadTotal(reanelcar.getSitios());

    asignarCochesYCrearTrayectos(reanelcar);

    aparcarCochesUsuario(reanelcar);

    alquilarCochesUsuariosWa(reanelcar);

    mostrarUsuariosConMultiplesTrayectos(reanelcar);
    std::string matricula_a_buscar = "6698 XKM";
    reanelcar.mostrarDatosCoche(matricula_a_buscar);

    Fecha fechaConsulta(29, 10, 2024);

    mostrarTrayectosEnFecha(reanelcar, fechaConsulta);

    return 0;
}