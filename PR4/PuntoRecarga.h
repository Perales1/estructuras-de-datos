/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file PuntoRecarga.h
 * @brief Declaración de la clase PuntoRecarga
 */
#ifndef PR4STL_PUNTORECARGA_H
#define PR4STL_PUNTORECARGA_H

#include <map>
#include "Coche.h"
#include "UTM.h"

/**
 * @brief Declaración anticipada de la clase Coche
 */
class Coche;

/**
 * @class PuntoRecarga
 * @brief Clase que representa un punto de recarga de coches eléctricos.
 *
 * La clase PuntoRecarga gestiona los coches conectados a un punto de recarga, su capacidad máxima y su posición en el espacio.
 * Permite añadir y eliminar coches, y proporciona métodos para obtener el coche con mayor batería o la lista de coches conectados.
 */
class PuntoRecarga {

private:

    unsigned int id = 0; ///< Identificador único del punto de recarga.
    unsigned int max = 0; ///< Capacidad máxima de coches en el punto de recarga.
    UTM posicion; ///< Posición geográfica del punto de recarga.
    std::multimap<float, Coche *> coches; ///< Lista dinámica de punteros a coches actualmente en el punto de recarga.

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
    PuntoRecarga(int id_, UTM &posicion_, unsigned int max_);

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
    [[nodiscard]] unsigned int getId();

    /**
     * @brief Establece el identificador del punto de recarga.
     * @param id_ Nuevo identificador del punto de recarga.
     */
    void setId(unsigned int id_);

    /**
     * @brief Obtiene la capacidad máxima de coches en el punto de recarga.
     * @return Capacidad máxima de coches.
     */
    [[nodiscard]] unsigned int getMax();

    /**
     * @brief Establece la capacidad máxima de coches.
     * @param max_ Nueva capacidad máxima de coches.
     */
    void setMax(unsigned int max_);

    /**
     * @brief Obtiene la posición del punto de recarga.
     * @return Referencia constante a la estructura Coordenadas que indica la posición.
     */
    [[nodiscard]]  UTM &getPosicion();

    /**
     * @brief Establece la posición del punto de recarga.
     * @param posicion_ Nueva posición geográfica del punto de recarga.
     */
    void setPosicion(UTM &posicion_);

    /**
     * @brief Obtiene el coche con mayor nivel de batería conectado al punto de recarga.
     *
     * Este método recorre la lista de coches conectados al punto de recarga y devuelve el puntero al coche con la batería más alta.
     * Si no hay coches conectados, devuelve nullptr.
     *
     * @return Puntero al coche con el mayor nivel de batería, o nullptr si no hay coches conectados.
     */
    Coche *getMaxBateria();

    /**
     * @brief Añade un coche al punto de recarga.
     *
     * Si la capacidad máxima no se ha alcanzado, añade el coche al punto de recarga. Si el punto de recarga está lleno,
     * no se añade el coche y se devuelve false.
     *
     * @param coche Coche a añadir al punto de recarga.
     * @return `true` si el coche fue añadido exitosamente, `false` si el punto de recarga está lleno.
     */
    bool addCoche(Coche *coche);

    /**
     * @brief Elimina un coche del punto de recarga.
     *
     * Este método elimina el coche especificado de la lista de coches conectados, si está presente.
     *
     * @param coche Coche a eliminar del punto de recarga.
     */
    void borrarCoche(Coche *coche);

    /**
     * @brief Obtiene la lista de coches conectados al punto de recarga.
     *
     * Este método devuelve una referencia constante a la lista de coches conectados al punto de recarga.
     *
     * @return Una referencia constante a un `std::multimap<float, Coche *>` que contiene los coches conectados.
     */
    [[nodiscard]]  std::multimap<float, Coche *> &getCoches();

    /**
     * @brief Establece la lista de coches conectados al punto de recarga.
     *
     * Este método asigna una nueva lista de coches conectados al punto de recarga.
     *
     * @param coches_ Nueva lista de coches a conectar al punto de recarga.
     */
    void setCoches(std::multimap<float, Coche *> &coches_);

    /**
     * @brief Constructor alternativo de PuntoRecarga con posición.
     *
     * Inicializa un punto de recarga con un identificador y una posición en coordenadas.
     *
     * @param i Identificador único del punto de recarga.
     * @param coordenadas Coordenadas de la posición del punto de recarga.
     */
    PuntoRecarga(int i, UTM coordenadas);

    /**
     * @brief Obtiene el número de coches conectados al punto de recarga.
     *
     * Este método devuelve la cantidad de coches actualmente conectados al punto de recarga.
     *
     * @return Número de coches conectados al punto de recarga.
     */
    int getNumCoches();

};


#endif //PR4STL_PUNTORECARGA_H
