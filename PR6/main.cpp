/**
 *  @author David Fernández Espejo, dfe00004@red.ujaen.es
 *  @author David Lorente Wagner, dlw00001@red.ujaen.es
 *  @file main.cpp
 *  @brief Archivo de prueba del programa principal
 *  @note Completado
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "Reanelcar.h"
#include "img.h"

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
 * @brief struct que representa los datos de un posterior ejercicio
 */
struct DatosGeograficos {
    std::vector<std::pair<std::string, UTM>> usuarios;
    float latmin, latmax, lonmin, lonmax;
};

/**
 * @brief Carga información geográfica desde un archivo CSV y calcula límites geográficos.
 *
 * Esta función procesa un archivo CSV que contiene datos de usuarios y sus posiciones geográficas
 * (latitud y longitud). Calcula los límites geográficos ampliados de las coordenadas y almacena los datos
 * en un objeto `DatosGeograficos`.
 *
 * @param rutaArchivo Ruta al archivo CSV que contiene los datos de entrada.
 * @param reanelcar Referencia a un objeto Reanelcar para gestión adicional (si aplica).
 * @return Un objeto `DatosGeograficos` con los usuarios, posiciones UTM y límites calculados.
 *
 * @note Se espera que el archivo contenga una línea de encabezado que será ignorada.
 *       Las coordenadas geográficas de cada usuario se ajustan en +/- 0.01 para calcular los límites.
 */
DatosGeograficos cargarDestino(const std::string &rutaArchivo, Reanelcar &reanelcar) {
    std::ifstream archivo;
    if (!abrirArchivo(archivo, rutaArchivo)) return {{}, 0, 0, 0, 0};

    std::string fila;
    bool primeraLinea = true;

    float latMin = std::numeric_limits<float>::max();
    float latMax = std::numeric_limits<float>::lowest();
    float lonMin = std::numeric_limits<float>::max();
    float lonMax = std::numeric_limits<float>::lowest();

    std::vector<std::pair<std::string, UTM>> usuariosUTM;

    while (std::getline(archivo, fila)) {
        if (primeraLinea) {
            primeraLinea = false;
            continue;
        }

        if (fila.empty()) continue;

        std::stringstream columnas(fila);
        std::string usuario;
        float lat, lon;

        std::getline(columnas, usuario, ',');
        columnas >> lat;
        columnas.ignore(1, ',');
        columnas >> lon;

        latMin = std::min(latMin, lat - 0.01f);
        latMax = std::max(latMax, lat + 0.01f);
        lonMin = std::min(lonMin, lon - 0.01f);
        lonMax = std::max(lonMax, lon + 0.01f);

        UTM posicion(lat, lon);
        usuariosUTM.emplace_back(usuario, posicion);
    }

    archivo.close();

    std::cout << "Latitud minima: " << latMin << ", maxima: " << latMax << std::endl;
    std::cout << "Longitud minima: " << lonMin << ", maxima: " << lonMax << std::endl;

    return {usuariosUTM, latMin, latMax, lonMin, lonMax};
}

