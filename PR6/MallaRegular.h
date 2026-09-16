/**
 * @author David Fernández Espejo, dfe00004@red.ujaen.es
 * @author David Lorente Wagner, dlw00001@red.ujaen.es
 * @file MallaRegular.h
 * @brief Declaración de la clase MallaRegular
 */

#ifndef PR6_MALLAREGULAR_H
#define PR6_MALLAREGULAR_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include "Casilla.h"

/**
 * @class MallaRegular
 * @brief Plantilla de clase que organiza datos en una estructura de malla regular.
 *
 * La malla regular divide un área bidimensional en celdas rectangulares. Cada celda puede contener una colección de objetos.
 *
 * @tparam T Tipo de objeto que se almacenará en las celdas de la malla.
 */
template<typename T>
class MallaRegular {
private:
    float xMin; ///< Coordenada mínima en el eje X.
    float yMin; ///< Coordenada mínima en el eje Y.
    float xMax; ///< Coordenada máxima en el eje X.
    float yMax; ///< Coordenada máxima en el eje Y.
    float tamaCasillaX; ///< Ancho de las celdas de la malla.
    float tamaCasillaY; ///< Altura de las celdas de la malla.

    std::vector<std::vector<Casilla<T>>> mr; ///< Matriz de celdas que forman la malla.
    unsigned totalCoches = 0; ///< Contador total de elementos insertados en la malla.

    /**
     * @brief Obtiene la casilla que contiene las coordenadas dadas.
     *
     * @param x Coordenada X.
     * @param y Coordenada Y.
     * @return Puntero a la casilla que contiene las coordenadas.
     * @throw std::out_of_range Si las coordenadas están fuera de los límites de la malla.
     */
    Casilla<T> *obtenerCasilla(float x, float y);

public:

    /**
     * @brief Constructor por defecto.
     */
    MallaRegular() = default;

    /**
     * @brief Constructor parametrizado.
     *
     * @param aXMin Coordenada mínima en X.
     * @param aYMin Coordenada mínima en Y.
     * @param aXMax Coordenada máxima en X.
     * @param aYMax Coordenada máxima en Y.
     * @param aNDiv Número de divisiones en cada eje.
     */
    MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int aNDiv);

    /**
     * @brief Inserta un objeto en una casilla correspondiente a las coordenadas.
     *
     * @param x Coordenada X del objeto.
     * @param y Coordenada Y del objeto.
     * @param dato Objeto a insertar.
     */
    void insertar(float x, float y, T &dato);

    /**
     * @brief Busca un objeto en una casilla específica.
     *
     * @param x Coordenada X del objeto.
     * @param y Coordenada Y del objeto.
     * @param dato Objeto a buscar.
     * @return El objeto encontrado.
     */
    T buscar(float x, float y, const T &dato);

    /**
     * @brief Borra un objeto de una casilla específica.
     *
     * @param x Coordenada X del objeto.
     * @param y Coordenada Y del objeto.
     * @param dato Objeto a borrar.
     * @return `true` si el objeto fue eliminado, `false` en caso contrario.
     */
    bool borrar(float x, float y, const T &dato);

    /**
     * @brief Busca objetos dentro de un radio alrededor de un punto.
     *
     * @param xcentro Coordenada X del centro del radio.
     * @param ycentro Coordenada Y del centro del radio.
     * @param radio Distancia máxima desde el centro.
     * @return Vector con los objetos encontrados en el radio.
     */
    std::vector<T> buscarRadio(float xcentro, float ycentro, float radio);

    /**
     * @brief Obtiene el máximo número de elementos contenidos en una sola celda.
     * @return Número máximo de elementos por celda.
     */
    unsigned maxElementosPorCelda();

    /**
     * @brief Calcula el promedio de elementos por celda.
     * @return Promedio de elementos por celda.
     */
    float promedioElementosPorCelda();

    /**
     * @brief Calcula la distancia Haversine entre dos puntos geográficos.
     *
     * @param lat1 Latitud del primer punto.
     * @param lon1 Longitud del primer punto.
     * @param lat2 Latitud del segundo punto.
     * @param lon2 Longitud del segundo punto.
     * @return Distancia en kilómetros entre los dos puntos.
     */
    float distanciaHaversine(float lat1, float lon1, float lat2, float lon2);

    /**
     * @brief Obtiene el ancho de las celdas de la malla.
     * @return Tamaño de las celdas en el eje X.
     */
    float getTamaCasillaX();

    /**
     * @brief Obtiene la altura de las celdas de la malla.
     * @return Tamaño de las celdas en el eje Y.
     */
    float getTamaCasillaY();

    /**
     * @brief Configura los límites de la malla y recalcula las celdas.
     *
     * @param aXMin Coordenada mínima en X.
     * @param aYMin Coordenada mínima en Y.
     * @param aXMax Coordenada máxima en X.
     * @param aYMax Coordenada máxima en Y.
     * @param aNDiv Número de divisiones en cada eje.
     */
    void setLimites(float aXMin, float aYMin, float aXMax, float aYMax, int aNDiv);

    /**
     * @brief Reinicia la malla eliminando todos los datos almacenados.
     */
    void resetMalla();

    /**
    * @brief Obtiene un puntero a la casilla más poblada.
    * @return Puntero a la casilla más poblada.
    */
    Casilla<T> *casillaMasPoblada();

    /**
     * @brief Obtiene el número total de elementos almacenados en la malla.
     * @return Número total de elementos.
     */
    unsigned int getTotalCoches();
};

