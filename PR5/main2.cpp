/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file main2.cpp
 * @brief Segundo archivo de pruebas
 * @note A la hora de mostrar los datos de un usuario en concreto se borran todos los trayectos
 * y coche asociado sin motivo aparente
 * @note La implementación del ejercicio de parejas está realizada pero no se llama en el main porque
 * desajusta la tabla
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
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
                    cocheAsignado = true;
                }
            }

            indexPunto = (indexPunto + 1) % puntosRecarga.size();

            if (!cocheAsignado && indexPunto == 0) {
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

    std::cout << std::endl << "Capacidad maxima total de todos los puntos de recarga: " << capacidadMaximaTotal
              << std::endl;
    std::cout << "Numero total de coches asignados en los puntos de recarga: " << cochesAsignadosTotal << std::endl;

    if (cochesAsignadosTotal < capacidadMaximaTotal) {
        std::cout << "Aun hay espacio disponible en los puntos de recarga." << std::endl;
    } else {
        std::cout << "Todos los puntos de recarga estan ocupados al maximo de su capacidad." << std::endl << std::endl;
    }
}

/**
 * @brief Asigna coches a los usuarios y crea trayectos de acuerdo a los puntos de recarga disponibles.
 * @param reanelcar Referencia al objeto de tipo Reanelcar con los usuarios y puntos de recarga.
 * @note Es la misma función de la práctica anterior
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

    Fecha fechaInicio(12, 11, 2024);
    int numPuntos = std::min(50, static_cast<int>(puntosRecarga.size()));
    int usuariosMostrados = 0;
    size_t indexPunto = 0;

    for (Usuario &usuario: usuarios) {
        if (usuario.getNombre().substr(0, 1) == "W") {
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
 * @brief Muestra la información detallada de un usuario en el sistema.
 *
 * Esta función busca un usuario por su NIF en el sistema Reanelcar, y muestra su nombre, NIF,
 * información sobre el coche alquilado (si tiene uno) y los trayectos realizados por el usuario,
 * incluyendo detalles sobre el origen, destino, el coche involucrado y las fechas de inicio y fin.
 * Si no se encuentra el usuario, se muestra un mensaje de error.
 *
 * @param nifabuscar NIF del usuario a buscar.
 * @param reanelcar Sistema Reanelcar en el que se buscará al usuario.
 */
void mostrarInformacionUsuario(std::string &nifabuscar, Reanelcar &reanelcar) {
    Usuario *usuario = reanelcar.buscarUsrNifThash(nifabuscar);

    if (usuario) {
        std::cout << "Usuario: " << usuario->getNombre() << ", NIF: " << usuario->getNif() << std::endl;

        Coche *coche = usuario->getCochealquilado();
        if (coche) {
            std::cout << "Coche alquilado: " << coche->getIdMatricula() << ", Marca: "
                      << coche->getMarca() << ", Modelo: " << coche->getModelo() << std::endl;
        } else {
            std::cout << "El usuario no tiene un coche alquilado." << std::endl;
        }

        std::multimap<Fecha, Trayecto *> trayectos = usuario->getTrayectos();
        if (!trayectos.empty()) {
            std::cout << "Trayectos del usuario:" << std::endl;
            for (std::pair<const Fecha,Trayecto*> const &par: trayectos) {
                Trayecto *trayecto = par.second;

                std::cout << "Trayecto ID: " << trayecto->getidTrayecto() << std::endl;

                if (trayecto->getOrigin() && trayecto->getDestination()) {
                    std::cout << "Origen: " << trayecto->getOrigin()->getId() << ", "
                              << "Destino: " << trayecto->getDestination()->getId() << std::endl;
                } else {
                    std::cout << "Origen o destino no disponibles." << std::endl;
                }

                if (trayecto->getinthecar()) {
                    std::cout << "Coche involucrado: " << trayecto->getinthecar()->getIdMatricula() << ", "
                              << trayecto->getinthecar()->getMarca() << " " << trayecto->getinthecar()->getModelo()
                              << std::endl;
                } else {
                    std::cout << "Coche no disponible para este trayecto." << std::endl;
                }

                std::cout << "Fecha de inicio: " << trayecto->getfechaInicio() << ", "
                          << "Fecha de fin: " << trayecto->getfechaFin() << std::endl;
                std::cout << "--------------------------------------------------" << std::endl;
            }
        } else {
            std::cout << "El usuario no tiene trayectos registrados." << std::endl;
        }

    } else {
        std::cout << "No se encontro el usuario con NIF: " << nifabuscar << std::endl;
    }

    std::cout << "--------------------------------------------------" << std::endl;
}

