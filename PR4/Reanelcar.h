/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Reanelcar.h
 * @brief Declaración de la clase Reanelcar
 */
#ifndef PR4STL_REANELCAR_H
#define PR4STL_REANELCAR_H

#include <iostream>
#include <vector>
#include "Usuario.h"
#include "PuntoRecarga.h"
#include "fecha.h"
#include "Trayecto.h"

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

    std::map<std::string, Coche> coches; ///< Árbol AVL de coches disponibles.
    std::list<Usuario> usuarios; ///< Lista doblemente enlazada de usuarios registrados.
    std::vector<PuntoRecarga> sitios; ///< Punto de recarga para coches eléctricos.

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
    explicit Reanelcar(std::map<std::string, Coche> &coches);

    /**
    * @brief Constructor de Reanelcar que inicializa con un conjunto de coches y usuarios.
    * @param coches AVL que contiene los coches.
    * @param usuarios Lista doblemente enlazada de usuarios.
    */
    Reanelcar(std::map<std::string, Coche> &coches, std::list<Usuario> &usuarios);

    /**
     * @brief Constructor de Reanelcar que inicializa con coches, usuarios y un punto de recarga.
     * @param coches AVL que contiene los coches.
     * @param usuarios Lista doblemente enlazada de usuarios.
     * @param puntoRecarga Punto de recarga de coches eléctricos.
     */
    Reanelcar(std::map<std::string, Coche> &coches, std::list<Usuario> &usuarios,
              std::vector<PuntoRecarga> &puntoRecarga);


    /**
     * @brief Coloca un coche en el punto de recarga.
     *
     * Añade un coche al punto de recarga asociado, si hay capacidad disponible.
     *
     * @param coche_ Coche a colocar en el punto de recarga.
     */
    bool colocarCochePR(Coche *coche_, PuntoRecarga *pr);

    /**
     * @brief Busca usuarios por su nombre.
     *
     * Devuelve una lista de usuarios cuyo nombre coincide con el parámetro de búsqueda.
     *
     * @param nombre Nombre del usuario a buscar.
     * @return Lista de usuarios con el nombre especificado.
     */
    std::list<Usuario> buscarUsuarioPorNombre(std::string &nombre);

    /**
     * @brief Busca un coche por su matrícula.
     *
     * Recorre el AVL de coches para encontrar un coche con la matrícula especificada.
     *
     * @param matricula Matrícula del coche a buscar.
     * @return Puntero al coche encontrado o nullptr si no existe.
     */
    Coche *buscarCochePorMatricula(std::string &matricula);

    /**
     * @brief Busca un usuario por su NIF.
     *
     * Recorre la lista de usuarios para encontrar un usuario con el NIF especificado.
     *
     * @param nif NIF del usuario a buscar.
     * @return Puntero al usuario encontrado o nullptr si no existe.
     */
    Usuario *buscarUsuarioPorNif(std::string &nif);

    /**
     * @brief Obtiene el AVL de coches del sistema.
     * @return El AVL de coches disponibles.
     */
    std::map<std::string, Coche>& getCoches();

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
     * @brief Alquila un coche a un usuario.
     *
     * Permite a un usuario alquilar un coche entre dos puntos de recarga.
     *
     * @param u Usuario que alquila el coche.
     * @param idprorigen ID del punto de recarga de origen.
     * @param idprdes ID del punto de recarga de destino.
     * @param fini Fecha de inicio del alquiler.
     * @return Puntero al coche alquilado o nullptr si no hay coches disponibles.
     */
    Coche *alquilar(Usuario &u, int idprorigen, int idprdes, Fecha &fini);

    /**
     * @brief Obtiene el punto de recarga con menos coches.
     *
     * Busca entre los puntos de recarga disponibles para encontrar aquel con menos coches.
     *
     * @return Puntero al punto de recarga con menos coches.
     */
    PuntoRecarga *obtenerPRmenosCoches();

    /**
     * @brief Establece los coches del sistema.
     *
     * @param coches Nuevo conjunto de coches para el sistema.
     */
    void setCoches(std::map<std::string, Coche> &coches);

    /**
     * @brief Obtiene la lista de usuarios del sistema.
     *
     * @return Referencia a la lista de usuarios registrados.
     */
    [[nodiscard]]  std::list<Usuario> &getUsuarios();

    /**
     * @brief Establece los usuarios del sistema.
     *
     * @param usuarios Nueva lista de usuarios para el sistema.
     */
    void setUsuarios(std::list<Usuario> &usuarios);

    /**
     * @brief Obtiene los puntos de recarga del sistema.
     *
     * @return Referencia a los puntos de recarga disponibles.
     */
    [[nodiscard]]  std::vector<PuntoRecarga> &getSitios();

    /**
     * @brief Establece los puntos de recarga del sistema.
     *
     * @param sitios Nuevos puntos de recarga para el sistema.
     */
    void setSitios(std::vector<PuntoRecarga> &sitios);

    /**
     * @brief Obtiene el punto de recarga por su ID.
     *
     * @param id ID del punto de recarga a obtener.
     * @return Puntero al punto de recarga correspondiente.
     */
    PuntoRecarga *getPuntoRecargaID(int id);

    /**
     * @brief Agrega un nuevo punto de recarga al sistema.
     *
     * @param punto Nuevo punto de recarga a añadir.
     */
    void agregarPuntosRecarga(PuntoRecarga &punto);

    /**
     * @brief Muestra los datos de un coche específico.
     *
     * @param matriculaObjetivo Matrícula del coche cuyo detalle se desea mostrar.
     */
    void mostrarDatosCoche(std::string &matriculaObjetivo);

    /**
     * @brief Obtiene los trayectos realizados por los usuarios en una fecha específica.
     *
     * @param f Fecha para la cual se buscan los trayectos.
     * @return Lista de pares de usuarios y trayectos realizados en esa fecha.
     */
    std::vector<std::pair<Usuario, Trayecto>> trayectosEnFecha(const Fecha f);
};


#endif //PR4STL_REANELCAR_H
