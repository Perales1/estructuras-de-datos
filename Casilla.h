/**
 * @author David Fernández Espejo, dfe00004@red.ujaen.es
 * @author David Lorente Wagner, dlw00001@red.ujaen.es
 * @file Casilla.h
 * @brief Declaración de la clase Casilla
 */

#ifndef PR6_CASILLA_H
#define PR6_CASILLA_H

#include <list>
#include <stdexcept>

/**
 * @brief Declaración adelantada de la plantilla de clase MallaRegular
 * @tparam T parametro de la plantilla
 */
template<typename T>
class MallaRegular;

/**
 * @class Casilla
 * @brief Representa una celda en la malla regular, que almacena una lista de objetos.
 *
 * Esta clase actúa como contenedor para los objetos de tipo T, organizados en una lista.
 *
 * @tparam T Tipo de los objetos que se almacenan en la casilla.
 */
template<typename T>
class Casilla {

private:
    std::list<T> puntos; ///< Lista de objetos almacenados en la casilla.

public:

    /**
     * @brief clase amiga con la plantilla de clase de MallaRegular
     */
    friend class MallaRegular<T>;

    /**
     * @brief Constructor por defecto.
     *
     * Inicializa la lista de puntos vacía.
     */
    Casilla();

    /**
     * @brief Inserta un objeto en la casilla.
     *
     * @param dato Referencia al objeto a insertar.
     */
    void inserta(T &dato);

    /**
     * @brief Busca un objeto en la casilla.
     *
     * @param dato Referencia al objeto que se desea buscar.
     * @return Una copia del objeto encontrado.
     * @throw std::runtime_error Si el objeto no está en la casilla.
     */
    T buscar(const T &dato);

    /**
     * @brief Borra un objeto de la casilla.
     *
     * @param dato Referencia al objeto que se desea borrar.
     * @return `true` si el objeto fue eliminado, `false` si no fue encontrado.
     */
    bool borrar(const T &dato);

    /**
    * @brief Obtiene la lista de objetos almacenados en la casilla.
    *
    * @return Referencia a la lista de objetos almacenados.
    */
    std::list<T> &getPuntos();

    /**
     * @brief Establece una nueva lista de objetos para la casilla.
     *
     * @param puntos Referencia a la lista de objetos que se desea establecer.
     */
    void setPuntos(std::list<T> &puntos);

};


template<typename T>
Casilla<T>::Casilla():puntos(0) {}

template<typename T>
void Casilla<T>::inserta(T &dato) {
    puntos.push_back(dato);
}

template<typename T>
T Casilla<T>::buscar(const T &dato) {
    for (const std::list<T> &item: puntos) {
        if (item == dato) {
            return item;
        }
    }
    throw std::runtime_error(" Dato no encontrado en la casilla. ");
}

template<typename T>
bool Casilla<T>::borrar(const T &dato) {
    typename std::list<T>::iterator iterator;
    iterator = puntos.begin();
    for (; iterator != puntos.end(); ++iterator) {
        if (*iterator == dato) {
            puntos.erase(iterator);
            return true;
        }
    }
    return false;
}

template<typename T>
std::list<T> &Casilla<T>::getPuntos() {
    return puntos;
}

template<typename T>
void Casilla<T>::setPuntos(std::list<T> &puntos) {
    Casilla::puntos = puntos;
}

#endif //PR6_CASILLA_H
