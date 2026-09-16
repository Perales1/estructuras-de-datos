/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file EntradaUsuario.h
 * @brief Implementación de la clase EntradaUsuario, que representa el dato alamcenado en la tabla de
 * dispersión
 */

#ifndef PR6_ENTRADAUSUARIO_H
#define PR6_ENTRADAUSUARIO_H

#include <memory>

/**
 * @brief Declaración anticipada de la clase Usuario.
 */
class Usuario;

/**
 * @brief Clase que representa una entrada en la tabla de dispersión de usuarios.
 *
 * La clase EntradaUsuario almacena una clave de hash única y un puntero a un objeto de tipo Usuario.
 * Se utiliza para gestionar la asociación entre claves hash y usuarios en una estructura de tabla de dispersión.
 */
class EntradaUsuario {
private:
    unsigned long claveHash; ///< La clave única de Hash
    std::unique_ptr<Usuario> usuario; ///< Puntero único al dato almacenado

public:

    /**
     * @brief Constructor por defecto. Inicializa una entrada vacía.
     */
    EntradaUsuario();

    /**
     * @brief Constructor que inicializa la entrada con una clave de hash y un usuario.
     * @param clave Clave hash única que identifica al usuario.
     * @param usr Usuario que se asocia a esta clave hash.
     */
    EntradaUsuario(unsigned long clave, Usuario &usr);

    /**
     * @brief Destructor por defecto.
     */
    ~EntradaUsuario();

    /**
    * @brief Constructor de copia.
    * @param otro EntradaUsuario de la cual se realiza la copia.
    */
    EntradaUsuario(const EntradaUsuario &otro);

    /**
     * @brief Sobrecarga del operador de asignación.
     * @param otro EntradaUsuario de la cual se copian los valores.
     * @return Referencia a la entrada actual.
     */
    EntradaUsuario &operator=(const EntradaUsuario &otro);

    /**
     * @brief Obtiene la clave hash de esta entrada.
     * @return La clave hash asociada.
     */
    [[nodiscard]] unsigned long getClaveHash() const;

    /**
    * @brief Obtiene el puntero al usuario almacenado en esta entrada.
    * @return Puntero al objeto Usuario.
    */
    [[nodiscard]] Usuario *getUsuario() const;

    /**
     * @brief Establece la clave hash de esta entrada.
     * @param clave Nueva clave hash.
     */
    void setClaveHash(unsigned long clave);

    /**
    * @brief Establece el usuario para esta entrada.
    * @param usr Usuario a asociar con esta entrada.
    */
    void setUsuario(Usuario &usr);

    /**
     * @brief Verifica si la entrada está vacía (sin usuario asociado).
     * @return True si la entrada está vacía, false en caso contrario.
     */
    [[nodiscard]] bool vacia() const;

    /**
     * @brief Vacía la entrada, eliminando al usuario asociado.
     */
    void vaciar();
};

#endif // PR5_ENTRADAUSUARIO_H
