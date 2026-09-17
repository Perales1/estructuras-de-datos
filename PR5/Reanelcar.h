/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Reanelcar.h
 * @brief Declaración de la clase Reanelcar
 */

#ifndef PR5_REANELCAR_H
#define PR5_REANELCAR_H

#include <iostream>
#include <vector>
#include <list>
#include "PuntoRecarga.h"
#include "Trayecto.h"
#include "Hash.h"
#include "Usuario.h"


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
    ThashUsuario usersNif;

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
     * @brief Constructor de Reanelcar que inicializa con coches, usuarios, puntos de recarga y nifs
     * de usuarios.
     * @param coches AVL que contiene los coches.
     * @param usuarios Lista doblemente enlazada de usuarios.
     * @param puntoRecarga Punto de recarga de coches eléctricos.
     * @param usersNif Tabla hash que almacena los nifs de los usuarios
     */
    Reanelcar(std::map<std::string, Coche> &coches, std::list<Usuario> &usuarios,
              std::vector<PuntoRecarga> &puntoRecarga, ThashUsuario &usersNif);

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
    std::map<std::string, Coche> &getCoches();

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
     * @brief Establece los coches_ del sistema.
     *
     * @param coches_ Nuevo conjunto de coches_ para el sistema.
     */
    void setCoches(std::map<std::string, Coche> &coches_);

    /**
     * @brief Obtiene la lista de usuarios del sistema.
     *
     * @return Referencia a la lista de usuarios registrados.
     */
    [[nodiscard]]  std::list<Usuario> &getUsuarios();

    /**
     * @brief Establece los usuarios_ del sistema.
     *
     * @param usuarios_ Nueva lista de usuarios_ para el sistema.
     */
    void setUsuarios(std::list<Usuario> &usuarios_);

    /**
     * @brief Obtiene los puntos de recarga del sistema.
     *
     * @return Referencia a los puntos de recarga disponibles.
     */
    [[nodiscard]]  std::vector<PuntoRecarga> &getSitios();

    /**
     * @brief Establece los puntos de recarga del sistema.
     *
     * @param sitios_ Nuevos puntos de recarga para el sistema.
     */
    void setSitios(std::vector<PuntoRecarga> &sitios_);

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
     * @brief Obtiene los trayectos realizados por los usuarios en una fecha específica.
     *
     * @param f Fecha para la cual se buscan los trayectos.
     * @return Lista de pares de usuarios y trayectos realizados en esa fecha.
     */
    std::vector<std::pair<Usuario, Trayecto>> trayectosEnFecha(Fecha f);

    /**
    * @brief Borra un usuario del sistema en la tabla hash.
    *
    * Elimina un usuario de la tabla hash de usuarios por su NIF.
    *
    * @param nif NIF del usuario a eliminar.
    * @return True si el usuario se borra correctamente, false si no existe.
    */
    bool borrarUsuarioTHash(const std::string &nif);

    /**
     * @brief Muestra el estado actual de la tabla hash de usuarios.
     */
    void mostrarEstadoTabla();

    /**
     * @brief Configura la tabla hash de usuarios.
     *
     * Establece el factor de carga (lambda) y el tipo de función hash.
     *
     * @param lambda Factor de carga de la tabla hash.
     * @param tipo Tipo de función hash a usar.
     */
    void configurarTablaHash(float lambda, ThashUsuario::TipoHash tipo);

    /**
     * @brief Verifica si un número es primo.
     *
     * Devuelve verdadero si el número es primo, falso en caso contrario.
     *
     * @param num Número a comprobar si es primo.
     * @return True si el número es primo, false si no lo es.
     */
    bool esprimo(int num);

    /**
     * @brief Calcula el siguiente número primo a partir de un número dado
     * @param num
     * @return Siguiente número primo
     */
    int siguientePrimo(int num);

    /**
     * @brief Busca usuarios por su primer carácter del nombre.
     *
     * Devuelve una lista de usuarios cuyo nombre comienza con la letra proporcionada.
     *
     * @param letra Letra inicial del nombre de usuario.
     * @return Lista de usuarios cuyos nombres empiezan con la letra dada.
     */
    std::vector<std::string> buscarUsuariosConW(char letra);

    /**
     * @brief Busca un usuario en la tabla hash por su NIF.
     *
     * Recorre la tabla hash para encontrar un usuario con el NIF especificado.
     *
     * @param nif NIF del usuario a buscar.
     * @return Puntero al usuario encontrado o nullptr si no existe.
     */
    Usuario *buscarUsrNifThash(std::string &nif);

    /**
     * @brief Configura la tabla hash de usuarios automáticamente.
     *
     * Configura la tabla hash de usuarios utilizando el tipo de hash especificado.
     *
     * @param tipoHash Tipo de hash a configurar.
     */
    void configurarTablaHashAuto(ThashUsuario::TipoHash tipoHash);

    /**
     * @brief Busca en la lista de usuarios del sistema los usuarios que empiecen por un prefijo dado
     * y devuelve una lista con los usuarios encontrados
     * @param prefijo
     * @return lista de Usuarios que empiecen por el prefijo dado
     */
    std::list<Usuario> buscarUsuarioPorNombreInicial(const std::string &prefijo);

    /**
     * @brief Busca usuarios cuyo nombre comience con un prefijo.
     *
     * Devuelve una lista de usuarios cuyos nombres empiezan con el prefijo dado.
     *
     * @param prefijo Prefijo que debe coincidir con el inicio del nombre de los usuarios.
     * @return Lista de usuarios cuyo nombre comienza con el prefijo.
     */
    void mostrarTrayectosUsuariosWi(std::string &prefijo, int retraso);

    /**
     * @brief Elimina y reinserta un usuario en la tabla hash.
     *
     * Permite eliminar un usuario por su NIF y luego reinsertarlo en la tabla hash.
     *
     * @param nifabuscar NIF del usuario a eliminar y reintegrar.
     */
    void eliminarYReinsertarUsuario(std::string &nifabuscar);

    /**
     * @brief Elimina usuarios cuyo nombre comienza con un prefijo específico.
     *
     * Elimina todos los usuarios cuya nombre comienza con el prefijo proporcionado.
     *
     * @param prefijo Prefijo para buscar y eliminar usuarios.
     */
    void eliminarUsuariosPorNombre(std::string &prefijo);

    /**
     * @brief Muestra los trayectos de los usuarios cuyo nombre comienza con un prefijo dado.
     *
     * Muestra los trayectos de los usuarios cuyo nombre empieza con un prefijo específico.
     *
     * @param prefijo Prefijo para buscar usuarios.
     * @param retraso Retraso en milisegundos entre cada trayecto mostrado.
     * @note Es diferente a la función llamada "mostrartrayectosusuarioswi" porque la implementación
     * es diferente debido a exigencias de los ejercicios propuestos
     */
    void mostrarTrayectosUsuariosWil(const std::string &prefijo, int retraso);

    /**
     * @brief Fuerza una redispersión de la tabla hash.
     *
     * Realiza una redispersión de la tabla hash para mejorar su eficiencia.
     */
    void forzarRedispersion();
};


#endif //PR5_REANELCAR_H
