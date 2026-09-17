/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Coche.h
 * @brief Declaración e implementación de la clase Coche.
 */
#ifndef LISTADENLAZADA3_COCHE_H
#define LISTADENLAZADA3_COCHE_H

#include <iostream>
#include <string>

/**
 * @brief Clase que representa un coche.
 *
 * La clase Coche almacena información básica sobre un coche,
 * incluyendo su matrícula, marca y modelo. Además, proporciona
 * operadores de comparación y funciones de entrada/salida.
 */
class Coche {
private:
    std::string id_matricula; ///< Matrícula del coche.
    std::string marca;        ///< Marca del coche.
    std::string modelo;       ///< Modelo del coche.

public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa un coche con matrícula, marca y modelo vacíos.
     */
    Coche() : id_matricula(""), marca(""), modelo("") {}

    /**
     * @brief Constructor con parámetros.
     *
     * @param idMatricula Matrícula del coche.
     * @param marca Marca del coche.
     * @param modelo Modelo del coche.
     */
    Coche(const std::string &idMatricula, const std::string &marca, const std::string &modelo)
            : id_matricula(idMatricula), marca(marca), modelo(modelo) {}

    /**
     * @brief Obtiene la matrícula del coche.
     *
     * @return Referencia constante a la matrícula del coche.
     */
    const std::string &getIdMatricula() const {
        return id_matricula;
    }

    /**
     * @brief Establece la matrícula del coche.
     *
     * @param idMatricula Nueva matrícula para el coche.
     */
    void setIdMatricula(const std::string &idMatricula) {
        id_matricula = idMatricula;
    }

    /**
     * @brief Obtiene la marca del coche.
     *
     * @return Referencia constante a la marca del coche.
     */
    const std::string &getMarca() const {
        return marca;
    }

    /**
     * @brief Establece la marca del coche.
     *
     * @param marca Nueva marca para el coche.
     */
    void setMarca(const std::string &marca) {
        this->marca = marca;
    }

    /**
     * @brief Obtiene el modelo del coche.
     *
     * @return Referencia constante a la modelo del coche.
     */
    const std::string &getModelo() const {
        return modelo;
    }

    /**
     * @brief Establece el modelo del coche.
     *
     * @param modelo Nuevo modelo para el coche.
     */
    void setModelo(const std::string &modelo) {
        this->modelo = modelo;
    }

    /**
     * @brief Destructor.
     *
     * Libera los recursos asignados por la clase Coche.
     */
    virtual ~Coche() = default;

    /**
     * @brief Operador de salida.
     *
     * Permite imprimir la información del coche en un flujo de salida.
     *
     * @param os Flujo de salida.
     * @param coche Objeto coche que se va a imprimir.
     * @return Referencia al flujo de salida.
     */
    friend std::ostream &operator<<(std::ostream &os, const Coche &coche) {
        os << "id_matricula: " << coche.id_matricula << " marca: " << coche.marca << " modelo: " << coche.modelo;
        return os;
    }

    /**
     * @brief Compara dos coches por matrícula.
     *
     * @param rhs Coche a comparar.
     * @return True si las matrículas son iguales, false en caso contrario.
     */
    bool operator==(const Coche &rhs) const {
        return id_matricula == rhs.id_matricula;
    }

    /**
     * @brief Compara si la matrícula del coche es menor que otra.
     *
     * @param rhs Coche a comparar.
     * @return True si la matrícula del coche actual es menor, false en caso contrario.
     */
    bool operator<(const Coche &rhs) const {
        return modelo < rhs.modelo;  // Comparación por modelo de coche
    }

    /**
     * @brief Compara si la matrícula del coche es mayor que otra.
     *
     * @param rhs Coche a comparar.
     * @return True si la matrícula del coche actual es mayor, false en caso contrario.
     */
    bool operator>(const Coche &rhs) const {
        return rhs < *this;
    }

    /**
     * @brief Compara si la matrícula del coche es menor o igual a otra.
     *
     * @param rhs Coche a comparar.
     * @return True si la matrícula del coche actual es menor o igual, false en caso contrario.
     */
    bool operator<=(const Coche &rhs) const {
        return !(rhs < *this);
    }

    /**
     * @brief Compara si la matrícula del coche es mayor o igual a otra.
     *
     * @param rhs Coche a comparar.
     * @return True si la matrícula del coche actual es mayor o igual, false en caso contrario.
     */
    bool operator>=(const Coche &rhs) const {
        return !(*this < rhs);
    }

    /**
     * @brief Compara si dos coches son diferentes por matrícula.
     *
     * @param rhs Coche a comparar.
     * @return True si las matrículas son diferentes, false en caso contrario.
     */
    bool operator!=(const Coche &rhs) const {
        return !(rhs == *this);
    }
};

#endif // LISTADENLAZADA3_COCHE_H