/**
 * @brief Alquila coches y muestra información sobre los primeros usuarios con nombres que empiezan con "Wi".
 *
 * Esta función recorre la lista de usuarios del sistema Reanelcar y asigna coches a aquellos cuyos nombres
 * empiezan con "Wi". Además, crea trayectos entre puntos de recarga disponibles y muestra información
 * detallada sobre los usuarios, los coches alquilados y los trayectos. La función termina cuando se muestran
 * 10 usuarios o si no hay puntos de recarga disponibles. Si no se puede alquilar un coche para un usuario,
 * se muestra un mensaje de error.
 *
 * @param reanelcar Sistema Reanelcar que contiene los usuarios y los puntos de recarga.
 */
void alquilarYMostrarPrimerosUsuariosWiConCocheYTrayecto(Reanelcar &reanelcar) {
    std::list<Usuario> &usuarios = reanelcar.getUsuarios();
    std::vector<PuntoRecarga> &puntosRecarga = reanelcar.getSitios();

    if (puntosRecarga.empty()) {
        std::cerr << "Error: No hay puntos de recarga disponibles." << std::endl;
        return;
    }

    for (Usuario &usuario: usuarios) {
        usuario.setLinkReanelcar(&reanelcar);
    }

    Fecha fechaInicio(12, 11, 2024);
    int numPuntos = std::min(50, static_cast<int>(puntosRecarga.size()));
    int usuariosMostrados = 0;
    size_t indexPunto = 0;

    for (Usuario &usuario: usuarios) {
        if (usuario.getNombre().substr(0, 2) == "Wi") {
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

int main() {

    /**
     * Prueba 1:
     */
    Reanelcar reanelcar;

    std::cout << "Cargando datos de usuarios..." << std::endl;
    cargarUsuarios("../usuarios1.csv", reanelcar);
    std::cout << "Cargando datos de coches..." << std::endl;
    cargarCoches("../coches_v2.csv", reanelcar);
    std::cout << "Cargando datos de puntos de recarga..." << std::endl;
    std::cout << std::endl;
    cargarPuntosRecarga("../puntos_recarga.csv", reanelcar);

    /**
     * Prueba 2:
     */
    reanelcar.configurarTablaHashAuto(ThashUsuario::DOBLE);
    std::cout << std::endl;

    /**
     * Prueba 3:
     */
    distribuirCochesPorBateria(reanelcar);

    contarCapacidadTotal(reanelcar.getSitios());

    asignarCochesYCrearTrayectos(reanelcar);

    /**
     * Prueba 4:
     */
    std::string prefijo1 = "Wi";
    reanelcar.mostrarTrayectosUsuariosWi(prefijo1, 2);

    /**
     * Prueba 5:
     */
    std::string nifabuscar = "84538382N";
    mostrarInformacionUsuario(nifabuscar, reanelcar);
    // NOTA: Elimina la información del coche buscado y trayectos sin motivo aparente

    /**
     * Prueba 6:
     */
    reanelcar.eliminarYReinsertarUsuario(nifabuscar);

    /**
     * Prueba 7:
     */
    std::cout << std::endl;
    std::string prefijo = "Wa";
    reanelcar.eliminarUsuariosPorNombre(prefijo);

    /**
     * Prueba 8:
     */
    std::cout << std::endl;
    alquilarYMostrarPrimerosUsuariosWiConCocheYTrayecto(reanelcar);

    /**
     * Prueba 9:
     */
    std::string prefijo2 = "Wil";
    reanelcar.mostrarTrayectosUsuariosWil(prefijo2, 4);

    return 0;
}