/**
 * @brief Distribuye coches eléctricos a puntos de recarga según el nivel de batería.
 *
 * Esta función organiza los coches en un sistema de recarga eléctrica. Los coches con mayor nivel de batería
 * son procesados primero. Cada coche se asigna al primer punto de recarga con capacidad disponible.
 * Los coches no asignados se almacenan en una lista para informar de la asignación incompleta.
 *
 * @param reanelcar Referencia a un objeto Reanelcar que gestiona coches y puntos de recarga.
 *
 * @note Los puntos de recarga se evalúan de manera circular para distribuir la carga de forma equitativa.
 *       Se genera una lista de coches que no pudieron ser asignados por falta de capacidad.
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
    size_t cochesAsignados = 0;
    size_t totalCoches = coches.size();
    std::vector<std::string> cochesNoAsignados;

    for (auto it = cochesPorBateria.rbegin(); it != cochesPorBateria.rend(); ++it) {
        Coche *coche = it->second;
        bool cocheAsignado = false;

        for (size_t intentos = 0; intentos < puntosRecarga.size(); ++intentos) {
            PuntoRecarga &puntoRecarga = puntosRecarga[indexPunto];

            if (puntoRecarga.getNumCoches() < puntoRecarga.getMax()) {
                if (puntoRecarga.addCoche(coche)) {
                    cocheAsignado = true;
                    ++cochesAsignados;
                    break;
                }
            }

            indexPunto = (indexPunto + 1) % puntosRecarga.size();
        }

        if (!cocheAsignado) {
            cochesNoAsignados.push_back(coche->getIdMatricula());
        }
    }

    std::cout << "Distribucion de coches completada." << std::endl;
    std::cout << "Total coches procesados: " << totalCoches << std::endl;
    std::cout << "Coches asignados: " << cochesAsignados << std::endl;
    std::cout << "Coches no asignados: " << cochesNoAsignados.size() << std::endl;

    if (!cochesNoAsignados.empty()) {
        std::cerr << "Los siguientes coches no pudieron ser asignados:" << std::endl;
        for (const std::string &matricula: cochesNoAsignados) {
            std::cerr << "  - " << matricula << std::endl;
        }
    }
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

    std::cout << std::endl << "Capacidad maxima total de todos los puntos de recarga: " << capacidadMaximaTotal - 1
              << std::endl;
    std::cout << "Numero total de coches asignados en los puntos de recarga: " << cochesAsignadosTotal << std::endl;

    if (cochesAsignadosTotal < capacidadMaximaTotal - 1) {
        std::cout << "Aun hay espacio disponible en los puntos de recarga." << std::endl;
    } else {
        std::cout << "Todos los puntos de recarga estan ocupados al maximo de su capacidad." << std::endl
                  << std::endl;
    }
}

/**
 * @brief Asigna coches a los usuarios cuyo nombre comienza con una letra específica y crea trayectos.
 *
 * @param letra Letra con la que deben comenzar los nombres de los usuarios.
 * @param reanelcar Objeto Reanelcar que contiene los datos de usuarios, coches y puntos de recarga.
 * @param indexpunto Índice inicial para seleccionar puntos de recarga de forma circular.
 */
void asignarCochesYCrearTrayectosParaUsuarios(std::string &letra, Reanelcar &reanelcar, size_t &indexpunto) {

    std::list<Usuario> &usuarios = reanelcar.getUsuarios();
    std::vector<PuntoRecarga> &puntosRecarga = reanelcar.getSitios();

    if (usuarios.empty()) {
        std::cerr << "Error: No hay usuarios disponibles. " << std::endl;
        return;
    }

    if (puntosRecarga.empty()) {
        std::cerr << "Error: No hay puntos de recarga disponibles. " << std::endl;
        return;
    }

    for (Usuario &usuario: usuarios) {
        usuario.setLinkReanelcar(&reanelcar);
    }

    Fecha fechainicio(25, 11, 2024);
    unsigned idTrayecto = 1;
    int usuariosMostrados = 0;

    for (Usuario &usuario: usuarios) {
        if (usuario.getNombre().substr(0, 1) == letra) {
            bool cocheAsignado = false;
            Coche *cocheAlquilado = nullptr;
            PuntoRecarga *puntoOrigen = nullptr;

            for (size_t intentos = 0; intentos < puntosRecarga.size(); ++intentos) {
                puntoOrigen = &puntosRecarga[indexpunto];
                indexpunto = (indexpunto + 1) % puntosRecarga.size(); // Avanzar el índice

                if (puntoOrigen->getNumCoches() > 0) {
                    PuntoRecarga *puntoDestino = &puntosRecarga[(puntoOrigen->getId()) % puntosRecarga.size()];
                    cocheAlquilado = usuario.cogecoche(puntoOrigen->getId(), puntoDestino->getId(), fechainicio);

                    if (cocheAlquilado) {
                        cocheAsignado = true;
                        break;
                    }
                }
            }

            if (!cocheAsignado) {
                std::cerr << " No se pudo alquilar el coche para el usuario: " << usuario.getNombre() << std::endl;
                continue;
            }

            PuntoRecarga *puntoDestino = &puntosRecarga[(puntoOrigen->getId()) % puntosRecarga.size()];
            Trayecto *trayecto = usuario.crearTrayecto(puntoOrigen, puntoDestino, fechainicio);

            if (!trayecto) {
                std::cerr << " Error al crear trayecto para el usuario: " << usuario.getNombre() << std::endl;
                continue;
            }

            Fecha fechaFin = fechainicio;
            fechaFin.anadirDias(1 + rand() % 2);
            trayecto->finalizarTrayecto(fechaFin);

            if (usuariosMostrados < 10) {
                std::cout << "Usuario: " << usuario.getNombre() << ", NIF: " << usuario.getNif() << std::endl;
                std::cout << "Coche alquilado: " << cocheAlquilado->getIdMatricula() << ", Marca: "
                          << cocheAlquilado->getMarca() << ", Modelo: " << cocheAlquilado->getModelo() << std::endl;
                std::cout << "Trayecto: ID " << trayecto->getidTrayecto() << ", Punto origen: "
                          << puntoOrigen->getId()
                          << ", Punto destino: " << puntoDestino->getId() << std::endl;
                std::cout << "Fecha de inicio: " << fechainicio.cadena() << ", Fecha de fin: " << fechaFin.cadena()
                          << std::endl;
                std::cout << "--------------------------------------------------" << std::endl;
                ++usuariosMostrados;
            }
        }
    }
    std::cout << " Asignacion completada. " << std::endl;
}

