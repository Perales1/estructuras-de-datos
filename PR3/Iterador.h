/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Iterador.h
 * @brief Declaración e implementación de la clase Iterador.
 */
#ifndef PR3AVL_ITERADOR_H
#define PR3AVL_ITERADOR_H

template<class T>
class ListaDEnlazada;

template<class T>
class Nodo;

/**
 * @brief Clase Iterador que permite recorrer una lista doblemente enlazada.
 * @tparam T Tipo de dato que contendrá el iterador.
 */
template<class T>
class Iterador {
public:
    Nodo<T> *nodo;  ///< Puntero al nodo actual.
    friend class ListaDEnlazada<T>;  ///< Permite a ListaDEnlazada acceder a los atributos privados del iterador.///< public:

    /**
     * @brief Constructor que inicializa el iterador con un nodo dado.
     * @param aNodo Puntero al nodo que se utilizará para inicializar el iterador.
     * @pre El nodo debe ser válido o nullptr.
     * @post El iterador queda apuntando al nodo proporcionado.
     */
    Iterador(Nodo<T> *aNodo);

    /**
     * @brief Verifica si existe un nodo anterior en la lista.
     * @return true si hay un nodo anterior, false en caso contrario.
     * @pre El iterador debe estar apuntando a un nodo válido.
     * @post Ninguna.
     */
    bool hayAnterior();

    /**
     * @brief Verifica si existe un nodo siguiente en la lista.
     * @return true si hay un nodo siguiente, false en caso contrario.
     * @pre El iterador debe estar apuntando a un nodo válido.
     * @post Ninguna.
     */
    bool haySiguiente();

    /**
     * @brief Mueve el iterador al nodo anterior en la lista.
     * @pre El iterador debe estar apuntando a un nodo válido y debe haber un nodo anterior.
     * @post El iterador apuntará al nodo anterior si existe.
     * @note No se realiza ninguna acción si no hay nodo anterior.
     */
    void anterior();

    /**
    * @brief Mueve el iterador al nodo siguiente en la lista.
    * @pre El iterador debe estar apuntando a un nodo válido y debe haber un nodo siguiente.
    * @post El iterador apuntará al nodo siguiente si existe.
    * @note No se realiza ninguna acción si no hay nodo siguiente.
    */
    void siguiente();

    /**
     * @brief Devuelve una referencia al dato del nodo actual.
     * @return Referencia al dato almacenado en el nodo actual.
     * @pre El iterador debe estar apuntando a un nodo válido.
     * @post Ninguna.
     * @throw std::out_of_range Si el nodo es nullptr.
     */
    T &dato();
};

template<class T>
Iterador<T>::Iterador(Nodo<T> *aNodo) {
    nodo = aNodo;
}

template<class T>
bool Iterador<T>::hayAnterior() {
    return nodo != nullptr && nodo->ant != nullptr;
}

template<class T>
bool Iterador<T>::haySiguiente() {
    return nodo != nullptr && nodo->sig != nullptr;
}

template<class T>
void Iterador<T>::anterior() {
    if (hayAnterior()) nodo = nodo->ant;
}

template<class T>
void Iterador<T>::siguiente() {
    if (haySiguiente()) nodo = nodo->sig;
}

template<class T>
T &Iterador<T>::dato() {
    return nodo->dato;
}

#endif // PR3AVL_ITERADOR_H
