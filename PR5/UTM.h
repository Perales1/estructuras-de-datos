/**
 * @author David Fernández Espejo, dfe00004@red.ujaen.es
 * @author David Lorente Wagner, dlw00001@red.ujaen.es
 * @file UTM.h
 * @brief Archivo de declaración e implementación de la clase UTM
 */
#ifndef PR5_UTM_H
#define PR5_UTM_H

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
    UTM() : lat(0), lon(0) {}


    /**
     * @brief Constructor que inicializa las coordenadas UTM.
     *
     * @param lat_ Latitud del punto en grados decimales.
     * @param lon_ Longitud del punto en grados decimales.
     */
    UTM(float lat_, float lon_) : lat(lat_), lon(lon_) {}

    /**
     * @brief Obtiene la latitud del punto UTM.
     *
     * @return La latitud en grados decimales.
     */
    float getLat() {
        return lat;
    }

    /**
     * @brief Establece la latitud del punto UTM.
     *
     * @param lat Nueva latitud en grados decimales.
     */
    void setLat(float lat) {
        UTM::lat = lat;
    }

    /**
     * @brief Obtiene la longitud del punto UTM.
     *
     * @return La longitud en grados decimales.
     */
    float getLon() {
        return lon;
    }

    /**
     * @brief Establece la longitud del punto UTM.
     *
     * @param lon Nueva longitud en grados decimales.
     */
    void setLon(float lon) {
        UTM::lon = lon;
    }
};

#endif //PR5_UTM_H