/**
 * @brief Aparca coches para los usuarios cuyo nombre comienza con una letra específica y muestra datos relevantes.
 *
 * @param letra Letra con la que deben comenzar los nombres de los usuarios.
 * @param reanelcar Objeto Reanelcar que contiene los datos de usuarios, coches y puntos de recarga.
 */
void aparcarCochesYMostrarDatos(std::string &letra, Reanelcar &reanelcar) {
    std::list<Usuario> &usuarios = reanelcar.getUsuarios();
    std::vector<PuntoRecarga> &puntosRecarga = reanelcar.getSitios();
    MallaRegular<Coche *> &malla = reanelcar.getMallaRegular();

    int usuariosMostrados = 0;

    for (Usuario &usuario: usuarios) {
        if (usuario.getNombre().substr(0, 1) == letra) {
            Trayecto *trayecto = usuario.getUltimoTrayecto();

            if (trayecto == nullptr) {
                std::cerr << "Error: El usuario " << usuario.getNombre() << " no tiene un trayecto válido."
                          << std::endl;
                continue;
            }

            PuntoRecarga *puntoDestino = reanelcar.getPuntoRecargaID(trayecto->getDestination()->getId());

            if (!puntoDestino) {
                std::cerr << "Error: No se encontró el punto de recarga destino para el trayecto del usuario "
                          << usuario.getNombre() << std::endl;
                continue;
            }

            Coche *coche = trayecto->getinthecar();

            if (!coche) {
                std::cerr << "Error: No se encontró un coche asociado al trayecto del usuario "
                          << usuario.getNombre() << std::endl;
                continue;
            }

            usuario.aparcaCoche(coche, puntoDestino, puntoDestino);

            UTM posicion = puntoDestino->getPosicion();
            malla.insertar(posicion.getLat(), posicion.getLon(), coche);

            if (usuariosMostrados < 10) {
                std::cout << "Usuario: " << usuario.getNombre() << ", NIF: " << usuario.getNif() << std::endl;
                std::cout << "Coche aparcado: " << coche->getIdMatricula() << ", Marca: " << coche->getMarca()
                          << ", Modelo: " << coche->getModelo() << std::endl;
                std::cout << "Trayecto: ID " << trayecto->getidTrayecto() << ", Punto origen: "
                          << trayecto->getOrigin()->getId() << ", Punto destino: "
                          << trayecto->getDestination()->getId()
                          << std::endl;
                std::cout << "Fecha de inicio: " << trayecto->getfechaInicio().cadena()
                          << ", Fecha de fin: " << trayecto->getfechaFin().cadena() << std::endl;
                std::cout << "Puntos acumulados: " << usuario.getPuntos() << std::endl;
                std::cout << "--------------------------------------------------" << std::endl;

                ++usuariosMostrados;
            }
        }
    }

    unsigned int maxElementos = malla.maxElementosPorCelda();
    float promedioElementos = malla.promedioElementosPorCelda();
    Casilla<Coche *> *casillaMasLlena = malla.casillaMasPoblada();

    std::cout << std::endl;
    std::cout << "Maximo de elementos por casilla: " << maxElementos << std::endl;
    std::cout << "Promedio de elementos por casilla: " << promedioElementos << std::endl;

    if (casillaMasLlena) {
        std::cout << "Casilla mas poblada:" << std::endl;

        std::cout << "Lista de coches en la casilla:" << std::endl;
        for (Coche *&coche: casillaMasLlena->getPuntos()) {
            std::cout << "  - Matricula: " << coche->getIdMatricula() << ", Marca: " << coche->getMarca()
                      << ", Modelo: " << coche->getModelo() << std::endl;
        }
    } else {
        std::cout << "No se encontraron casillas pobladas en la malla." << std::endl;
    }
}

