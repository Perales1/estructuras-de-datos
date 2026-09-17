/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Coche.h
 * @brief Declaración de la clase Coche que representa un vehículo eléctrico con atributos como matrícula, marca, modelo,
 * y métodos para simular su funcionamiento y gestionar su estado de carga.
 */
#ifndef PR3AVL_COCHE_H
#define PR3AVL_COCHE_H

#include <string>
#include <ostream>
#include <cstdlib>
#include "PuntoRecarga.h"

/**
 * @brief Declaración anticipada de la clase PuntoRecarga.
 */
class PuntoRecarga;

/**
 * @brief Clase que representa un coche eléctrico.
 *
 * La clase Coche encapsula la información de un vehículo eléctrico, incluyendo
 * su identificación (matrícula), marca, modelo, estado de la batería, y la
 * asociación a un punto de recarga.
 */
class Coche {
private:
    std::string id_matricula; ///< Matrícula del coche.
    std::string marca; ///< Marca del coche.
    std::string modelo; ///< Modelo del coche.
    PuntoRecarga *puntoRecarga; ///< Puntero al punto de recarga asociado.
    double bateria; ///< Nivel de batería del coche.

public:

    /**
     * @brief Constructor por defecto. Inicializa un coche sin especificar atributos.
     */
    Coche();

    /**
     * @brief Constructor que inicializa el coche con su matrícula, marca y modelo.
     * @param id_matricula Matrícula del coche.
     * @param marca Marca del coche.
     * @param modelo Modelo del coche.
     */
    Coche(const std::string &id_matricula, const std::string &marca, const std::string &modelo);

    /**
     * @brief Destructor por defecto.
     */
    ~Coche() = default;

    /**
     * @brief Obtiene la matrícula del coche.
     * @return Referencia constante a la matrícula.
     */
    [[nodiscard]] const std::string &getIdMatricula() const;

    /**
     * @brief Establece la matrícula del coche.
     * @param idMatricula Nueva matrícula del coche.
     */
    void setIdMatricula(const std::string &idMatricula);

    /**
     * @brief Obtiene la marca del coche.
     * @return Referencia constante a la marca.
     */
    [[nodiscard]] const std::string &getMarca() const;

    /**
     * @brief Establece la marca del coche.
     * @param _marca Nueva marca del coche.
     */
    void setMarca(const std::string &_marca);

    /**
     * @brief Obtiene el modelo del coche.
     * @return Referencia constante al modelo.
     */
    [[nodiscard]] const std::string &getModelo() const;

    /**
     * @brief Establece el modelo del coche.
     * @param modelo_ Nuevo modelo del coche.
     */
    void setModelo(const std::string &modelo_);

    /**
     * @brief Obtiene el punto de recarga asociado al coche.
     * @return Puntero al punto de recarga.
     */
    [[nodiscard]] PuntoRecarga *getPuntoRecarga() const;

    /**
     * @brief Asigna un punto de recarga al coche.
     * @param puntoRecarga_ Puntero al punto de recarga.
     */
    void setPuntoRecarga(PuntoRecarga *puntoRecarga_);

    /**
     * @brief Obtiene el nivel de batería actual del coche.
     * @return Nivel de batería del coche.
     */
    [[nodiscard]] double getBateria() const;

    /**
     * @brief Establece el nivel de batería del coche.
     * @param bateria_ Nuevo nivel de batería.
     */
    void setBateria(double bateria_);

    /**
     * @brief Simula el movimiento del coche eliminándolo del punto de recarga
     */
    void circular();

    /**
     * @brief Sobrecarga del operador de igualdad.
     * @param rhs Coche con el que se compara.
     * @return True si los coches son iguales, false en caso contrario.
     * @note Realiza la comparación por matrícula
     */
    bool operator==(const Coche &rhs) const;

    /**
     * @brief Sobrecarga del operador de desigualdad.
     * @param rhs Coche con el que se compara.
     * @return True si los coches son diferentes, false en caso contrario.
     * @note Realiza la comparación por matrícula
     */
    bool operator!=(const Coche &rhs) const;

    /**
     * @brief Sobrecarga del operador mayor que.
     * @param rhs Coche con el que se compara.
     * @return True si el coche actual es mayor que rhs, false en caso contrario.
     * @note Realiza la comparación por matrícula
     */
    bool operator>(const Coche &rhs) const;

    /**
     * @brief Sobrecarga del operador menor que.
     * @param rhs Coche con el que se compara.
     * @return True si el coche actual es menor que rhs, false en caso contrario.
     * @note Realiza la comparación por matrícula
     */
    bool operator<(const Coche &rhs) const;

    /**
     * @brief Sobrecarga del operador menor o igual que.
     * @param rhs Coche con el que se compara.
     * @return True si el coche actual es menor o igual que rhs, false en caso contrario.
     * @note Realiza la comparación por matrícula
     */
    bool operator<=(const Coche &rhs) const;

    /**
     * @brief Sobrecarga del operador mayor o igual que.
     * @param rhs Coche con el que se compara.
     * @return True si el coche actual es mayor o igual que rhs, false en caso contrario.
     * @note Realiza la comparación por matrícula
     */
    bool operator>=(const Coche &rhs) const;

    /**
     * @brief Sobrecarga del operador de inserción en flujo.
     *
     * Permite que la información del coche sea enviada a un flujo de salida cout.
     *
     * @param os Flujo de salida.
     * @param coche Coche a mostrar.
     * @return Referencia al flujo de salida.
     */
    friend std::ostream &operator<<(std::ostream &os, const Coche &coche);
};

#endif //PR3AVL_COCHE_H
