/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Hash.cpp
 * @brief Implementación de la clase Hash, que representa la estructura de una tabla de dispersión
 */

#include "Hash.h"
#include <cmath>

/**
 * @brief Verifica si un número es primo
 * @param num Número a verificar si es primo o no
 * @return True si el número es primo, False si el número no es primo
 */
bool esprimo(int num) {
    if (num <= 1) return false;
    for (int i = 2; i < sqrt(num); ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

/**
 * @brief Calcula el siguiente número primo a partir de un número dado
 * @param num Número entero a partir del cuál se buscará el siguiente número primo
 * @return Siguiente número primo
 */
int siguientePrimo(int num) {
    while (!esprimo(num)) {
        num++;
    }
    return num;
}

ThashUsuario::ThashUsuario(int maxElem, float lambda, TipoHash tipo) : numElementos(0),
                                                                       lambda(lambda), tipoHash(tipo) {
    int tamInicial = siguientePrimo(std::ceil((maxElem / lambda)));
    tabla.resize(tamInicial);
    maxElementos = std::floor(tamInicial * lambda);
}

ThashUsuario::ThashUsuario(const ThashUsuario &thashUsuario) :
        tabla(thashUsuario.tabla), maxElementos(thashUsuario.maxElementos), numElementos(thashUsuario.numElementos),
        lambda(thashUsuario.lambda), tipoHash(thashUsuario.tipoHash) {}

ThashUsuario &ThashUsuario::operator=(const ThashUsuario &thashUsuario) {
    if (this != &thashUsuario) {
        tabla = thashUsuario.tabla;
        maxElementos = thashUsuario.maxElementos;
        numElementos = thashUsuario.numElementos;
        lambda = thashUsuario.lambda;
        tipoHash = thashUsuario.tipoHash;
    }
    return *this;
}

ThashUsuario::~ThashUsuario() {}

bool ThashUsuario::insertar(unsigned long claveHash, Usuario &usuario) {
    if (numElementos >= maxElementos) {
        std::cerr << " Error se ha alcanzado el numero maximo de elementos. " << std::endl;
        /// REDISPERSAR
        unsigned nuevoTam = std::ceil(tamTabla() * 1.3);
        redispersar(nuevoTam);
    }

    int intento = 0;
    while (true) {
        unsigned int pos = hash(claveHash, intento);
        if (tabla[pos].vacia()) {
            tabla[pos] = EntradaUsuario(claveHash, usuario);
            numElementos++;
            return true;
        } else if (tabla[pos].getClaveHash() == claveHash) {
            return false;
        }
        intento++;
    }
}

Usuario *ThashUsuario::buscar(unsigned long claveHash) {
    int intento = 0;
    int maxIntentos = tamTabla();
    while (intento < maxIntentos) {
        unsigned int pos = hashDoble(claveHash, intento) % tamTabla();

        if (tabla[pos].vacia()) {
            return nullptr;
        }

        if (tabla[pos].getClaveHash() == claveHash) {
            return tabla[pos].getUsuario();
        }
        intento++;
    }
    return nullptr;
}

bool ThashUsuario::borrar(unsigned long claveHash) {
    int intento = 0;
    while (true) {
        unsigned int pos = hash(claveHash, intento);
        if (tabla[pos].vacia()) {
            return false;
        }
        if (tabla[pos].getClaveHash() == claveHash) {
            tabla[pos].vaciar();
            numElementos--;
            return true;
        }
        intento++;
    }
}

unsigned long ThashUsuario::djb2(const std::string &str) {
    unsigned long hash = 5381;

    for (char c: str) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}


float ThashUsuario::factorCarga() {
    return lambda;
}

unsigned int ThashUsuario::tamTabla() {
    return tabla.size();
}

void ThashUsuario::mostrarEstadoTabla() {
    std::cout << "Estado de la tabla de dispersion de usuarios:" << std::endl;
    std::cout << "Tamanio de la tabla: " << tamTabla() << std::endl;
    std::cout << "Numero de elementos: " << numElementos << std::endl;
    std::cout << "Numero maximo de elementos: " << maxElementos << std::endl;
    std::cout << "Factor de carga: " << factorCarga() << std::endl;
    std::cout << "Maximo numero de colisiones: " << maxColisiones() << std::endl;
    std::cout << "Numero de inserciones con mas de 10 colisiones: " << numMax10() << std::endl;
    std::cout << "Promedio de colisiones: " << promedioColisiones() << std::endl;
    std::cout << "Numero de redispersiones: " << numRedispersiones << std::endl;
}

float ThashUsuario::promedioColisiones() {
    float totalColisiones = 0;
    float totalInserciones = 0;

    for (EntradaUsuario const &i: tabla) {
        if (!i.vacia()) {
            float intento = 0;
            unsigned long claveHash = i.getClaveHash();
            while (true) {
                unsigned int pos = hash(claveHash, intento);
                if (tabla[pos].vacia() || tabla[pos].getClaveHash() == claveHash) {
                    totalColisiones += intento;
                    totalInserciones++;
                    break;
                }
                intento++;
            }
        }
    }
    if (totalInserciones == 0) {
        std::cerr << " Proteccion contra la division entre 0. " << std::endl;
        return 0;
    }
    float resultado = totalColisiones / totalInserciones;
    return resultado;
}

unsigned int ThashUsuario::numMax10() {
    unsigned int numColisiones = 0;

    for (EntradaUsuario const &i: tabla) {
        if (!i.vacia()) {
            int intento = 0;
            unsigned long claveHash = i.getClaveHash();
            while (true) {
                unsigned int pos = hash(claveHash, intento);
                if (tabla[pos].vacia() || tabla[pos].getClaveHash() == claveHash) {
                    break;
                }
                intento++;
            }
            if (intento > 10) {
                numColisiones++;
            }
        }
    }
    return numColisiones;
}

unsigned int ThashUsuario::maxColisiones() {
    unsigned int maxCol = 0;

    for (EntradaUsuario const &i: tabla) {
        if (!i.vacia()) {
            int intento = 0;
            unsigned long claveHash = i.getClaveHash();
            while (true) {
                unsigned int pos = hash(claveHash, intento);
                if (tabla[pos].vacia() || tabla[pos].getClaveHash() == claveHash) {
                    break;
                }
                intento++;
            }
            maxCol = std::max(maxCol, (unsigned int) intento);
        }
    }
    return maxCol;
}

std::vector<Usuario *> ThashUsuario::obtenerUsuariosValidos() const {
    std::vector<Usuario *> usuarios;
    for (EntradaUsuario const &entrada: tabla) {
        if (!entrada.vacia()) {
            usuarios.push_back(entrada.getUsuario());
        }
    }
    return usuarios;
}

void ThashUsuario::setLambda(float lambda_) {
    this->lambda = lambda_;
}

void ThashUsuario::redispersar(unsigned tam) {
    unsigned nuevoTam = siguientePrimo(tam);

    std::vector<EntradaUsuario> nuevaTabla(nuevoTam);

    for (EntradaUsuario const &entrada: tabla) {
        if (!entrada.vacia()) {

            unsigned long claveHash = entrada.getClaveHash();
            Usuario *usuario = entrada.getUsuario();
            int intento = 0;

            while (true) {
                unsigned int pos = hashDoble(claveHash, intento) % nuevoTam;
                if (nuevaTabla[pos].vacia()) {
                    nuevaTabla[pos] = EntradaUsuario(claveHash, *usuario);
                    break;
                }
                intento++;
            }
        }
    }
    tabla = std::move(nuevaTabla);
    maxElementos = std::floor(nuevoTam * lambda);
    numRedispersiones++;
}