/**
 * @brief Aparca coches en posiciones especificadas por un vector y muestra datos relevantes.
 *
 * @param vectorPosiciones Vector de pares que asocia nombres de usuarios con posiciones UTM.
 * @param reanelcar Objeto Reanelcar que contiene los datos de usuarios, coches y puntos de recarga.
 * @param letra Letra con la que deben comenzar los nombres de los usuarios.
 */
void aparcarCochesPorVectorDePosicionesYMostrar(std::vector<std::pair<std::string, UTM>> &vectorPosiciones,
                                                Reanelcar &reanelcar, std::string &letra) {
    int usuariosProcesados = 0;
    int idPuntoRecargaTemporal = 1;
    std::vector<PuntoRecarga> puntosRecargaTemporales;

    std::list<Usuario> &usuarios = reanelcar.getUsuarios();
    MallaRegular<Coche *> &mallaRegular = reanelcar.getMallaRegular();

    for (Usuario &usuario: usuarios) {
        if (usuario.getNombre().substr(0, 1) == letra) {
            auto it = std::find_if(vectorPosiciones.begin(), vectorPosiciones.end(),
                                   [&usuario](const std::pair<std::string, UTM> &pos) {
                                       return pos.first == usuario.getNombre();
                                   });
            if (it == vectorPosiciones.end()) {
                std::cerr << "No se encontro una posicion para el usuario: " << usuario.getNombre() << std::endl;
                continue;
            }

            UTM posicionAsignada = it->second;

            PuntoRecarga *puntoDestinoTemporal = nullptr;

            for (PuntoRecarga &puntoRecarga: reanelcar.getSitios()) {
                if (puntoRecarga.getPosicion() == posicionAsignada) {
                    puntoDestinoTemporal = &puntoRecarga;
                    break;
                }
            }

            if (!puntoDestinoTemporal) {
                PuntoRecarga nuevoPuntoTemporal(idPuntoRecargaTemporal++, posicionAsignada);
                puntosRecargaTemporales.push_back(nuevoPuntoTemporal);
                puntoDestinoTemporal = &puntosRecargaTemporales.back();
            }

            Trayecto *trayecto = usuario.getUltimoTrayecto();
            if (!trayecto) {
                std::cerr << "Error: El usuario " << usuario.getNombre() << " no tiene un trayecto válido."
                          << std::endl;
                continue;
            }

            Coche *coche = trayecto->getinthecar();
            if (!coche) {
                std::cerr << "Error: No hay un coche asociado al trayecto del usuario " << usuario.getNombre()
                          << std::endl;
                continue;
            }

            PuntoRecarga *puntoPrevistoTrayecto = trayecto->getDestination();
            if (!puntoPrevistoTrayecto) {
                std::cerr << "Error: El trayecto del usuario " << usuario.getNombre()
                          << "no tiene punto de recarga previsto. " << std::endl;
                continue;
            }

            usuario.aparcaCoche(coche, puntoDestinoTemporal, puntoPrevistoTrayecto);

            mallaRegular.insertar(posicionAsignada.getLat(), posicionAsignada.getLon(), coche);

            vectorPosiciones.erase(it);

            if (usuariosProcesados < 10) {
                std::cout << "Usuario: " << usuario.getNombre() << ", NIF: " << usuario.getNif() << std::endl;
                std::cout << "Coche aparcado: " << coche->getIdMatricula() << ", Marca: " << coche->getMarca()
                          << ", Modelo: " << coche->getModelo() << std::endl;
                std::cout << "Trayecto: ID " << trayecto->getidTrayecto()
                          << ", Punto origen: " << trayecto->getOrigin()->getId()
                          << ", Punto destino: " << trayecto->getDestination()->getId() << std::endl;
                std::cout << "Fecha de inicio: " << trayecto->getfechaInicio().cadena()
                          << ", Fecha de fin: " << trayecto->getfechaFin().cadena() << std::endl;
                std::cout << "Puntos acumulados: " << usuario.getPuntos() << std::endl;
                std::cout << "--------------------------------------------------" << std::endl;

                ++usuariosProcesados;
            }
        }
    }

    if (usuariosProcesados == 0) {
        std::cerr << " No se encontraron usuarios cuyo nombre empiece con 'A'. " << std::endl;
    } else {
        std::cout << " Se procesaron y mostaron datos de " << usuariosProcesados << " usuarios." << std::endl;
    }

    unsigned int maxElementos = mallaRegular.maxElementosPorCelda();
    float promedioElementos = mallaRegular.promedioElementosPorCelda();
    Casilla<Coche *> *casillaMasLlena = mallaRegular.casillaMasPoblada();

    std::cout << std::endl;
    std::cout << "Maximo de elementos por casilla: " << maxElementos << std::endl;
    std::cout << "Promedio de elementos por casilla: " << promedioElementos << std::endl;
    std::cout << "Total de elementos en la malla: " << mallaRegular.getTotalCoches() << std::endl;

    if (casillaMasLlena) {
        std::cout << "Casilla mas poblada:" << std::endl;

        std::cout << "Lista de coches en la casilla:" << std::endl;
        for (Coche *&coche: casillaMasLlena->getPuntos()) {
            std::cout << "  - Matricula: " << coche->getIdMatricula() << ", Marca: " << coche->getMarca()
                      << ", Modelo: " << coche->getModelo() << std::endl;
        }
    } else {
        std::cout << "No se encontraron casillas pobladas en la malla." << std::endl;
    }
}

