/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file PuntoRecarga.h
 * @brief Declaración de la clase PuntoRecarga
 */
#ifndef PR3AVL_PUNTORECARGA_H
#define PR3AVL_PUNTORECARGA_H

#include "VDinamico.h"
#include "Coche.h"

/**
 * @brief Declaración anticipada de la clase Coche
 */
class Coche;

/**
 * @struct Coordenadas
 * @brief Representa una posición en el plano cartesiano.
 *
 * Contiene las coordenadas `x` e `y` de un punto, que se utilizan para definir la ubicación de un PuntoRecarga.
 */
struct Coordenadas {
    float x; ///< Coordenada x del punto.
    float y; ///< Coordenada y del punto.

    /**
     * @brief Constructor por defecto de Coordenadas, inicializa `x` y `y` a 0.
     */
    Coordenadas() : x(0), y(0) {};

    /**
     * @brief Constructor parametrizado de Coordenadas.
     * @param x_ Valor de la coordenada x.
     * @param y_ Valor de la coordenada y.
     */
    Coordenadas(float x_, float y_) : x(x_), y(y_) {};
};

/**
 * @class PuntoRecarga
 * @brief Clase que representa un punto de recarga de coches eléctricos.
 *
 * Almacena los coches conectados, su capacidad máxima y su posición en el espacio. Permite añadir y eliminar coches,
 * y proporciona métodos para obtener el coche con mayor batería o la lista de coches conectados.
 */
class PuntoRecarga {

private:

    unsigned int id = 0; ///< Identificador único del punto de recarga.
    unsigned int max = 0; ///< Capacidad máxima de coches en el punto de recarga.
    Coordenadas posicion; ///< Posición geográfica del punto de recarga.
    VDinamico<Coche *> coches; ///< Lista dinámica de punteros a coches actualmente en el punto de recarga.

public:

    /**
     * @brief Constructor por defecto de PuntoRecarga.
     */
    PuntoRecarga() = default;

    /**
    * @brief Constructor completo de PuntoRecarga.
    *
    * @param id_ Identificador único del punto de recarga.
    * @param posicion_ Posición geográfica del punto de recarga.
    * @param max_ Capacidad máxima del punto de recarga.
    */
    PuntoRecarga(int id_, const Coordenadas &posicion_, unsigned int max_);

    /**
     * @brief Constructor de PuntoRecarga con solo el identificador.
     *
     * @param id_ Identificador único del punto de recarga.
     */
    explicit PuntoRecarga(int id_);

    /**
     * @brief Destructor por defecto de PuntoRecarga.
     */
    ~PuntoRecarga() = default;

    /**
     * @brief Obtiene el identificador del punto de recarga.
     * @return El identificador único del punto de recarga.
     */
    [[nodiscard]] unsigned int getId() const;

    /**
     * @brief Establece el identificador del punto de recarga.
     * @param id_ Nuevo identificador del punto de recarga.
     */
    void setId(unsigned int id_);

    /**
     * @brief Obtiene la capacidad máxima de coches en el punto de recarga.
     * @return Capacidad máxima de coches.
     */
    [[nodiscard]] unsigned int getMax() const;

    /**
     * @brief Establece la capacidad máxima de coches.
     * @param max_ Nueva capacidad máxima de coches.
     */
    void setMax(unsigned int max_);

    /**
     * @brief Obtiene la posición del punto de recarga.
     * @return Referencia constante a la estructura Coordenadas que indica la posición.
     */
    [[nodiscard]] const Coordenadas &getPosicion() const;

    /**
     * @brief Establece la posición del punto de recarga.
     * @param posicion_ Nueva posición geográfica del punto de recarga.
     */
    void setPosicion(const Coordenadas &posicion_);

    /**
     * @brief Obtiene el coche con mayor nivel de batería.
     *
     * Recorre la lista de coches conectados al punto de recarga y devuelve el coche con la batería más alta.
     *
     * @return Puntero al coche con la mayor batería, o nullptr si no hay coches.
     */
    Coche *getMaxBateria();

    /**
     * @brief Añade un coche al punto de recarga.
     *
     * Si la capacidad máxima no se ha alcanzado, añade el coche al punto de recarga.
     *
     * @param coche Coche a añadir.
     * @return `true` si el coche fue añadido exitosamente, `false` si el punto de recarga está lleno.
     */
    bool addCoche(Coche &coche);

    /**
     * @brief Elimina un coche del punto de recarga.
     *
     * Elimina el coche especificado de la lista de coches conectados, si está presente.
     *
     * @param coche Coche a eliminar del punto de recarga.
     */
    void borrarCoche(Coche &coche);

    /**
     * @brief Obtiene la lista de coches conectados al punto de recarga.
     * @return Una referencia constante a un VDinamico de punteros a coches.
     */
    [[nodiscard]] const VDinamico<Coche *> &getCoches() const;

    /**
     * @brief Establece la lista de coches en el punto de recarga.
     *
     * Asigna una nueva lista de coches conectados al punto de recarga.
     *
     * @param coches_ Nueva lista de coches.
     */
    void setCoches(const VDinamico<Coche *> &coches_);

    /**
     * @brief Constructor alternativo de PuntoRecarga con posición.
     *
     * Inicializa un punto de recarga con un identificador y una posición en coordenadas.
     *
     * @param i Identificador único del punto de recarga.
     * @param coordenadas Coordenadas de la posición del punto de recarga.
     */
    PuntoRecarga(int i, Coordenadas coordenadas);
};


#endif //PR3AVL_PUNTORECARGA_H
