/** @author David Fernández Espejo dfe00004@red.ujaen.es
 *   @author David Lorente Wagner dlw00001@red.ujaen.es
 *   @note Este programa está realizado sin utilizar librerias externas, obteniendo un rendimiento menor.
 */

#include "VDinamico.h"
#include <vector>

int Aleatorio(int maximo) { // Crea un número aleatorio con el uso de una semilla, en este caso 123
    static unsigned int semilla = 123;
    semilla = (semilla * 1231221412412 + 123) % maximo;
    return semilla;
}

int main() {
    static const unsigned int TMAX = 1000;
    VDinamico<int> vector(TMAX);

    std::cout << "Iniciando generacion de numeros aleatorios..." << std::endl;

    std::vector<int> vectorunico;
    while (vectorunico.size() < TMAX) {
        int n = Aleatorio(TMAX * 10) + 1;
        bool esta = false;
        for (int i = 0; i < vectorunico.size(); ++i) {
            if (vectorunico[i] == n) {
                esta = true;
                break;
            }
        }
        if (!esta) {
            vectorunico.push_back(n); // Para agregar el numero generado aleatoriamente unico
        }
        if (vectorunico.size() % 10000 == 0) {
            std::cout << "Generados " << vectorunico.size() << " numeros unicos." << std::endl;
        }
    }

    std::cout << "Todos los números únicos han sido generados. Total: " << vectorunico.size() << std::endl;

    for (int i = 0; i < TMAX; ++i) {
        vector[i] = vectorunico[i];
    }

    std::cout << "Vector lleno. Comenzando a ordenar..." << std::endl;
    vector.ordenar();
    std::cout << "Ordenacion completa." << std::endl;

    static const unsigned int posicionconcreta = 200;
    std::cout << " Los 200 primeros elementos del vector original son: " << std::endl;
    for (int i = 0; i < posicionconcreta; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;

    VDinamico<int> vectorCopia = vector;

    std::cout << "Comenzando la ordenación burbuja..." << std::endl;
    vector.ordenar2();
    std::cout << "Ordenacion burbuja completa." << std::endl;
    std::cout << " Los 200 primeros elementos del vector con el algoritmo de ordenación burbuja: " << std::endl;
    for (int i = 0; i < posicionconcreta; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;

    if (vector == vectorCopia) {
        std::cout << "Ambos vectores son iguales. " << std::endl;
    } else {
        std::cout << "Los vectores no son iguales. " << std::endl;
    }

    return 0;
}