template<typename T>
MallaRegular<T>::MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int aNDiv):
        xMin(aXMin), yMin(aYMin), xMax(aXMax), yMax(aYMax) {
    try {
        tamaCasillaX = (xMax - xMin) / aNDiv;
        tamaCasillaY = (yMax - yMin) / aNDiv;

        /**
         * std::cout << "Tamanio de casillas: tamaCasillaX = " << tamaCasillaX << ", tamaCasillaY = " << tamaCasillaY
         * << "\n";
         */

        if (tamaCasillaX <= 0 || tamaCasillaY <= 0) {
            std::cout << "ERROR: Tamanio de casillas no valido. tamaCasillaX = " << tamaCasillaX << ", tamaCasillaY = "
                      << tamaCasillaY << std::endl;
            throw std::logic_error("Tamanio de casilla inválido en constructor de MallaRegular.");
        }

        mr = std::vector<std::vector<Casilla<T>>>(aNDiv, std::vector<Casilla<T>>(aNDiv));

        if (mr.empty() || mr.size() != aNDiv || mr[0].size() != aNDiv) {
            std::cout << "ERROR: Inicialización del vector 'mr' fallida. Tamaño esperado: " << aNDiv << "x" << aNDiv
                      << "\n";
            throw std::logic_error("Error en la inicialización del vector 'mr' en el constructor de MallaRegular.");
        }
    } catch (const std::exception &e) {
        std::cerr << "Excepcion: " << e.what() << std::endl;
        throw;
    }
}

template<typename T>
Casilla<T> *MallaRegular<T>::obtenerCasilla(float x, float y) {
    static int contador = 0;
    try {
        contador++;
        if (x < xMin || x > xMax || y < yMin || y > yMax) {
            std::cerr << "ERROR: Coordenadas fuera de los limites de la malla. Coordenadas: (" << x << ", " << y
                      << ")\n";
            std::cerr << "Limites: xMin = " << xMin << ", xMax = " << xMax
                      << ", yMin = " << yMin << ", yMax = " << yMax << "\n";
            throw std::out_of_range("Coordenadas fuera de los limites de la malla.");
        }

        if (tamaCasillaX <= 0 || tamaCasillaY <= 0) {
            throw std::logic_error("Tamaño de casillas inválido.");
        }

        int i = (x >= xMax) ? mr.size() - 1 : (x - xMin) / tamaCasillaX;
        int j = (y >= yMax) ? mr[0].size() - 1 : (y - yMin) / tamaCasillaY;

        if (i < 0 || i >= mr.size() || j < 0 || j >= mr[0].size()) {
            throw std::out_of_range("Indices fuera de rango.");
        }

        return &mr[i][j];
    } catch (const std::exception &e) {
        std::cerr << "Excepcion en intento #" << contador << ": " << e.what() << std::endl;
        throw;
    }
}


template<typename T>
void MallaRegular<T>::insertar(float x, float y, T &dato) {
    Casilla<T> *c = obtenerCasilla(x, y);
    c->inserta(dato);
    ++totalCoches;
}

template<typename T>
bool MallaRegular<T>::borrar(float x, float y, const T &dato) {
    if (x < xMin || x >= xMax || y < yMin || y > yMax) {
        throw std::invalid_argument("Coordenadas fuera de los límites de la malla.");
    }

    Casilla<T> *c = obtenerCasilla(x, y);
    if (c->borrar(dato)) {
        --totalCoches;
        return true;
    }
    return false;
}