/**
 * @brief Busca coches en un radio específico desde una ubicación central.
 *
 * @param reanelcar Objeto Reanelcar que contiene los datos de usuarios, coches y puntos de recarga.
 * @param latCentro Latitud del centro del área de búsqueda.
 * @param lonCentro Longitud del centro del área de búsqueda.
 * @param radio Radio en kilómetros para realizar la búsqueda.
 */
void buscarCochesCercanos(Reanelcar &reanelcar, float latCentro, float lonCentro, float radio) {
    MallaRegular<Coche *> &mallaRegular = reanelcar.getMallaRegular();
    std::vector<Coche *> cochesCercanos = mallaRegular.buscarRadio(latCentro, lonCentro, radio);

    if (cochesCercanos.empty()) {
        std::cerr << "No se encontraron coches en un radio de: " << radio << " km del centro especificado. "
                  << std::endl;
        return;
    }

    Coche *cocheMasCercano = nullptr;
    float distanciaMinima = std::numeric_limits<float>::max();

    std::cout << "Coches encontrados en un radio de: " << radio << " km: " << std::endl;
    for (Coche *coche: cochesCercanos) {
        if (!coche || !coche->getPuntoRecarga()) continue;

        UTM posicionCoche = coche->getPuntoRecarga()->getPosicion();
        float distancia = mallaRegular.distanciaHaversine(latCentro, lonCentro, posicionCoche.getLat(),
                                                          posicionCoche.getLon());

        // Esto es para ignorar los coches que estén aparcados en el propio punto de recarga para la prueba 10
        if (distancia == 0) continue;

        if (distancia < distanciaMinima) {
            distanciaMinima = distancia;
            cocheMasCercano = coche;
        }

        std::cout << "Matricula: " << coche->getIdMatricula() << " Marca: " << coche->getMarca() << " Modelo: "
                  << coche->getModelo() << "Distancia: " << distancia << " km." << std::endl;
    }

    if (cocheMasCercano) {
        std::cout << "El coche mas cercano al centro especificado es: " << std::endl;
        std::cout << "Matricula: " << cocheMasCercano->getIdMatricula() << " Marca: " << cocheMasCercano->getMarca()
                  << " Modelo: " << cocheMasCercano->getModelo() << " Distancia: " << distanciaMinima << std::endl;
    }
}

