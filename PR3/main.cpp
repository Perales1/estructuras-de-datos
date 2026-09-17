/**
 * @author David Fernández Espejo, dfe00004@red.ujaen.es
 * @author David Lorente Wagner, dlw00001@red.ujaen.es
 * @file main.cpp
 * @brief Programa principal para gestionar la aplicación Reanelcar.
 * @note Al ejecutar el main, la prueba 2 provoca un error, por lo que para ejecutar el resto del programa
 * hay que comentar la prueba 3 y el resto se ejecutará sin problema
 */
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
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
 * @brief Carga los datos de usuarios desde un archivo CSV e inserta cada usuario en el sistema.
 * @param rutaArchivo Ruta del archivo CSV de usuarios.
 * @param r Referencia al objeto Reanelcar donde se insertarán los usuarios.
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
 * @brief Carga los datos de coches desde un archivo CSV e inserta cada coche en el sistema.
 * @param rutaArchivo Ruta del archivo CSV de coches.
 * @param r Referencia al objeto Reanelcar donde se insertarán los coches.
 */
void cargarCoches(const std::string &rutaArchivo, Reanelcar &r) {
    std::ifstream archivo;
    if (!abrirArchivo(archivo, rutaArchivo)) return;

    std::string fila;
    while (getline(archivo, fila)) {
        if (fila.empty()) continue;

        std::stringstream columnas(fila);
        std::string id_matricula, marca, modelo;

        getline(columnas, id_matricula, ',');
        getline(columnas, marca, ',');
        getline(columnas, modelo, ',');

        Coche coche(id_matricula, marca, modelo);
        r.insertacoche(coche);
    }

    archivo.close();
}

int main() {

    /*
     * Primera prueba:
     */

    Reanelcar reanelcar;
    cargarUsuarios("../usuarios1.csv", reanelcar);
    cargarCoches("../coches.csv", reanelcar);

    /*
    * Segunda prueba:
    */

    std::cout << "La altura del arbol de coches es de: " << reanelcar.getCoches().alturaAux() << std::endl;

    /*
     * Tercera prueba:
     */

    VDinamico<Coche *> v = reanelcar.getCoches().recorreinorden();

    /** static const int TVEC = 1000;
     unsigned int tamlogv = v.tamlog();

     unsigned int limite = (TVEC < tamlogv) ? TVEC : tamlogv;

     for (unsigned int i = 0; i < limite; ++i) {
         if (v[i]) {
             std::cout << v[i]->getIdMatricula() << " ";
         }
     }
 */

    /*
     * Cuarta prueba:
     */

    PuntoRecarga puntoRecarga(1, Coordenadas(0, 0), 50);

    std::vector<std::string> lc = {
            "6028 ZXL", "6795 MLS", "0209 GZT", "2171 ZDC", "4649 HJH", "8953 YRT",
            "6698 XKM", "5830 MNZ", "7690 DKN", "6557 BGW", "4680 BBC", "1045 GYK",
            "9400 HRX", "9856 FLG", "3704 RWK", "8514 HLL", "7048 YYY", "2910 ZXN",
            "7358 DZN", "2966 LTL", "4268 MGX", "4155 DFX", "7891 XXB", "2140 SNB",
            "9838 THH", "3168 LNC", "9150 HNB", "1691 FHS"
    };

    for (unsigned int i = 0; i < lc.size(); ++i) {
        std::string matricula = lc[i];
        Coche *coche = reanelcar.buscarCochePorMatricula(matricula);

        if (coche != nullptr) {
            if (!puntoRecarga.addCoche(*coche)) {
                std::cerr << "Error: No se pudo añadir el coche con matrícula " << matricula
                          << " al punto de recarga. " << std::endl;
            }
        } else {
            std::cerr << "Coche con matrícula " << matricula << " no encontrado en el AVL.\n";
        }
    }

    /*
     * Quinta prueba:
     */

    reanelcar.setPuntoRecarga(puntoRecarga);

    Usuario *usuario = reanelcar.buscarUsuarioPorNif("91477235Q");

    if (usuario != nullptr) {
        Coche *cochealquilado = reanelcar.alquila();

        if (cochealquilado != nullptr) {
            std::cout << " Coche con matricula: " << cochealquilado->getIdMatricula() << " y bateria: "
                      << cochealquilado->getBateria()
                      << " ha sido alquilado al usuario con NIF: " << usuario->getNif() << std::endl;
        } else {
            std::cerr << " No hay coches disponibles. " << std::endl;
        }
    } else {
        std::cerr << " Usuario con NIF 91477235Q no encontrado. " << std::endl;
    }

    /*
     * Sexta prueba:
     */

    VDinamico<Coche *> preorden = reanelcar.getCoches().recorrepreorden();

    std::cout << "Coches en preorden:" << std::endl;

    unsigned int totalCoches = preorden.tamlog();

    std::cout << totalCoches << std::endl;

    std::cout << " Coches en preorden: " << std::endl;
    for (unsigned int i = 0; i < preorden.tamlog(); ++i) {
        if (preorden[i] != nullptr) {
            std::cout << preorden[i]->getIdMatricula() << " ";
        }
    }

    std::cout << std::endl;
    return 0;
}