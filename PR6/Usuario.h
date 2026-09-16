/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Usuario.h
 * @brief Declaración de la clase Usuario
 */

#ifndef PR6_USUARIO_H
#define PR6_USUARIO_H

#include <iostream>
#include <map>
#include <list>
#include "Reanelcar.h"

class Reanelcar;

/**
 * @class Usuario
 * @brief Clase que representa un usuario en el sistema Reanelcar.
 *
 * La clase Usuario incluye atributos básicos del usuario como nif, clave, nombre y dirección,
 * además de un puntero al coche alquilado y un vínculo al sistema Reanelcar.
 */
class Usuario {

private:

    std::string nif; ///< NIF del usuario.
    std::string clave; ///< Clave de acceso del usuario.
    std::string nombre; ///< Nombre completo del usuario.
    std::string direccion; ///< Dirección de residencia del usuario.
    Coche *cochealquilado{}; ///< Puntero al coche alquilado por el usuario.
    Reanelcar *linkReanelcar_{}; ///< Puntero al sistema Reanelcar asociado al usuario.
    std::multimap<Fecha, Trayecto *> trayectos; ///< Lista de trayectos realizados por el usuario, ordenados por fecha.
    int puntos = 100; ///< Puntos de usuario a tener  en cuenta para el alquiler de coches.

public:
    /**
     * @brief Constructor de Usuario con nombre y NIF.
     * @param nombre_ Nombre completo del usuario.
     * @param nif_ NIF del usuario.
     */
    Usuario(std::string &nombre_, std::string &nif_);

    /**
     * @brief Constructor de Usuario con todos los atributos.
     * @param nif_ NIF del usuario.
     * @param clave_ Clave de acceso del usuario.
     * @param nombre_ Nombre completo del usuario.
     * @param direccion Dirección de residencia del usuario.
     * @param link_ Puntero al sistema Reanelcar asociado al usuario.
     */
    Usuario(std::string &nif_, std::string &clave_, std::string &nombre_, std::string &direccion, Reanelcar *link_);

    /**
     * @brief Constructor por defecto de Usuario.
     */
    Usuario() = default;

    /**
     * @brief Constructor de Usuario que inicializa todos los atributos personales.
     * @param nif_ NIF del usuario.
     * @param clave_ Clave de acceso del usuario.
     * @param nombre_ Nombre completo del usuario.
     * @param direccion Dirección del usuario.
     */
    Usuario(std::string &nif_, std::string &clave_, std::string &nombre_, std::string &direccion);

    /**
     * @brief Destructor por defecto de Usuario.
     */
    ~Usuario() = default;

    /**
     * @brief Obtiene el NIF del usuario.
     * @return Referencia constante al NIF.
     */
    [[nodiscard]]  std::string &getNif();

    /**
     * @brief Establece el NIF del usuario.
     * @param nif Nuevo NIF del usuario.
     */
    void setNif(std::string &nif);

    /**
     * @brief Obtiene la clave de acceso del usuario.
     * @return Referencia constante a la clave de acceso.
     */
    [[nodiscard]]  std::string &getClave();

    /**
     * @brief Establece la clave de acceso del usuario.
     * @param clave Nueva clave de acceso del usuario.
     */
    void setClave(std::string &clave);

    /**
     * @brief Obtiene el nombre del usuario.
     * @return Referencia constante al nombre del usuario.
     */
    [[nodiscard]]  std::string &getNombre();

    /**
     * @brief Establece el nombre del usuario.
     * @param nombre Nuevo nombre del usuario.
     */
    void setNombre(std::string &nombre);

    /**
     * @brief Obtiene la dirección del usuario.
     * @return Referencia constante a la dirección del usuario.
     */
    [[nodiscard]]  std::string &getDireccion();

    /**
     * @brief Establece la dirección del usuario.
     * @param direccion Nueva dirección del usuario.
     */
    void setDireccion(std::string &direccion);

    /**
     * @brief Obtiene el coche alquilado por el usuario.
     * @return Puntero al coche alquilado o nullptr si no tiene ningún coche alquilado.
     */
    [[nodiscard]] Coche *getCochealquilado();

    /**
     * @brief Establece el coche alquilado por el usuario.
     * @param cochealquilado Puntero al coche que será alquilado por el usuario.
     */
    void setCochealquilado(Coche *cochealquilado);

    /**
     * @brief Obtiene el enlace al sistema Reanelcar.
     * @return Puntero al sistema Reanelcar al que está vinculado el usuario.
     */
    [[nodiscard]] Reanelcar *getLinkReanelcar();

