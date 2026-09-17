/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file main.cpp
 * @brief Primer archivo de prueba
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
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

void pruebaRendimiento(Reanelcar &reanelcar) {
    std::vector<std::string> nifs = reanelcar.buscarUsuariosConW('W');

    auto comienzo = std::chrono::high_resolution_clock::now();
    for (std::string &nif: nifs) {
        Usuario *usuario = reanelcar.buscarUsrNifThash(nif);
    }

    auto final = std::chrono::high_resolution_clock::now();
    auto hashduracion = std::chrono::duration_cast<std::chrono::microseconds>(final - comienzo);
    std::cout << "Tiempo de duracion en la tabla Hash con configuracion DOBLE: " << hashduracion.count()
              << " milisegundos. " << std::endl;

    comienzo = std::chrono::high_resolution_clock::now();
    std::list<Usuario> usuarios = reanelcar.getUsuarios();

    for (Usuario &usuarioptr: usuarios) {
        if (usuarioptr.getNombre()[0] == 'W') {
            std::string nif = usuarioptr.getNif();
        }
    }

    final = std::chrono::high_resolution_clock::now();
    auto duracionLista = std::chrono::duration_cast<std::chrono::microseconds>(final - comienzo);
    std::cout << "Tiempo de busqueda en la lista de usuarios: " << duracionLista.count() << " milisegundos. "
              << std::endl;

    if (hashduracion < duracionLista) {
        std::cout << "La busqueda en la tabla hash fue mas rapida. " << std::endl;
    } else {
        std::cout << "La busqueda en la lista de usuarios fue mas rapida. " << std::endl;
    }
}

int main() {

    Reanelcar reanelcar;

    std::cout << "Cargando datos de usuarios..." << std::endl;
    cargarUsuarios("../usuarios1.csv", reanelcar);
    std::cout << "Cargando datos de coches..." << std::endl;
    cargarCoches("../coches_v2.csv", reanelcar);
    std::cout << "Cargando datos de puntos de recarga..." << std::endl;
    std::cout << std::endl;
    cargarPuntosRecarga("../puntos_recarga.csv", reanelcar);

    float lambdas[] = {0.65, 0.68};
    for (int i = 0; i < 2; ++i) {
        float lambda = lambdas[i];

        for (ThashUsuario::TipoHash tipo: {ThashUsuario::VARIANTE, ThashUsuario::CUADRATICA, ThashUsuario::DOBLE}) {
            std::cout << "Configurando tabla hash con lambda: " << lambda << " y dispersion tipo: ";
            switch (tipo) {
                case ThashUsuario::VARIANTE:
                    std::cout << "VARIANTE" << std::endl;
                    break;
                case ThashUsuario::CUADRATICA:
                    std::cout << "CUADRATICA" << std::endl;
                    break;
                case ThashUsuario::DOBLE:
                    std::cout << "DOBLE" << std::endl;
                    break;
                default:
                    std::cout << "DESCONOCIDO" << std::endl;
            }

            reanelcar.configurarTablaHash(lambda, tipo);
            std::cout << std::endl;
        }
    }

    pruebaRendimiento(reanelcar);

    return 0;
}
