/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file VDinamico.h
 * @brief Declaración e implementación de la clase VDinamico.
 */
#ifndef LISTADENLAZADA3_VDINAMICO_H
#define LISTADENLAZADA3_VDINAMICO_H

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cmath>

/**
 * @brief Clase para un vector dinámico.
 *
 * Esta clase implementa un vector dinámico que permite
 * operaciones de inserción, borrado, búsqueda y ordenamiento.
 *
 * @tparam T Tipo de los elementos que contendrá el vector.
 */
template<class T>
class VDinamico {
    T *mem;                          ///< Puntero a la memoria que almacena los elementos.
    unsigned int tamfisico;          ///< Tamaño físico del vector (capacidad).
    unsigned int tamlogico;          ///< Tamaño lógico del vector (número de elementos).

public:
    /**
     * @brief Constructor por defecto.
     *
     * Crea un vector dinámico de tamaño físico 1 y tamaño lógico 0.
     */
    VDinamico();

    /**
     * @brief Constructor con tamaño lógico especificado.
     *
     * @param _tamlogico Tamaño lógico inicial del vector.
     */
    explicit VDinamico(unsigned int _tamlogico);

    /**
     * @brief Constructor de copia.
     *
     * @param other Vector que se va a copiar.
     */
    VDinamico(const VDinamico<T> &other);

    /**
     * @brief Constructor de copia parcial.
     *
     * @param other Vector del cual se copiarán elementos.
     * @param posicioninicial Posición inicial para la copia.
     * @param numelementos Número de elementos a copiar.
     * @throw std::out_of_range Si la posición inicial es inválida.
     */
    VDinamico(const VDinamico<T> &other, unsigned int posicioninicial, unsigned int numelementos);

    /**
     * @brief Operador de asignación.
     *
     * @param other Vector a asignar.
     * @return Referencia al objeto actual.
     */
    VDinamico<T> &operator=(const VDinamico<T> &other);

    /**
     * @brief Acceso a los elementos del vector.
     *
     * @param pos Índice del elemento a acceder.
     * @return Referencia al elemento en la posición especificada.
     * @throw std::out_of_range Si la posición está fuera de rango.
     */
    T &operator[](unsigned int pos);

    /**
     * @brief Búsqueda binaria de un elemento.
     *
     * @param dato Elemento a buscar.
     * @return Índice del elemento encontrado, o -1 si no se encuentra.
     */
    int busquedaBin(const T &dato);

    /**
     * @brief Obtiene el tamaño lógico del vector.
     *
     * @return Tamaño lógico del vector.
     */
    unsigned int tamlog() const;

    /**
     * @brief Operador de igualdad.
     *
     * @param other Vector a comparar.
     * @return True si los vectores son iguales, false en caso contrario.
     */
    bool operator==(const VDinamico<T> &other);

    /**
     * @brief Ordena el vector utilizando sort.
     */
    void ordenar();

    /**
     * @brief Ordena el vector utilizando el algoritmo Quicksort.
     *
     * @param izquierda Límite izquierdo del subvector.
     * @param derecha Límite derecho del subvector.
     */
    void quicksort(int izquierda, int derecha);

    /**
     * @brief Ordena el vector utilizando Quicksort.
     */
    void ordenar2();

    /**
     * @brief Destructor.
     *
     * Libera la memoria asignada.
     */
    virtual ~VDinamico();

    /**
     * @brief Inserta un elemento en el vector.
     *
     * @param dato Elemento a insertar.
     * @param pos Posición en la que se desea insertar (opcional).
     * @throw std::out_of_range Si la posición está fuera de rango.
     */
    void insertar(const T &dato, unsigned int pos = UINT_MAX);

    /**
     * @brief Borra un elemento en la posición especificada.
     *
     * @param pos Posición del elemento a borrar (opcional).
     * @return Elemento eliminado.
     * @throw std::out_of_range Si el vector está vacío o la posición está fuera de rango.
     */
    T borrar(unsigned int pos = UINT_MAX);
};

template<class T>
VDinamico<T>::VDinamico():tamfisico(1), tamlogico(0) {
    mem = new T[tamfisico];
}

