/**
 * @author David Fernández Espejo, dfe00004@red.ujaen.es
 * @author David Lorente Wagner, dlw00001@red.ujaen.es
 * @file UTM.h
 * @brief Archivo de declaración de la clase UTM
 */
#ifndef PR6_UTM_H
#define PR6_UTM_H

/**
 * @class UTM
 * @brief Clase que representa un punto geográfico en coordenadas UTM (Universal Transverse Mercator).
 *
 * Esta clase almacena las coordenadas geográficas de un punto utilizando el sistema de coordenadas UTM.
 * Las coordenadas se representan mediante la latitud y longitud en grados decimales.
 */
class UTM {
private:
    float lat; ///< Latitud del punto en grados decimales.
    float lon; ///< Longitud del punto en grados decimales.

public:

    /**
    * @brief Constructor por defecto de la clase UTM.
    *
    * Inicializa las coordenadas `lat` y `lon` a 0.
    */
    UTM();


    /**
     * @brief Constructor que inicializa las coordenadas UTM.
     *
     * @param lat_ Latitud del punto en grados decimales.
     * @param lon_ Longitud del punto en grados decimales.
     */
    UTM(float lat_, float lon_);

    /**
     * @brief Obtiene la latitud del punto UTM.
     *
     * @return La latitud en grados decimales.
     */
    float getLat();

    /**
     * @brief Establece la latitud del punto UTM.
     *
     * @param lat Nueva latitud en grados decimales.
     */
    void setLat(float lat_);


    /**
     * @brief Obtiene la longitud del punto UTM.
     *
     * @return La longitud en grados decimales.
     */
    float getLon();

    /**
     * @brief Establece la longitud del punto UTM.
     *
     * @param lon_ Nueva longitud en grados decimales.
     */
    void setLon(float lon_);

    /**
   * @brief Sobrecarga del operador de igualdad (==).
   *
   * Compara dos objetos de la clase UTM para determinar si representan el mismo punto.
   *
   * @param otro El objeto UTM con el que se compara.
   * @return `true` si las coordenadas (latitud y longitud) de ambos objetos son iguales, `false` en caso contrario.
   */
    bool operator==(const UTM &otro) const;

    /**
     * @brief Sobrecarga del operador de desigualdad (!=).
     *
     * Compara dos objetos de la clase UTM para determinar si representan puntos diferentes.
     *
     * @param otro El objeto UTM con el que se compara.
     * @return `true` si las coordenadas (latitud y longitud) de ambos objetos son diferentes, `false` en caso contrario.
     */
    bool operator!=(const UTM &otro) const;
};

#endif //PR6_UTM_H
