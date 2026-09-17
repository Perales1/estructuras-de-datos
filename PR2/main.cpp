/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file main.cpp
 * @brief Programa que utiliza una lista doblemente enlazada para realizar varias operaciones de inserción, eliminación y visualización de datos.
 */
#include <iostream>
#include "ListaDEnlazada.h"

/**
 * @brief Muestra los elementos de una lista doblemente enlazada.
 *
 * Esta función recorre la lista doblemente enlazada utilizando un iterador y muestra cada elemento en la consola.
 *
 * @tparam T Tipo de dato que contiene la lista.
 * @param lista Referencia a la lista doblemente enlazada que se desea mostrar.
 * @pre La lista debe estar correctamente inicializada.
 * @post Los elementos de la lista serán impresos en la consola.
 * @note La lista no debe estar vacía para mostrar elementos, pero si lo está, simplemente no imprimirá nada.
 */
template<class T>
void mostrarLista(ListaDEnlazada<T> &lista) {
    Iterador<T> iterador(lista.cabeza);
    while (iterador.haySiguiente()) {
        std::cout << iterador.dato() << " ";
        iterador.siguiente();
    }
    std::cout << std::endl;
}

/**
 * @brief Función principal del programa.
 *
 * Crea una lista doblemente enlazada, realiza inserciones de datos tanto al inicio como al final de la lista,
 * inserta elementos en ubicaciones específicas, elimina elementos de la lista, y finalmente imprime los resultados
 * de las operaciones en la consola.
 *
 * @return int Código de retorno del programa, 0 si se ejecuta correctamente.
 */
int main() {
    ListaDEnlazada<int> lista;

    for (int i = 101; i <= 200; ++i) {
        lista.insertaFin(i);
    }

    for (int i = 98; i >= 1; --i) {
        lista.insertaInicio(i);
    }

    Iterador<int> iterador = lista.iterador();
    while (iterador.haySiguiente() && iterador.dato() != 101) {
        iterador.siguiente();
    }
    lista.inserta(iterador, 100);

    iterador = lista.iterador();
    while (iterador.haySiguiente() && iterador.dato() != 98) {
        iterador.siguiente();
    }
    lista.inserta(iterador, 99);

    std::cout << " Lista despues de las inserciones: ";
    mostrarLista(lista);

    for (int i = 0; i < 10; ++i) {
        lista.borraInicio();
    }
    for (int i = 0; i < 10; ++i) {
        lista.borraFinal();
    }

    std::cout << " Lista despues de borrar los 10 primeros y 10 ultimos: ";
    mostrarLista(lista);

    iterador = lista.iterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato() % 10 == 0) {
            Iterador<int> tempIterador = iterador;
            iterador.siguiente();
            lista.borra(tempIterador);
        } else {
            iterador.siguiente();
        }
    }

    std::cout << " Lista final despues de borrar multiplos de 10: ";
    mostrarLista(lista);

    return 0;
}
