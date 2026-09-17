/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file ListaDEnlazada.h
 * @brief Declaración e implementación de la clase ListaDEnlazada y Nodo.
 */
#ifndef PR3AVL_LISTADENLAZADA_H
#define PR3AVL_LISTADENLAZADA_H

#include <iostream>
#include "Iterador.h"

/**
 * @brief Clase Nodo que representa un nodo de la lista doblemente enlazada.
 * @tparam T Tipo de dato que contiene el nodo.
 */
template<class T>
class Nodo {
public:
    T dato;             ///< Dato almacenado en el nodo.
    Nodo *ant;          ///< Puntero al nodo anterior.
    Nodo *sig;          ///< Puntero al nodo siguiente.

    /**
     * @brief Constructor que inicializa el nodo con un dato.
     * @param dato_ Dato que se almacenará en el nodo.
     */
    Nodo(const T &dato);
};

template<class T>
Nodo<T>::Nodo(const T &dato):dato(dato) {
    ant = nullptr;
    sig = nullptr;
}

/**
 * @brief Clase ListaDEnlazada que representa una lista doblemente enlazada.
 * @tparam T Tipo de dato que contendrá la lista.
 */
template<class T>
class ListaDEnlazada {
public:
    Nodo<T> *cabeza;    ///< Puntero al primer nodo de la lista.
    Nodo<T> *cola;      ///< Puntero al último nodo de la lista.
    int tamanio;        ///< Número de elementos en la lista.

    /**
     * @brief Constructor por defecto que inicializa la lista vacía.
     * @pre Ninguna.
     * @post La lista está vacía (cabeza y cola son nullptr).
     */
    ListaDEnlazada();

    /**
     * @brief Constructor de copia que inicializa la lista como una copia de otra.
     * @param origen Lista que se va a copiar.
     * @pre La lista origen debe estar correctamente inicializada.
     * @post La nueva lista es una copia profunda de la lista origen.
     */
    ListaDEnlazada(const ListaDEnlazada<T> &origen);

    /**
     * @brief Destructor que libera toda la memoria utilizada por la lista.
     * @pre Ninguna.
     * @post Todos los nodos de la lista son eliminados.
     */
    ~ListaDEnlazada();

    /**
     * @brief Operador de asignación para copiar otra lista a esta.
     * @param origen Lista a copiar.
     * @return Referencia a esta lista modificada.
     * @pre La lista origen debe estar correctamente inicializada.
     * @post Esta lista será una copia profunda de la lista origen.
     */
    ListaDEnlazada<T> &operator=(const ListaDEnlazada<T> &origen);

    /**
     * @brief Devuelve el primer elemento de la lista.
     * @return Referencia al primer elemento.
     * @throw std::out_of_range Si la lista está vacía.
     * @pre La lista no debe estar vacía.
     * @post Ninguna.
     */
    T &inicio();

    /**
     * @brief Devuelve el último elemento de la lista.
     * @return Referencia al último elemento.
     * @throw std::out_of_range Si la lista está vacía.
     * @pre La lista no debe estar vacía.
     * @post Ninguna.
     */
    T &fin();

    /**
     * @brief Crea un iterador que apunta al inicio de la lista.
     * @return Iterador que apunta al primer nodo de la lista.
     * @pre Ninguna.
     * @post El iterador apunta a la cabeza de la lista.
     */
    Iterador <T> iterador();

    /**
    * @brief Inserta un elemento al inicio de la lista.
    * @param dato Elemento a insertar.
    * @pre Ninguna.
    * @post El nuevo elemento será el primero en la lista.
    */
    void insertaInicio(const T &dato);

    /**
     * @brief Inserta un elemento al final de la lista.
     * @param dato Elemento a insertar.
     * @pre Ninguna.
     * @post El nuevo elemento será el último en la lista.
     */
    void insertaFin(const T &dato);

    /**
     * @brief Inserta un elemento antes de la posición del iterador.
     * @param i Iterador que indica la posición donde se va a insertar.
     * @param dato Elemento a insertar.
     * @pre El iterador debe ser válido.
     * @post El nuevo elemento estará antes de la posición indicada por el iterador.
     */
    void inserta(Iterador <T> &i, const T &dato);

    /**
     * @brief Elimina el primer elemento de la lista.
     * @pre La lista no debe estar vacía.
     * @post El primer elemento es eliminado de la lista.
     */
    void borraInicio();

    /**
     * @brief Elimina el último elemento de la lista.
     * @pre La lista no debe estar vacía.
     * @post El último elemento es eliminado de la lista.
     */
    void borraFinal();

    /**
     * @brief Elimina el elemento en la posición del iterador.
     * @param i Iterador que apunta al nodo a eliminar.
     * @pre El iterador debe ser válido.
     * @post El nodo indicado por el iterador es eliminado.
     */
    void borra(Iterador <T> &i);

