/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Usuario.h
 * @brief Declaración de la clase Usuario.
 *
 * La clase Usuario representa a un usuario del sistema de alquiler de coches.
 * Almacena información personal y la relación del usuario con un coche alquilado.
 */

#ifndef LISTADENLAZADA3_USUARIO_H
#define LISTADENLAZADA3_USUARIO_H

#include <string>
#include "Coche.h"

/**
 * @class Usuario
 * @brief Clase que representa a un usuario del sistema.
 */
class Usuario {
private:
    std::string nif;  ///< NIF del usuario.
    std::string clave; ///< Clave del usuario.
    std::string nombre; ///< Nombre del usuario.
    std::string direccion; ///< Dirección del usuario.
    Coche* cocheAlquilado; ///< Puntero al coche alquilado por el usuario (puede ser nullptr si no ha alquilado uno).

public:
    /**
     * @brief Constructor de la clase Usuario.
     *
     * @param nif El NIF del usuario.
     * @param clave La clave del usuario.
     * @param nombre El nombre del usuario.
     * @param direccion La dirección del usuario.
     */
    Usuario(const std::string& nif, const std::string& clave, const std::string& nombre, const std::string &direccion);

    /**
     * @brief Obtiene el NIF del usuario.
     *
     * @return El NIF del usuario.
     */
    const std::string &getNif() const;

    /**
     * @brief Establece el NIF del usuario.
     *
     * @param nif El nuevo NIF del usuario.
     */
    void setNif(const std::string &nif);

    /**
     * @brief Obtiene la clave del usuario.
     *
     * @return La clave del usuario.
     */
    const std::string &getClave() const;

    /**
     * @brief Establece la clave del usuario.
     *
     * @param clave La nueva clave del usuario.
     */
    void setClave(const std::string &clave);

    /**
     * @brief Obtiene el nombre del usuario.
     *
     * @return El nombre del usuario.
     */
    const std::string &getNombre() const;

    /**
     * @brief Establece el nombre del usuario.
     *
     * @param nombre El nuevo nombre del usuario.
     */
    void setNombre(const std::string &nombre);

    /**
     * @brief Obtiene la dirección del usuario.
     *
     * @return La dirección del usuario.
     */
    const std::string &getDireccion() const;

    /**
     * @brief Establece la dirección del usuario.
     *
     * @param direccion La nueva dirección del usuario.
     */
    void setDireccion(const std::string &direccion);

    /**
     * @brief Obtiene el coche alquilado por el usuario.
     *
     * @return Puntero al coche alquilado, o nullptr si no ha alquilado uno.
     */
    Coche *getCocheAlquilado() const;

    /**
     * @brief Establece el coche alquilado por el usuario.
     *
     * @param cocheAlquilado Puntero al coche que se desea asignar como alquilado.
     */
    void setCocheAlquilado(Coche *cocheAlquilado);
};

#endif //LISTADENLAZADA3_USUARIO_H