/**
 * @brief Muestra los coches más cercanos a un punto de recarga específico.
 *
 * @param reanelcar Objeto Reanelcar que contiene los datos de usuarios, coches y puntos de recarga.
 * @param idPuntoRecarga ID del punto de recarga al que se buscarán coches cercanos.
 */
void mostrarCochesMasCercanoAPunto(Reanelcar &reanelcar, int idPuntoRecarga) {
    PuntoRecarga *puntoRecarga = reanelcar.getPuntoRecargaID(idPuntoRecarga);

    if (!puntoRecarga) {
        std::cerr << "Error: No se encontro el punto de recarga con ID " << idPuntoRecarga << ". " << std::endl;
        return;
    }

    UTM posicion = puntoRecarga->getPosicion();
    float latCentro = posicion.getLat();
    float lonCentro = posicion.getLon();

    float radio = 10.0;

    std::cout << "Buscando coches cercanos al punto de recarga con ID " << idPuntoRecarga << " en un radio de " << radio
              << "km" << std::endl;

    buscarCochesCercanos(reanelcar, latCentro, lonCentro, radio);
}

/**
 * @brief Determina el punto de recarga con más coches dentro de un radio de 15 km de Jaén
 *        y actualiza los puntos de los usuarios en base a la distancia de sus coches a dicho punto.
 *
 * @param reanelcar Objeto Reanelcar que contiene los datos de usuarios, coches y puntos de recarga.
 * @param latJaen Latitud de Jaén.
 * @param lonJaen Longitud de Jaén.
 */
void PuntoRecargaMasCoches(Reanelcar &reanelcar, float latJaen, float lonJaen) {
    std::vector<PuntoRecarga> &puntosRecarga = reanelcar.getSitios();
    MallaRegular<Coche *> &mallaRegular = reanelcar.getMallaRegular();

    if (puntosRecarga.empty()) {
        std::cerr << "Error: No hay puntos de recarga disponibles. " << std::endl;
        return;
    }

    PuntoRecarga *puntoConMasCoche = nullptr;
    size_t maxCoches = 0;

    for (PuntoRecarga &puntoRecarga: puntosRecarga) {
        UTM posicionPunto = puntoRecarga.getPosicion();
        float latPunto = posicionPunto.getLat();
        float lonPunto = posicionPunto.getLon();

        float distancia = mallaRegular.distanciaHaversine(latJaen, lonJaen, latPunto, lonPunto);

        if (distancia <= 15.0) {
            size_t cochesEnPunto = puntoRecarga.getCoches().size();

            if (cochesEnPunto > maxCoches) {
                maxCoches = cochesEnPunto;
                puntoConMasCoche = &puntoRecarga;
            }
        }
    }

    if (!puntoConMasCoche) {
        std::cerr << "No se encontro ningun punto de recarga con coches en un radio de 15 kilometros de Jaen. "
                  << std::endl;
        return;
    }

    std::cout << "El punto de recarga con mas coches tiene de ID: " << puntoConMasCoche->getId() << " y tiene "
              << maxCoches << " coches en un radio de 15km de Jaen. " << std::endl;

    /// PARTE 2:

    UTM posicionConMasCoches = puntoConMasCoche->getPosicion();
    float latPuntoConMasCoches = posicionConMasCoches.getLat();
    float lonPuntoConMasCoches = posicionConMasCoches.getLon();

    std::vector<Coche *> cochesEnRango = mallaRegular.buscarRadio(latPuntoConMasCoches, lonPuntoConMasCoches, 25.0);

    std::list<Usuario> &usuarios = reanelcar.getUsuarios();
    for (std::list<Usuario>::iterator iterator = usuarios.begin(); iterator != usuarios.end();) {
        Usuario &usuario = *iterator;

        Coche *coche = usuario.getCochealquilado();
        if (!coche || !coche->getPuntoRecarga()) {
            ++iterator;
            continue;
        }

        auto itCoche = std::find(cochesEnRango.begin(), cochesEnRango.end(), coche);
        if (itCoche != cochesEnRango.end()) {
            UTM posicionCoche = coche->getPuntoRecarga()->getPosicion();
            float distancia = mallaRegular.distanciaHaversine(latPuntoConMasCoches, lonPuntoConMasCoches,
                                                              posicionCoche.getLat(), posicionCoche.getLon());
            int puntosPerdidos = static_cast<int>(distancia * 2);
            usuario.decrementarPuntos(puntosPerdidos);

            ///NOTA: Ya se quitaron puntos en el ejercicio de aparcar los coches en la posición que indica
            /// el vector de posiciones sacado del ejercicio 3

            std::cout << "El usuario: " << usuario.getNombre() << "perdio: " << puntosPerdidos
                      << " puntos por aparcar a " << distancia << " km del punto con mas coches. "
                      << " Puntos restantes: " << usuario.getPuntos() << std::endl;

            if (distancia > 20.0) {
                std::cout << "El usuario " << usuario.getNombre()
                          << " sera eliminado porque aparco a mas de 20 kilometros. " << std::endl;
                coche->setPuntoRecarga(nullptr);
                iterator = usuarios.erase(iterator);
                continue;
            }
        }
        iterator++;
    }
}

