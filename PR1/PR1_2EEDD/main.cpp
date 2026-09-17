/** @author David Fernández Espejo dfe00004@red.ujaen.es
 *   @author David Lorente Wagner dlw00001@red.ujaen.es
 *   @note Este programa está realizado utilizando librerías externas, obteniendo un rendimiento mayor.
 */

#include "VDinamico.h"

int Aleatorio(int maximo) {
    unsigned semilla = std::chrono::system_clock::now().time_since_epoch().count(); //Variable para generar un numero aleatorio por cada ejecución
    static std::mt19937 generador(semilla); //Asignación del numero aleatorio a la función generador()
    std::uniform_int_distribution<int> distribucion(1, maximo);
    return distribucion(generador);
}

int main() {
    static const unsigned int TMAX = 1000000;
    VDinamico<int> vector(TMAX);

    std::cout << "Iniciando generacion de numeros aleatorios..." << std::endl;

    std::unordered_set<int> numerosUnicos;
    while (numerosUnicos.size() < TMAX) {
        int n = Aleatorio(TMAX * 10);
        numerosUnicos.insert(n);
    }

    std::cout << "Todos los numeros unicos han sido generados. Total: " << numerosUnicos.size() << std::endl;

    int i = 0;
    for (int num: numerosUnicos) {
        vector[i++] = num;
    }

    std::cout << "Vector lleno. Comenzando a ordenar..." << std::endl;
    vector.ordenar();
    std::cout << "Ordenacion completa." << std::endl;

    static const unsigned int posicionconcreta = 200;
    std::cout << "Los 200 primeros elementos del vector original son: " << std::endl;
    for (int i = 0; i < posicionconcreta; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;

    VDinamico<int> vectorCopia = vector;

    std::cout << "Comenzando la ordenacion quicksort..." << std::endl;
    vector.ordenar2();
    std::cout << "Ordenacion quicksort completa." << std::endl;
    std::cout << "Los 200 primeros elementos del vector con el algoritmo de ordenacion quicksort: " << std::endl;
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