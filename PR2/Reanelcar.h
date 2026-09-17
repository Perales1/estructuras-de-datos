/**
 * @author David Fernández Espejo dfe00004@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Usuario.h
 * @brief Declaración de la clase Reanelcar.
 *
 * La clase Reanelcar gestiona la información de coches y usuarios
 * en un sistema de alquiler de coches. Proporciona métodos para
 * buscar usuarios y coches, así como para gestionar el alquiler de coches.
 */

#ifndef LISTADENLAZADA3_REANELCAR_H
#define LISTADENLAZADA3_REANELCAR_H

#include <string>
#include <stdexcept>
#include "Usuario.h"
#include "Coche.h"
#include "VDinamico.h"
#include "ListaDEnlazada.h"

/**
 * @class Reanelcar
 * @brief Clase que representa un sistema de alquiler de coches.
 */
class Reanelcar {
public:
    VDinamico<Coche> coches; ///< Almacena los coches disponibles para alquiler.
    ListaDEnlazada<Usuario> usuarios; ///< Almacena los usuarios del sistema.

public:
    /**
     * @brief Busca un usuario por su NIF.
     *
     * @param nif El NIF del usuario a buscar.
     * @return Puntero al usuario encontrado, o nullptr si no se encuentra.
     */
    Usuario *buscarUsuarioPorNif(const std::string &nif);

    /**
     * @brief Busca usuarios por su nombre.
     *
     * @param nombre El nombre del usuario a buscar.
     * @return Lista de usuarios que coinciden con el nombre proporcionado.
     */
    ListaDEnlazada<Usuario> buscarUsuarioPorNombre(const std::string &nombre);

    /**
     * @brief Busca un coche por su matrícula.
     *
     * @param matricula La matrícula del coche a buscar.
     * @return Puntero al coche encontrado, o nullptr si no se encuentra.
     */
    Coche *buscarCochePorMatricula(const std::string &matricula);

    /**
     * @brief Busca coches por su modelo.
     *
     * @param modelo El modelo del coche a buscar.
     * @return Puntero a un objeto VDinamico que contiene los coches encontrados.
     */
    VDinamico<Coche> *buscarCochePorModelo(const std::string &modelo);

    /**
     * @brief Alquila un coche a un usuario.
     *
     * @param nif El NIF del usuario que alquila el coche.
     * @param matricula La matrícula del coche a alquilar.
     */
    void alquilar(const std::string &nif, const std::string &matricula);
};

#endif //LISTADENLAZADA3_REANELCAR_H