/**
 * @brief Comprueba la densidad de coches en una posición específica y crea un nuevo punto de recarga si es necesario.
 *
 * Esta función verifica si el número de coches en una posición objetivo supera el promedio de coches por celda en la malla.
 * Si es así, se crea un nuevo punto de recarga en esa ubicación y se añade al vector de puntos de recarga.
 *
 * @param reanelcar Objeto Reanelcar que contiene la malla de coches y el vector de puntos de recarga.
 *
 * - Utiliza la posición objetivo especificada por las coordenadas latitud y longitud:
 *   - Latitud: 37.79143
 *   - Longitud: -3.77716
 * - Si el número de coches en la posición es mayor al promedio de coches por celda, se crea un nuevo punto de recarga con:
 *   - Un ID único basado en el tamaño actual del vector de puntos de recarga.
 *   - Capacidad máxima de 100 coches.
 */
void ComprobarYCrearPuntoRecarga(Reanelcar &reanelcar) {
    float latObjetivo = 37.79143;
    float lonObjetivo = -3.77716;

    MallaRegular<Coche *> &mallaRegular = reanelcar.getMallaRegular();
    std::vector<PuntoRecarga> &puntosRecarga = reanelcar.getSitios();

    std::vector<Coche *> cochesEnPosicion = mallaRegular.buscarRadio(latObjetivo, lonObjetivo, 0.01);
    size_t numCochesEnPosicion = cochesEnPosicion.size();

    float promedioCelda = mallaRegular.promedioElementosPorCelda();

    std::cout << " Numero de coches en la posicion: " << latObjetivo << ", " << lonObjetivo << "): "
              << numCochesEnPosicion << std::endl;
    std::cout << " Promedio de elementos por celda: " << promedioCelda << std::endl;

    if (numCochesEnPosicion > promedioCelda) {
        std::cout << "Numero de coches en la posicion mayor al promedio. Creando un nuevo punto de recarga. "
                  << std::endl;

        UTM posicion(latObjetivo, lonObjetivo);

        unsigned int nuevoID = puntosRecarga.size() + 1;
        unsigned int capacidadMaxima = 100;
        PuntoRecarga nuevoPunto(nuevoID, posicion, capacidadMaxima);
        puntosRecarga.push_back(nuevoPunto);

        std::cout << "Nuevo punto de recarga creado en (" << latObjetivo << ", " << lonObjetivo << ") "
                  << " y aniadido al vector de puntos de recarga. " << std::endl;
    } else {
        std::cout << " Numero de coches en la posicion no supera el promedio. No se crea un nuevo punto de recarga. "
                  << std::endl;
    }
}

