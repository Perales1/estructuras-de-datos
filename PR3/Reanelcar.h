/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Reanelcar.h
 * @brief Declaración de la clase Reanelcar
 */
#ifndef PR3AVL_REANELCAR_H
#define PR3AVL_REANELCAR_H

#include <iostream>
#include "ListaDEnlazada.h"
#include "AVL.h"
#include "Usuario.h"
#include "PuntoRecarga.h"

/**
 * @brief Declaración adelantada de la clase Usuario
 */
class Usuario;

/**
 * @class Reanelcar
 * @brief Clase que representa el sistema de gestión de coches eléctricos y usuarios.
 *
 * La clase permite gestionar coches en un árbol AVL, una lista de usuarios y un punto de recarga.
 * Facilita el alquiler de coches, la asignación de coches al punto de recarga, y la búsqueda de coches y usuarios.
 */
class Reanelcar {
private:

    AVL<Coche> coches; ///< Árbol AVL de coches disponibles.
    ListaDEnlazada<Usuario> usuarios; ///< Lista doblemente enlazada de usuarios registrados.
    PuntoRecarga puntoRecarga; ///< Punto de recarga para coches eléctricos.

public:

    /**
    * @brief Constructor por defecto de Reanelcar.
    */
    Reanelcar();

    /**
     * @brief Destructor virtual de Reanelcar.
     */
    virtual ~Reanelcar();

    /**
     * @brief Constructor de Reanelcar que inicializa con un conjunto de coches.
     * @param coches AVL que contiene los coches a añadir al sistema.
     */
    explicit Reanelcar(const AVL<Coche> &coches);

    /**
    * @brief Constructor de Reanelcar que inicializa con un conjunto de coches y usuarios.
    * @param coches AVL que contiene los coches.
    * @param usuarios Lista doblemente enlazada de usuarios.
    */
    Reanelcar(const AVL<Coche> &coches, const ListaDEnlazada<Usuario> &usuarios);

    /**
     * @brief Constructor de Reanelcar que inicializa con coches, usuarios y un punto de recarga.
     * @param coches AVL que contiene los coches.
     * @param usuarios Lista doblemente enlazada de usuarios.
     * @param puntoRecarga Punto de recarga de coches eléctricos.
     */
    Reanelcar(const AVL<Coche> &coches, const ListaDEnlazada<Usuario> &usuarios, const PuntoRecarga &puntoRecarga);

    /**
     * @brief Alquila un coche del sistema.
     *
     * Devuelve un puntero al coche disponible con mayor nivel de batería y lo marca como alquilado.
     *
     * @return Puntero al coche con mayor batería, o nullptr si no hay coches disponibles.
     */
    Coche *alquila();

    /**
     * @brief Coloca un coche en el punto de recarga.
     *
     * Añade un coche al punto de recarga asociado, si hay capacidad disponible.
     *
     * @param coche_ Coche a colocar en el punto de recarga.
     */
    void colocarCochePR(Coche &coche_);

    /**
     * @brief Busca usuarios por su nombre.
     *
     * Devuelve una lista de usuarios cuyo nombre coincide con el parámetro de búsqueda.
     *
     * @param nombre Nombre del usuario a buscar.
     * @return Lista de usuarios con el nombre especificado.
     */
    ListaDEnlazada<Usuario> buscarUsuarioPorNombre(const std::string &nombre);

    /**
     * @brief Busca un coche por su matrícula.
     *
     * Recorre el AVL de coches para encontrar un coche con la matrícula especificada.
     *
     * @param matricula Matrícula del coche a buscar.
     * @return Puntero al coche encontrado o nullptr si no existe.
     */
    Coche *buscarCochePorMatricula(const std::string &matricula);

    /**
     * @brief Busca un usuario por su NIF.
     *
     * Recorre la lista de usuarios para encontrar un usuario con el NIF especificado.
     *
     * @param nif NIF del usuario a buscar.
     * @return Puntero al usuario encontrado o nullptr si no existe.
     */
    Usuario *buscarUsuarioPorNif(const std::string &nif);

    /**
     * @brief Obtiene el AVL de coches del sistema.
     * @return El AVL de coches disponibles.
     */
    AVL<Coche> getCoches();

    /**
     * @brief Inserta un usuario en el sistema.
     *
     * Añade un usuario a la lista de usuarios.
     *
     * @param usuario Usuario a añadir.
     */
    void insertausuario(Usuario &usuario);

    /**
     * @brief Inserta un coche en el sistema.
     *
     * Añade un coche al AVL de coches.
     *
     * @param coche Coche a añadir.
     */
    void insertacoche(Coche &coche);

    /**
     * @brief Establece el punto de recarga del sistema.
     *
     * Asigna un punto de recarga al sistema de Reanelcar.
     *
     * @param puntoRecarga Punto de recarga a asignar.
     */
    void setPuntoRecarga(const PuntoRecarga &puntoRecarga);

    /**
     * @brief Obtiene el punto de recarga asignado al sistema.
     * @return Referencia constante al punto de recarga.
     */
    [[nodiscard]] const PuntoRecarga &getPuntoRecarga() const;

    /**
     * @brief Obtiene la lista de usuarios del sistema.
     * @return Referencia constante a la lista de usuarios registrados.
     */
    [[nodiscard]] const ListaDEnlazada<Usuario> &getUsuarios() const;

    /**
     * @brief Establece la lista de usuarios del sistema.
     *
     * Asigna una lista de usuarios a la instancia de Reanelcar.
     *
     * @param usuarios Lista doblemente enlazada de usuarios.
     */
    void setUsuarios(const ListaDEnlazada<Usuario> &usuarios);
};


#endif //PR3AVL_REANELCAR_H
