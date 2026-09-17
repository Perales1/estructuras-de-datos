/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaeb.es
 * @file Trayecto.h
 * @brief Declaración de la clase Trayecto
 */
#ifndef PR4STL_TRAYECTO_H
#define PR4STL_TRAYECTO_H

#include "PuntoRecarga.h"
#include "Coche.h"
#include "fecha.h"

/**
 * @class Trayecto
 * @brief Clase que representa un trayecto realizado entre dos puntos de recarga.
 *
 * Un trayecto tiene un identificador único, un coche involucrado, una fecha de inicio y fin, y dos puntos de recarga:
 * el origen y el destino. El trayecto permite registrar cuándo comenzó y terminó un viaje entre los puntos de recarga.
 */
class Trayecto {
private:
    static int contadorTrayectos; ///< Contador estático para generar identificadores únicos de trayectos.
    int idTrayecto; ///< Identificador único del trayecto.
    PuntoRecarga *origin; ///< Punto de recarga de origen.
    PuntoRecarga *destination; ///< Punto de recarga de destino.
    Coche *inthecar; ///< Coche involucrado en el trayecto.
    Fecha fechainicio; ///< Fecha y hora de inicio del trayecto.
    Fecha fechafin; ///< Fecha y hora de finalización del trayecto.

public:

    /**
     * @brief Constructor de un trayecto.
     *
     * Inicializa un trayecto con el punto de recarga de origen, el destino, el coche que realiza el trayecto y la fecha de inicio.
     *
     * @param origin_ Puntero al punto de recarga de origen.
     * @param destination_ Puntero al punto de recarga de destino.
     * @param inthecar_ Puntero al coche que realiza el trayecto.
     * @param fechainicio_ Fecha de inicio del trayecto.
     */
    Trayecto(PuntoRecarga *origin_, PuntoRecarga *destination_, Coche *inthecar_, Fecha &fechainicio_);

    /**
     * @brief Obtiene el identificador único del trayecto.
     *
     * Este método devuelve el identificador único del trayecto, que es generado automáticamente durante la creación del objeto.
     *
     * @return El identificador único del trayecto.
     */
    [[nodiscard]] int getidTrayecto();

    /**
     * @brief Obtiene el punto de recarga de origen.
     *
     * Este método devuelve el puntero al punto de recarga de origen del trayecto.
     *
     * @return Puntero al punto de recarga de origen.
     */
    [[nodiscard]] PuntoRecarga *getOrigin();

    /**
     * @brief Obtiene el punto de recarga de destino.
     *
     * Este método devuelve el puntero al punto de recarga de destino del trayecto.
     *
     * @return Puntero al punto de recarga de destino.
     */
    [[nodiscard]] PuntoRecarga *getDestination();

    /**
    * @brief Obtiene el coche involucrado en el trayecto.
    *
    * Este método devuelve el puntero al coche que está realizando el trayecto.
    *
    * @return Puntero al coche que realiza el trayecto.
    */
    [[nodiscard]] Coche *getinthecar();

    /**
     * @brief Obtiene la fecha de inicio del trayecto.
     *
     * Este método devuelve la fecha en que comenzó el trayecto.
     *
     * @return Referencia constante a la fecha de inicio del trayecto.
     */
    [[nodiscard]]  Fecha &getfechaInicio();

    /**
    * @brief Obtiene la fecha de finalización del trayecto.
    *
    * Este método devuelve la fecha en que terminó el trayecto. Si el trayecto no ha finalizado, la fecha será una fecha vacía.
    *
    * @return Referencia constante a la fecha de finalización del trayecto.
    */
    [[nodiscard]]  Fecha &getfechaFin();

    /**
     * @brief Finaliza el trayecto.
     *
     * Este método establece la fecha de finalización del trayecto, indicando que el trayecto ha sido completado.
     *
     * @param fechaFin Fecha de finalización del trayecto.
     */
    void finalizarTrayecto(Fecha &fechaFin); // Método para terminar el trayecto
};


#endif //PR4STL_TRAYECTO_H