    /**
     * @brief Devuelve el tamaño de la lista.
     * @return Número de elementos en la lista.
     * @pre Ninguna.
     * @post Ninguna.
     */
    int tam();

    /**
     * @brief Concatena otra lista al final de esta.
     * @param lista Lista a concatenar.
     * @pre La lista debe estar correctamente inicializada.
     * @post Los elementos de la lista dada se añaden al final de esta lista.
     */
    void concatena(const ListaDEnlazada<T> &l);

};

template<class T>
ListaDEnlazada<T>::ListaDEnlazada() {
    cabeza = nullptr;
    cola = nullptr;
    tamanio = 0;
}

template<class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada<T> &origen) : cabeza(nullptr), cola(nullptr), tamanio(0) {
    Nodo<T> *actual = origen.cabeza;
    while (actual != nullptr) {
        insertaFin(actual->dato);
        actual = actual->sig;
    }
}

template<class T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    while (cabeza != nullptr) {
        borraInicio();
    }
}

template<class T>
ListaDEnlazada<T> &ListaDEnlazada<T>::operator=(const ListaDEnlazada<T> &origen) {
    if (this != &origen) {
        while (cabeza != nullptr) {
            borraInicio();
        }
        Nodo<T> *actual = origen.cabeza;
        while (actual != nullptr) {
            insertaFin(actual->dato);
            actual = actual->sig;
        }
    }
    return *this;
}

template<class T>
T &ListaDEnlazada<T>::inicio() {
    if (cabeza != nullptr) return cabeza->dato;
    throw std::out_of_range("La lista está vacía");
}

template<class T>
T &ListaDEnlazada<T>::fin() {
    if (cola != nullptr) return cola->dato;
    throw std::out_of_range("La lista está vacía");
}

template<class T>
Iterador <T> ListaDEnlazada<T>::iterador() {
    return Iterador<T>(cabeza);
}

template<class T>
void ListaDEnlazada<T>::insertaInicio(const T &dato) {
    Nodo<T> *nuevo = new Nodo<T>(dato);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        nuevo->sig = cabeza;
        cabeza->ant = nuevo;
        cabeza = nuevo;
    }
    tamanio++;
}

template<class T>
void ListaDEnlazada<T>::insertaFin(const T &dato) {
    Nodo<T> *nuevo = new Nodo<T>(dato);
    if (cola == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        nuevo->ant = cola;
        cola->sig = nuevo;
        cola = nuevo;
    }
    tamanio++;
}

template<class T>
void ListaDEnlazada<T>::inserta(Iterador <T> &i, const T &dato) {
    Nodo<T> *nuevo = new Nodo<T>(dato);
    if (i.nodo == cabeza) {
        insertaInicio(dato);
    } else if (i.nodo == nullptr) {
        insertaFin(dato);
    } else {
        nuevo->ant = i.nodo->ant;
        nuevo->sig = i.nodo;
        if (i.nodo->ant != nullptr) {
            i.nodo->ant->sig = nuevo;
        }
        i.nodo->ant = nuevo;
        tamanio++;
    }
}

template<class T>
void ListaDEnlazada<T>::borraInicio() {
    if (cabeza != nullptr) {
        Nodo<T> *temp = cabeza;
        cabeza = cabeza->sig;
        if (cabeza != nullptr) {
            cabeza->ant = nullptr;
        } else {
            cola = nullptr;
        }
        delete temp;
        tamanio--;
    }
}

template<class T>
void ListaDEnlazada<T>::borraFinal() {
    if (cola != nullptr) {
        Nodo<T> *temp = cola;
        cola = cola->ant;
        if (cola != nullptr) {
            cola->sig = nullptr;
        } else {
            cabeza = nullptr;
        }
        delete temp;
        tamanio--;
    }
}

template<class T>
void ListaDEnlazada<T>::borra(Iterador <T> &i) {
    if (i.nodo != nullptr) {
        if (i.nodo == cabeza) {
            borraInicio();
        } else if (i.nodo == cola) {
            borraFinal();
        } else {
            Nodo<T> *temp = i.nodo;
            if (temp->ant != nullptr) {
                temp->ant->sig = temp->sig;
            }
            if (temp->sig != nullptr) {
                temp->sig->ant = temp->ant;
            }
            delete temp;
            tamanio--;
        }
    }
}

template<class T>
int ListaDEnlazada<T>::tam() {
    return tamanio;
}

template<class T>
void ListaDEnlazada<T>::concatena(const ListaDEnlazada<T> &lista) {
    if (lista.cabeza != nullptr) {
        Nodo<T> *actual = lista.cabeza;
        while (actual != nullptr) {
            insertaFin(actual->dato);
            actual = actual->sig;
        }
    }
}

#endif // PR3AVL_LISTADENLAZADA_H