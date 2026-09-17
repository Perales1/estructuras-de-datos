/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file AVL.h
 * @brief Declaración e implementación de las clases Nodo2 y AVL para un árbol AVL balanceado.
 */
#include "VDinamico.h"

#ifndef PR3AVL_AVL_H
#define PR3AVL_AVL_H

/**
 * @brief Clase para los nodos del árbol AVL.
 *
 * La clase Nodo2 representa un nodo individual en un árbol AVL, con punteros
 * a los nodos hijo izquierdo y derecho, así como un dato almacenado y un
 * indicador de balance.
 *
 * @tparam T Tipo de los elementos almacenados en el nodo.
 */
template<class T>
class Nodo2 {
public:
    Nodo2<T> *izq, *der; ///< Punteros a los nodos hijo izquierdo y derecho.
    T dato;               ///< Elemento almacenado en el nodo.
    char bal;             ///< Factor de balance del nodo.

    /**
     * @brief Constructor para inicializar un nodo con un valor.
     * @param ele Valor del elemento a almacenar.
     */
    explicit Nodo2(T &ele) : izq(nullptr), der(nullptr), bal(0), dato(ele) {}
};

/**
 * @brief Clase para la implementación de un árbol AVL.
 *
 * La clase AVL permite almacenar y manipular datos en un árbol AVL, asegurando
 * un balance de altura para optimizar las operaciones de búsqueda, inserción y eliminación.
 *
 * @tparam T Tipo de los elementos almacenados en el árbol.
 */
template<class T>
class AVL {
public:

    AVL(); ///< Constructor por defecto.

    AVL(const AVL<T> &origen); ///< Constructor de copia.

    AVL<T> &operator=(const AVL<T> &origen); ///< Operador de asignación.

    ~AVL(); ///< Destructor.

    /**
     * @brief Búsqueda recursiva de un elemento en el árbol.
     * @param dato Elemento a buscar.
     * @return Puntero al dato encontrado o nullptr si no existe.
     */
    T *buscaREC(T &dato);

    /**
     * @brief Búsqueda iterativa de un elemento en el árbol.
     * @param dato Elemento a buscar.
     * @return Puntero al dato encontrado o nullptr si no existe.
     */
    T *buscaIT(T &dato);

    /**
     * @brief Obtiene el número de elementos en el árbol.
     * @return Número de elementos en el árbol.
     */
    unsigned int numElementos();

    /**
     * @brief Inserta un elemento en el árbol AVL.
     * @param dato Elemento a insertar.
     * @return True si la inserción fue exitosa, false en caso contrario.
     */
    bool inserta(T &dato);

    /**
     * @brief Calcula la altura del árbol.
     * @return Altura del árbol.
     */
    unsigned int alturaAux();

    /**
     * @brief Recorre el árbol en orden y devuelve un vector de punteros a los elementos.
     * @return Vector dinámico con punteros a los elementos en orden.
     */
    VDinamico<T *> recorreinorden();

    /**
     * @brief Recorre el árbol en preorden y devuelve un vector de punteros a los elementos.
     * @return Vector dinámico con punteros a los elementos en preorden.
     */
    VDinamico<T *> recorrepreorden();

private:

    VDinamico<T *> inorden(Nodo2<T> *p, VDinamico<T *> &v); ///< Recorrido en inorden auxiliar.

    VDinamico<T *> preorden(Nodo2<T> *p, VDinamico<T *> &v); ///< Recorrido en preorden auxiliar.

    unsigned int contador; ///< Número de elementos en el árbol.

    /**
     * @brief Inserta un elemento en el árbol de manera recursiva y lo balancea.
     * @param c Nodo actual en el árbol.
     * @param dato Elemento a insertar.
     * @return Variación de altura tras la inserción.
     */
    int inserta(Nodo2<T> *&c, T &dato);

    Nodo2<T> *raiz; ///< Puntero a la raíz del árbol.

    /**
     * @brief Rotación hacia la derecha para balancear el árbol.
     * @param p Nodo desbalanceado.
     */
    void rotDcha(Nodo2<T> *&P);

    /**
     * @brief Rotación hacia la izquierda para balancear el árbol.
     * @param p Nodo desbalanceado.
     */
    void rotIzq(Nodo2<T> *&p);

    /**
    * @brief Calcula la altura de un subárbol dado.
    * @param nodo2 Nodo raíz del subárbol.
    * @return Altura del subárbol.
    */
    unsigned int altura(Nodo2<T> *nodo2);

    /**
     * @brief Borra los nodos del árbol recursivamente.
     * @param nodo2 Nodo a eliminar.
     */
    void borrarNodos(Nodo2<T> *nodo2);

    /**
    * @brief Copia recursivamente los nodos de un árbol a otro.
    * @param nodo2 Nodo raíz del árbol a copiar.
    * @return Nodo raíz del árbol copiado.
    */
    Nodo2<T> *copiarNodos(Nodo2<T> *nodo2);

    /**
     * @brief Búsqueda recursiva auxiliar de un elemento en el árbol.
     * @param nodo2 Nodo actual en la búsqueda.
     * @param dato Elemento a buscar.
     * @return Puntero al dato encontrado o nullptr si no existe.
     */
    T *buscaRecAuxiliar(Nodo2<T> *nodo2, T &dato);
};