    /**
     * @brief Establece el enlace al sistema Reanelcar.
     * @param linkReanelcar Puntero al sistema Reanelcar que se asociará al usuario.
     */
    void setLinkReanelcar(Reanelcar *linkReanelcar);

    /**
     * @brief Alquila un coche disponible para el usuario desde el sistema Reanelcar.
     *
     * Este método busca un coche disponible en el sistema Reanelcar y lo asigna como coche alquilado al usuario.
     *
     * @param idprorigen Identificador del punto de recarga de origen.
     * @param idprdes Identificador del punto de recarga de destino.
     * @param fini Fecha de inicio del alquiler.
     *
     * @return Puntero al coche alquilado o `nullptr` si no hay coches disponibles.
     */
    Coche *cogecoche(int idprorigen, int idprdes, Fecha &fini);

    /**
     * @brief Crea un trayecto entre dos puntos de recarga.
     *
     * Este método crea un trayecto con los puntos de recarga proporcionados y la fecha de inicio.
     *
     * @param origin Punto de recarga de origen.
     * @param destination Punto de recarga de destino.
     * @param fechaInicio Fecha de inicio del trayecto.
     *
     * @return Puntero al trayecto creado.
     */
    Trayecto *crearTrayecto(PuntoRecarga *origin, PuntoRecarga *destination, Fecha &fechaInicio);

    /**
     * @brief Inicia un trayecto entre el punto de recarga de origen y el destino especificado.
     *
     * Este método comienza el trayecto desde un punto de recarga de origen y lo dirige a un punto de recarga de destino.
     *
     * @param origin Punto de recarga de origen.
     * @param destino Identificador del punto de recarga de destino.
     *
     * @return Puntero al coche utilizado para el trayecto.
     */
    Coche *iniciarTrayecto(PuntoRecarga *origin, int destino);

    /**
     * @brief Aparca el coche en el punto de recarga de destino.
     *
     * Este método finaliza el trayecto y aparca el coche en el punto de recarga de destino.
     *
     * @param destination Punto de recarga de destino donde se aparca el coche.
     */
    void aparcaCoche(Coche *coche, PuntoRecarga *destination, PuntoRecarga *destinoEsperado);

    /**
     * @brief Obtiene la lista de trayectos realizados en una fecha específica.
     *
     * Este método devuelve los trayectos realizados en la fecha proporcionada.
     *
     * @param fecha Fecha en la que se buscan los trayectos.
     *
     * @return Lista de punteros a trayectos realizados en la fecha indicada.
     */
    std::list<Trayecto *> getTrayectosFecha(Fecha &fecha);

    /**
    * @brief Obtiene todos los trayectos del usuario.
    *
    * Este método devuelve todos los trayectos realizados por el usuario, ordenados por fecha.
    *
    * @return Multimap de trayectos, ordenados por fecha.
    */
    std::multimap<Fecha, Trayecto *> getTrayectos();

    /**
    * @brief Establece la lista de trayectos del usuario.
    *
    * Este método asigna una nueva lista de trayectos al usuario.
    *
    * @param trayectos Nueva lista de trayectos a asignar.
    */
    void setTrayectos(std::multimap<Fecha, Trayecto *> &trayectos);

    /**
     * @brief Obtiene el último trayecto realizado por el usuario.
     *
     * Este método devuelve el último trayecto que el usuario ha realizado, basado en la fecha.
     *
     * @return Puntero al último trayecto realizado.
     */
    Trayecto *getUltimoTrayecto();

    /**
    * @brief Elimina todos los trayectos realizados por el usuario.
    */
    void eliminarTrayectos();

    /**
     * @brief Decrementa los puntos del usuario.
     *
     * Este método decrementa los puntos del usuario basándose en un retraso.
     *
     * @param retraso Cantidad de puntos a descontar según el retraso.
     */
    void decrementarPuntos(int retraso);

    /**
     * @brief Muestra los trayectos realizados por el usuario con un retraso.
     *
     * Este método muestra los trayectos con un retraso específico.
     */
    void mostrarTrayectosConRetraso();

    /**
     * @brief Decrementa los puntos del usuario en función de los kilómetros que disten entre el usuario
     * y el punto
     * @param distanciaKm la distancia a la que se encuentra aparcado del punto de recarga
     */
    void decrementarPuntosPorDistancia(float distanciaKm);

    /**
     * getter de los puntos del usuario
     * @return puntos del usuario
     */
    int getPuntos() const;

    /**
     * setter de los puntos del usuario
     * @param puntos los puntos a asignar
     */
    void setPuntos(int puntos);
};

#endif //PR6_USUARIO_H