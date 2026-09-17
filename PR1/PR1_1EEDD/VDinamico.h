#ifndef PR1_1EEDD_VDINAMICO_H
#define PR1_1EEDD_VDINAMICO_H

#include <iostream>
#include <stdexcept>
#include <algorithm>

    /**
     * @class VDinamico
     * @brief Clase plantilla que implementa un vector dinamico generico.
     *
     * Esta clase permite la creacion y manipulacion de un vector dinamico
     * para almacenar datos de tipo generico T.
     *
     * @tparam T Tipo de dato que almacenara el vector.
     */

template<class T>
class VDinamico {
private:
    T *mem;            /**< Puntero a la memoria que almacena los elementos. */
    unsigned int tam;      /**< Tamaño del vector. */
public:

    /**
     * @brief Constructor que reserva memoria para n elementos.
     *
     * @pre n debe ser mayor que 0.
     * @post Se inicializa el vector dinamico con n elementos.
     *
     * @param n Cantidad de elementos a almacenar.
     */

    explicit VDinamico(unsigned int n);

    /**
     * @brief Constructor de copia.
     *
     * @pre El objeto other debe ser valido y estar correctamente inicializado.
     * @post Se crea una copia profunda de los elementos en other.
     *
     * @param other Objeto a copiar.
     */

    VDinamico(const VDinamico<T> &other);

    /**
     * @brief Constructor que copia un rango especifico de otro VDinamico.
     *
     * @pre La suma de posicionInicial y numElementos no debe exceder el tamaño de other.
     * @post Se inicializa un nuevo vector copiando un subconjunto de elementos del otro vector.
     *
     * @param other Objeto del cual se copiaran los elementos.
     * @param posicionInicial Posicion inicial para comenzar la copia.
     * @param numElementos Numero de elementos a copiar.
     * @throws std::out_of_range Si los indices estan fuera del rango valido.
     */

    VDinamico(const VDinamico<T> &other, unsigned int posicionInicial, unsigned int numElementos);

    /**
    * @brief Destructor. Libera la memoria asignada dinamicamente.
    *
    * @pre Ninguna.
    * @post La memoria asignada para el vector dinamico es liberada.
    */

    virtual ~VDinamico();

    /**
     * @brief Sobrecarga del operador de asignacion.
     *
     * @pre El objeto other debe estar correctamente inicializado.
     * @post Se asignan los elementos del objeto other al objeto actual.
     *
     * @note Si el objeto actual ya tiene memoria asignada, esta es liberada.
     * @param other Objeto del cual se copiaran los elementos.
     * @return Referencia al objeto asignado.
     */

    VDinamico<T> &operator=(const VDinamico<T> &other);

    /**
     * @brief Sobrecarga del operador de acceso mediante indice.
     *
     * @pre El indice debe estar dentro del rango [0, tam-1].
     * @post Se devuelve una referencia al elemento en la posicion especificada.
     *
     * @param pos Indice del elemento a acceder.
     * @return Referencia al elemento en la posicion especificada.
     * @throws std::out_of_range Si el indice esta fuera del rango valido.
     */

    T &operator[](unsigned int pos);

    /**
     * @brief Ordena los elementos del vector en orden ascendente.
     *
     * @pre El vector debe estar correctamente inicializado.
     * @post El vector queda ordenado en orden ascendente.
     */

    void ordenar();

    /**
    * @brief Ordena el vector usando el algoritmo Burbuja.
    *
    * Esta función implementa el algoritmo Burbuja para ordenar
    * los elementos del vector de forma ascendente.
    *
    * @pre El vector debe estar inicializado y contener elementos.
    * @post El vector estara ordenado en orden ascendente.
    */

    void ordenar2();

    /**
     * @brief Sobrecarga del operador de igualdad.
     *
     * Compara el tamaño (tam) y contenido de dos vectores para determinar si ambos son iguales,
     * en caso afirmativo la función devuelve "true" y en caso negativo, la función devuelve "false".
     *
     * @param other Referencia a otro objeto, que se compara con el objeto actual.
     * @return true si al comparar ambos vectores son iguales en cuanto a tamaño y contenido.
     * @return false si al comprar ambos vectores tienen distinto tamaño o contenido.
     */

    bool operator==(const VDinamico<T> &other); // Para comprobar la función de son Iguales los vectores
};

template<class T>
VDinamico<T>::VDinamico(unsigned int n) {
    tam = n;
    mem = new T[tam];
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &other) {
    tam = other.tam;
    mem = new T[tam];
    for (int i = 0; i < tam; ++i) {
        mem[i] = other.mem[i];
    }
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &other, unsigned int posicionInicial, unsigned int numElementos) {
    if (posicionInicial + numElementos > other.tam) {
        throw std::out_of_range(" Posicion inicial invalida. ");
    }
    tam = numElementos;
    mem = new T[tam];
    for (int i = 0; i < tam; ++i) {
        mem[i] = other.mem[posicionInicial + i];
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
        tam = other.tam;
        mem = new T[tam];
        for (int i = 0; i < tam; ++i) {
            mem[i] = other.mem[i];
        }
    }
    return *this;
}

template<class T>
T &VDinamico<T>::operator[](unsigned int pos) {
    if (pos >= tam) {
        throw std::out_of_range(" Posicion fuera de rango. ");
    }
    return mem[pos];
}

template<class T>
void VDinamico<T>::ordenar() {
    std::sort(mem, mem + tam);
}

template<class T>
void VDinamico<T>::ordenar2() {
    for (int i = 0; i < tam - 1; ++i) {
        for (int j = 0; j < tam - i - 1; ++j) {
            if (mem[j] > mem[j + 1]) {
                T temp = mem[j];
                mem[j] = mem[j + 1];
                mem[j + 1] = temp;
            }
        }
    }
}

template<class T>
bool VDinamico<T>::operator==(const VDinamico<T> &other) {
    if (tam != other.tam)
        return false;
    for (int i = 0; i < tam; ++i) {
        if (mem[i] != other.mem[i]) {
            return false;
        }
    }
    return true;
}

#endif //PR1_1EEDD_VDINAMICO_H
