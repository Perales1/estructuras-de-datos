/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file main.cpp
 * @brief Programa de prueba para la clase Reanelcar
 *
 * Este programa carga datos de coches y usuarios desde archivos CSV,
 * realiza búsquedas secuenciales y binarias de coches por modelo,
 * y gestiona el alquiler de coches a los usuarios.
 */

#include <fstream>
#include <sstream>
#include <chrono>
#include "Reanelcar.h"

/**
 * @brief Carga coches desde un archivo CSV a la clase Reanelcar.
 *
 * @param rental Objeto de la clase Reanelcar donde se almacenan los coches.
 */
void cargarCoches(Reanelcar &rental) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    std::string id_matricula = "";
    std::string marca = "";
    std::string modelo = "";

    is.open("../coches.csv");

    if (is.good()) {
        auto t_ini = std::chrono::high_resolution_clock::now();

        while (getline(is, fila)) {
            if (fila != "") {
                columnas.str(fila);

                getline(columnas, id_matricula, ',');
                getline(columnas, marca, ',');
                getline(columnas, modelo, ',');

                rental.coches.insertar(Coche(id_matricula, marca, modelo));

                fila = "";
                columnas.clear();
            }
        }

        is.close();

        auto t_fin = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duracion = t_fin - t_ini;
        std::cout << "Coches cargados en " << duracion.count() << " segundos." << std::endl;
    } else {
        std::cerr << "Error al abrir el archivo coches.csv" << std::endl;
    }
}

/**
 * @brief Carga usuarios desde un archivo CSV a la clase Reanelcar.
 *
 * @param rental Objeto de la clase Reanelcar donde se almacenan los usuarios.
 */
void cargarUsuarios(Reanelcar &rental) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    std::string nif = "";
    std::string clave = "";
    std::string nombre = "";
    std::string direccion = "";

    is.open("../usuarios1.csv");

    if (is.good()) {
        while (getline(is, fila)) {
            if (fila != "") {
                columnas.str(fila);

                getline(columnas, nif, ',');
                getline(columnas, clave, ',');
                getline(columnas, nombre, ',');
                getline(columnas, direccion, ',');

                rental.usuarios.insertaFin(Usuario(nif, clave, nombre, direccion));

                fila = "";
                columnas.clear();
            }
        }

        is.close();
    } else {
        std::cerr << "Error al abrir el archivo usuarios.csv" << std::endl;
    }
}

/**
 * @brief Función principal del programa.
 *
 * Carga coches y usuarios, realiza búsquedas de coches por modelo,
 * gestiona alquileres y realiza operaciones sobre los usuarios.
 *
 * @return int Código de estado de salida.
 */
int main() {
    Reanelcar reanelcar;

    cargarCoches(reanelcar);
    cargarUsuarios(reanelcar);

    auto inicioSecuencial = std::chrono::high_resolution_clock::now();
    VDinamico<Coche> *fordsSecuencial = reanelcar.buscarCochePorModelo("Fiesta");
    auto finSecuencial = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracionSecuencial = finSecuencial - inicioSecuencial;
    std::cout << "Tiempo de busqueda secuencial: " << duracionSecuencial.count() << " segundos." << std::endl;

    if (fordsSecuencial == nullptr || fordsSecuencial->tamlog() == 0) {
        std::cerr << "No se encontraron coches del modelo 'Fiesta' con la busqueda secuencial." << std::endl;
    } else {
        std::cout << "Numero de coches encontrados con la busqueda secuencial: " << fordsSecuencial->tamlog() << std::endl;
    }

    reanelcar.coches.ordenar();

    auto inicioBinaria = std::chrono::high_resolution_clock::now();
    Coche cocheBuscado("", "", "Fiesta");
    int indice = reanelcar.coches.busquedaBin(cocheBuscado);
    auto finBinaria = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracionBinaria = finBinaria - inicioBinaria;
    std::cout << "Tiempo de busqueda binaria: " << duracionBinaria.count() << " segundos." << std::endl;

    if (indice == -1) {
        std::cerr << "No se encontraron coches del modelo 'Fiesta' con la busqueda binaria." << std::endl;
    } else {
        int contador = 0;
        while (indice < reanelcar.coches.tamlog() && reanelcar.coches[indice].getModelo() == "Fiesta") {
            contador++;
            indice++;
        }
        std::cout << "Numero de coches encontrados con la busqueda binaria: " << contador << std::endl;
    }

    if (fordsSecuencial != nullptr && fordsSecuencial->tamlog() > 0) {
        ListaDEnlazada<Usuario> usuarios = reanelcar.buscarUsuarioPorNombre("W");

        int i = 0;
        Iterador<Usuario> iterador1 = usuarios.iterador();

        while (iterador1.haySiguiente() && i < fordsSecuencial->tamlog()) {
            Usuario &usuario = iterador1.dato();
            if (usuario.getCocheAlquilado() == nullptr) {
                Coche &coche = fordsSecuencial->operator[](i);
                reanelcar.alquilar(usuario.getNif(), coche.getIdMatricula());
                i++;
            }
            iterador1.siguiente();
        }
    }

    Iterador<Usuario> iterador2 = reanelcar.usuarios.iterador();
    ListaDEnlazada<Usuario> nuevos;
    while (iterador2.haySiguiente()) {
        Usuario &usuario = iterador2.dato();
        if (usuario.getNombre().substr(0, 2) != "Wa") {
            nuevos.insertaFin(usuario);
        }
        iterador2.siguiente();
    }
    reanelcar.usuarios = nuevos;

    int cont = 0;
    Iterador<Usuario> iterador3 = reanelcar.usuarios.iterador();
    while (iterador3.haySiguiente()) {
        Usuario &usuario = iterador3.dato();
        if (usuario.getNombre().substr(0, 1) == "W" && usuario.getCocheAlquilado() != nullptr) {
            ++cont;
        }
        iterador3.siguiente();
    }

    if (cont == 0) {
        std::cout << "No se encontraron usuarios con nombre que comience con 'W' y con un coche alquilado." << std::endl;
    } else {
        std::cout << "Numero de usuarios que comienzan con 'W' y tienen un coche alquilado: " << cont << std::endl;
    }

    delete fordsSecuencial;

    return 0;
}