int main() {

    /**
     * Primera prueba:
     */

    std::cout << " PRIMERA PRUEBA " << std::endl;
    Reanelcar reanelcar;
    std::cout << "Cargando usuarios en Reanelcar: " << std::endl;
    cargarUsuarios("../usuarios1.csv", reanelcar);
    std::cout << "Cargando coches en Reanelcar: " << std::endl;
    cargarCoches("../coches_v2.csv", reanelcar);
    std::cout << "Cargando puntos de recarga en reanelcar: " << std::endl << std::endl;
    cargarPuntosRecarga("../puntos_recarga.csv", reanelcar);

    reanelcar.configurarTablaHash(0.65, ThashUsuario::DOBLE);

    std::cout << std::endl;

    /**
     * Segunda prueba:
     */

    /// Malla Regular creada.

    /**
     * Tercera prueba:
     */

    std::cout << " Tercera PRUEBA " << std::endl;
    auto [usuariosPosiciones, latminima, latmaxima, lonminima, lonmaxima] = cargarDestino(
            "../destino.csv",
            reanelcar);
    std::cout << std::endl;

    /**
     * Cuarta prueba:
     */

    std::cout << " CUARTA PRUEBA " << std::endl;
    distribuirCochesPorBateria(reanelcar);
    contarCapacidadTotal(reanelcar.getSitios());

    /**
     * Quinta prueba:
     */

    std::cout << " QUINTA PRUEBA " << std::endl;
    std::string letra1 = "A";
    size_t ultimoindex = 0;
    asignarCochesYCrearTrayectosParaUsuarios(letra1, reanelcar, ultimoindex);

    /**
     * Sexta prueba:
     */

    std::cout << " SEXTA PRUEBA " << std::endl;
    std::string letra2 = "B";
    asignarCochesYCrearTrayectosParaUsuarios(letra2, reanelcar, ultimoindex);

    /**
     * Séptima prueba:
     */

    std::cout << " SEPTIMA PRUEBA " << std::endl;
    int nDivisiones = 10;

    reanelcar.getMallaRegular().resetMalla();
    /// Está puesto en +-0.3 para evitar que se salga del rango en los últimos ejercicios, aunque desconfigura
    /// ligeramente la malla
    reanelcar.getMallaRegular().setLimites(latminima - 0.3, lonminima - 0.3, latmaxima + 0.3, lonmaxima + 0.3,
                                           nDivisiones);
    aparcarCochesYMostrarDatos(letra2, reanelcar);

    /**
     * Octava prueba:
     */

    std::cout << " OCTAVA PRUEBA " << std::endl;
    std::cout << std::endl;
    /// NOTA: Los coches se aparcan en un punto de recarga creado si la posicion del archivo destino.csv no coincide
    /// con una posición de un punto de recarga del archivo puntos_recarga.csv
    aparcarCochesPorVectorDePosicionesYMostrar(usuariosPosiciones, reanelcar, letra1);

    /**
     * Novena prueba:
     */

    std::cout << " NOVENA PRUEBA " << std::endl;
    const float lonJaen = -3.7902800;
    const float latJaen = 37.7692200;
    const float radio = 10.0f;

    std::cout << std::endl;
    buscarCochesCercanos(reanelcar, latJaen, lonJaen, radio);

    /**
     * Décima prueba:
     */

    std::cout << " DECIMA PRUEBA " << std::endl;
    std::cout << std::endl;
    mostrarCochesMasCercanoAPunto(reanelcar, 43);

    /**
     * Undécima prueba:
     */

    std::cout << " UNDECIMA PRUEBA " << std::endl;
    std::cout << std::endl;

    /// NOTA: Se sale del radio de la malla por la función de buscar radio, y en el caso de reconfigurar
    /// la malla se distribuyen las celdas mal. Hace solo la primera parte del ejercicio bien

    PuntoRecargaMasCoches(reanelcar, latJaen, lonJaen);

    /**
     * Ejercicio extra:
     */

    std::cout << " EJERCICIO EXTRA " << std::endl;
    ComprobarYCrearPuntoRecarga(reanelcar);
    ///NOTA: Ocurre lo mismo del radio de la malla que en el ejercicio anterior, por lo del rango

    return 0;
}