template<typename T>
T MallaRegular<T>::buscar(float x, float y, const T &dato) {
    Casilla<T> *c = obtenerCasilla(x, y);
    return c->buscar(dato);
}

template<typename T>
float MallaRegular<T>::distanciaHaversine(float lat1, float lon1, float lat2, float lon2) {
    const float R = 6378.0f;
    float incrLat = (lat2 - lat1) * M_PI / 180.0f;
    float incrLon = (lon2 - lon1) * M_PI / 180.0f;
    float a = std::sin(incrLat / 2) * std::sin(incrLat / 2) +
              std::cos(lat1 * M_PI / 180.0f) * std::cos(lat2 * M_PI / 180.0f) * std::sin(incrLon / 2) *
              std::sin(incrLon / 2);
    float c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return R * c;
}

template<typename T>
std::vector<T> MallaRegular<T>::buscarRadio(float xcentro, float ycentro, float radio) {
    std::vector<T> encontrados;

    float deltaLat = radio / 111.32;
    float deltaLon = radio / (111.32 * std::cos(xcentro * M_PI / 180.0));

    float xMinRadio = xcentro - deltaLat;
    float yMinRadio = ycentro - deltaLon;
    float xMaxRadio = xcentro + deltaLat;
    float yMaxRadio = ycentro + deltaLon;

    for (float x = xMinRadio; x <= xMaxRadio; x += tamaCasillaX) {
        for (float y = yMinRadio; y <= yMaxRadio; y += tamaCasillaY) {
            try {
                Casilla<T> *c = obtenerCasilla(x, y);
                if (c) {
                    for (const T &punto: c->puntos) {
                        if (punto && punto->getPuntoRecarga()) {
                            float distancia = distanciaHaversine(xcentro, ycentro,
                                                                 punto->getPuntoRecarga()->getPosicion().getLat(),
                                                                 punto->getPuntoRecarga()->getPosicion().getLon());
                            if (distancia <= radio) {
                                encontrados.push_back(punto);
                            }
                        }
                    }
                }
            } catch (const std::out_of_range &e) {
                std::cerr << "Coordenada fuera del rango: " << e.what() << std::endl;
            } catch (const std::exception &e) {
                std::cerr << "Error inesperado: " << e.what() << std::endl;
                throw;
            }
        }
    }

    return encontrados;
}

template<typename T>
unsigned int MallaRegular<T>::maxElementosPorCelda() {
    unsigned maximo = 0;
    for (const auto &fila: mr) {
        for (const auto &casilla: fila) {
            maximo = std::max(maximo, static_cast<unsigned>(casilla.puntos.size()));
        }
    }
    return maximo;
}

template<typename T>
Casilla<T> *MallaRegular<T>::casillaMasPoblada() {
    Casilla<T> *casillaMasLlena = nullptr;
    unsigned int maxElementos = 0;

    for (auto &fila: mr) {
        for (auto &casilla: fila) {
            unsigned int numElementos = casilla.puntos.size();
            if (numElementos > maxElementos) {
                maxElementos = numElementos;
                casillaMasLlena = &casilla;
            }
        }
    }

    return casillaMasLlena;
}

template<typename T>
float MallaRegular<T>::promedioElementosPorCelda() {
    unsigned totalElementos = 0;
    unsigned totalCeldas = 0;
    for (const auto &fila: mr) {
        for (const auto &casilla: fila) {
            totalElementos += casilla.puntos.size();
            ++totalCeldas;
        }
    }
    return totalCeldas > 0 ? static_cast<float>(totalElementos) / totalCeldas : 0.0f;
}

template<typename T>
float MallaRegular<T>::getTamaCasillaX() {
    return tamaCasillaX;
}

template<typename T>
float MallaRegular<T>::getTamaCasillaY() {
    return tamaCasillaY;
}

template<typename T>

void MallaRegular<T>::setLimites(float aXMin, float aYMin, float aXMax, float aYMax, int aNDiv) {
    xMin = aXMin;
    yMin = aYMin;
    xMax = aXMax;
    yMax = aYMax;

    tamaCasillaX = (xMax - xMin) / aNDiv;
    tamaCasillaY = (yMax - yMin) / aNDiv;

    mr = std::vector<std::vector<Casilla<T>>>(aNDiv, std::vector<Casilla<T>>(aNDiv));
}

template<typename T>
void MallaRegular<T>::resetMalla() {
    mr.clear();
}

template<typename T>
unsigned int MallaRegular<T>::getTotalCoches() {
    return totalCoches;
}

#endif //PR6_MALLAREGULAR_H