template<class T>
VDinamico<T>::VDinamico(unsigned int _tamlogico):tamlogico(_tamlogico) {
    tamfisico = std::pow(2, std::ceil(std::log2(_tamlogico + 1)));
    mem = new T[tamfisico];
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &other): tamlogico(other.tamlogico), tamfisico(other.fisico) {
    mem = new T[tamfisico];
    for (unsigned int i = 0; i < tamlogico; ++i) {
        mem[i] = other.mem[i];
    }
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &other, unsigned int posicioninicial, unsigned int numelementos) {
    if (posicioninicial + numelementos > other.tamlogico) {
        throw std::out_of_range(" Posicion inicial invalida. ");
    }
    tamlogico = numelementos;
    tamfisico = std::pow(2, std::ceil(std::log2(numelementos + 1)));
    mem = new T[tamfisico];
    for (int i = 0; i < tamlogico; ++i) {
        mem[i] = other.mem[posicioninicial + i];
    }
}

template<class T>
VDinamico<T>::~VDinamico() {
    delete[] mem;
}

template<class T>
VDinamico<T> &VDinamico<T>::operator=(const VDinamico<T> &other) {
    if (this != other) {
        delete[] mem;
        tamlogico = other.tamlogico;
        tamfisico = other.tamfisico;
        mem = new T[tamfisico];
        for (unsigned int i = 0; i < tamlogico; i++) {
            mem[i] = other.mem[i];
        }
    }
    return *this;
}

template<class T>
T &VDinamico<T>::operator[](unsigned int pos) {
    if (pos >= tamlogico) {
        throw std::out_of_range("Posicion fuera de rango");
    }
    return mem[pos];
}

template<class T>
void VDinamico<T>::ordenar() {
    std::sort(mem, mem + tamlogico);
}

template<class T>
void VDinamico<T>::quicksort(int izquierda, int derecha) {
    if (izquierda < derecha) {
        T pivote = mem[derecha];
        int i = izquierda - 1;
        for (int j = izquierda; j < derecha; ++j) {
            if (mem[j] <= pivote) {
                ++i;
                std::swap(mem[i], mem[j]);
            }
        }
        std::swap(mem[i + 1], mem[derecha]);
        int pivoteIndice = i + 1;

        quicksort(izquierda, pivoteIndice - 1);
        quicksort(pivoteIndice + 1, derecha);
    }
}

template<class T>
void VDinamico<T>::ordenar2() {
    quicksort(0, tamlogico - 1);
}

template<class T>
unsigned int VDinamico<T>::tamlog() const {
    return tamlogico;
}

template<class T>
bool VDinamico<T>::operator==(const VDinamico<T> &other) {
    if (tamlogico != other.tamlogico) {
        return false;
    }
    for (unsigned int i = 0; i < tamlogico; i++) {
        if (mem[i] != other.mem[i]) {
            return false;
        }
    }
    return true;
}

template<class T>
int VDinamico<T>::busquedaBin(const T &dato) {
    int izquierda = 0;
    int derecha = tamlogico - 1;
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (mem[medio] == dato) {
            return medio;
        } else if (mem[medio] < dato) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    return -1;
}

template<class T>
void VDinamico<T>::insertar(const T &dato, unsigned int pos) {

    if (pos == UINT_MAX) {
        pos = tamlogico;
    }
    if (pos > tamlogico) {
        throw std::out_of_range(" Posicion fuera de rango. ");
    }

    if (tamlogico == tamfisico) {
        tamfisico *= 2;
        T *_mem = new T[tamfisico];
        std::copy(mem, mem + tamlogico, _mem);
        delete[] mem;
        mem = _mem;
    }

    for (unsigned int i = tamlogico; i > pos; --i) {
        mem[i] = mem[i - 1];
    }

    mem[pos] = dato;
    ++tamlogico;
}

template<class T>
T VDinamico<T>::borrar(unsigned int pos) {
    if (tamlogico == 0) {
        throw std::out_of_range(" El vector esta vacio. ");
    }

    if (pos == UINT_MAX) {
        pos = tamlogico - 1;
    }

    if (pos >= tamlogico) {
        throw std::out_of_range(" Posicion fuera de rango. ");
    }

    T eliminado = mem[pos];

    for (unsigned int i = pos; i < tamlogico - 1; ++i) {
        mem[i] = mem[i + 1];
    }

    --tamlogico;

    if (tamlogico < tamfisico / 3 && tamfisico > 1) {
        tamfisico /= 2;
        T *_mem = new T[tamfisico];
        std::copy(mem, mem + tamlogico, _mem);
        delete[] mem;
        mem = _mem;
    }
    return eliminado;
}

#endif //LISTADENLAZADA3_VDINAMICO_H