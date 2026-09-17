/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Usuario.h
 * @brief Implementación de la clase Usuario
 */
#ifndef PR3AVL_USUARIO_H
#define PR3AVL_USUARIO_H

#include <iostream>
#include "Coche.h"
#include "Reanelcar.h"

/**
 * @brief Declaración adelantada de la clase Reanelcar
 */
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
    Coche *cochealquilado; ///< Puntero al coche alquilado por el usuario.
    Reanelcar *linkReanelcar; ///< Puntero al sistema Reanelcar asociado al usuario.

public:

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
    [[nodiscard]] const std::string &getNif() const;

    /**
     * @brief Establece el NIF del usuario.
     * @param nif Nuevo NIF del usuario.
     */
    void setNif(const std::string &nif);

    /**
     * @brief Obtiene la clave de acceso del usuario.
     * @return Referencia constante a la clave de acceso.
     */
    [[nodiscard]] const std::string &getClave() const;

    /**
     * @brief Establece la clave de acceso del usuario.
     * @param clave Nueva clave de acceso del usuario.
     */
    void setClave(const std::string &clave);

    /**
     * @brief Obtiene el nombre del usuario.
     * @return Referencia constante al nombre del usuario.
     */
    [[nodiscard]] const std::string &getNombre() const;

    /**
     * @brief Establece el nombre del usuario.
     * @param nombre Nuevo nombre del usuario.
     */
    void setNombre(const std::string &nombre);

    /**
     * @brief Obtiene la dirección del usuario.
     * @return Referencia constante a la dirección del usuario.
     */
    [[nodiscard]] const std::string &getDireccion() const;

    /**
     * @brief Establece la dirección del usuario.
     * @param direccion Nueva dirección del usuario.
     */
    void setDireccion(const std::string &direccion);

    /**
     * @brief Obtiene el coche alquilado por el usuario.
     * @return Puntero al coche alquilado o nullptr si no tiene ningún coche alquilado.
     */
    [[nodiscard]] Coche *getCochealquilado() const;

    /**
     * @brief Establece el coche alquilado por el usuario.
     * @param cochealquilado Puntero al coche que será alquilado por el usuario.
     */
    void setCochealquilado(Coche *cochealquilado);

    /**
     * @brief Obtiene el enlace al sistema Reanelcar.
     * @return Puntero al sistema Reanelcar al que está vinculado el usuario.
     */
    [[nodiscard]] Reanelcar *getLinkReanelcar() const;

    /**
     * @brief Establece el enlace al sistema Reanelcar.
     * @param linkReanelcar Puntero al sistema Reanelcar que se asociará al usuario.
     */
    void setLinkReanelcar(Reanelcar *linkReanelcar);

    /**
     * @brief Alquila un coche disponible para el usuario desde el sistema Reanelcar.
     *
     * Busca un coche en el sistema Reanelcar y lo asigna como coche alquilado del usuario.
     *
     * @return Puntero al coche alquilado o nullptr si no hay coches disponibles.
     */
    Coche *cogecoche();
};


#endif //PR3AVL_USUARIO_H