template<class T>
VDinamico<T *> AVL<T>::inorden(Nodo2<T> *p, VDinamico<T *> &v) {
    if (p != nullptr) {
        inorden(p->izq, v);
        v.insertar(&p->dato);
        inorden(p->der, v);
    }
    return v;
}

template<class T>
VDinamico<T *> AVL<T>::recorreinorden() {
    VDinamico<T *> v;
    return inorden(raiz, v);
}

template<class T>
VDinamico<T *> AVL<T>::preorden(Nodo2<T> *p, VDinamico<T *> &v) {
    if (p != nullptr) {
        v.insertar(&p->dato);
        preorden(p->izq, v);
        preorden(p->der, v);
    }
    return v;
}

template<class T>
VDinamico<T *> AVL<T>::recorrepreorden() {
    VDinamico<T *> v;
    return preorden(raiz, v);
}

template<class T>
AVL<T>::AVL():raiz(nullptr), contador(0) {}

template<class T>
AVL<T>::~AVL() {
    borrarNodos(raiz);
}

template<class T>
AVL<T>::AVL(const AVL<T> &origen) {
    raiz = copiarNodos(origen.raiz);
    contador = origen.contador;
}

template<class T>
AVL<T> &AVL<T>::operator=(const AVL<T> &origen) {
    if (this != &origen) {
        borrarNodos(raiz);
        raiz = copiarNodos(origen.raiz);
        contador = origen.contador;
    }
    return *this;
}

template<class T>
void AVL<T>::borrarNodos(Nodo2<T> *nodo2) {
    if (nodo2 != nullptr) {
        borrarNodos(nodo2->izq);
        borrarNodos(nodo2->der);
        delete nodo2;
        contador--;
    }
}

template<class T>
Nodo2<T> *AVL<T>::copiarNodos(Nodo2<T> *nodo2) {
    if (!nodo2) {
        return nullptr;
    }
    Nodo2<T> *nuevoNodo = new Nodo2<T>(nodo2->dato);
    nuevoNodo->izq = copiarNodos(nodo2->izq);
    nuevoNodo->der = copiarNodos(nodo2->der);
    nuevoNodo->bal = nodo2->bal;

    return nuevoNodo;
}

template<class T>
unsigned int AVL<T>::numElementos() {
    return contador;
}

template<class T>
T *AVL<T>::buscaIT(T &dato) {
    Nodo2<T> *nodo2 = raiz;
    while (nodo2) {
        if (dato < nodo2->dato) {
            nodo2 = nodo2->izq;
        } else if (dato > nodo2->dato) {
            nodo2 = nodo2->der;
        } else {
            return &nodo2->dato;
        }
    }
    return nullptr;
}

template<class T>
T *AVL<T>::buscaREC(T &dato) {
    Nodo2<T> *nodo2 = raiz;
    while (nodo2 != nullptr) {
        if (dato < nodo2->dato) {
            nodo2 = nodo2->izq;
        } else if (dato > nodo2->dato) {
            nodo2 = nodo2->der;
        } else {
            return &nodo2->dato;
        }
    }
    return nullptr;
}

template<class T>
T *AVL<T>::buscaRecAuxiliar(Nodo2<T> *nodo2, T &dato) {
    return buscaREC(raiz, dato);
}

template<class T>
unsigned int AVL<T>::alturaAux() {
    return altura(raiz);
}

template<class T>
unsigned int AVL<T>::altura(Nodo2<T> *nodo2) {
    if (nodo2 == nullptr) return 0;

    unsigned int alturaIzquierda = altura(nodo2->izq);
    unsigned int alturaDerecha = altura(nodo2->der);

    return 1 + (alturaIzquierda >= alturaDerecha ? alturaIzquierda : alturaDerecha);
}

template<typename T>
int AVL<T>::inserta(Nodo2<T> *&c, T &dato) {
    Nodo2<T> *p = c;
    int deltaH = 0;
    if (!p) {
        p = new Nodo2<T>(dato);
        c = p;
        deltaH = 1;
    } else if (dato > p->dato) {
        if (inserta(p->der, dato)) {
            p->bal--;
            if (p->bal == -1) deltaH = 1;
            else if (p->bal == -2) {
                if (p->der->bal == 1) rotDcha(p->der);
                rotIzq(c);
            }
        }
    } else if (dato < p->dato) {
        if (inserta(p->izq, dato)) {
            p->bal++;
            if (p->bal == 1) deltaH = 1;
            else if (p->bal == 2) {
                if (p->izq->bal == -1) rotIzq(p->izq);
                rotDcha(c);
            }
        }
    }
    return deltaH;
}

template<class T>
bool AVL<T>::inserta(T &dato) {
    return inserta(raiz, dato);
}

template<typename T>
void AVL<T>::rotIzq(Nodo2<T> *&p) {
    Nodo2<T> *q = p, *r;
    p = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if (q->bal > 0) r->bal += q->bal;
}

template<typename T>
void AVL<T>::rotDcha(Nodo2<T> *&p) {
    Nodo2<T> *q = p, *l;
    p = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if (q->bal < 0) l->bal -= -q->bal;
}


#endif //PR3AVL_AVL_H
