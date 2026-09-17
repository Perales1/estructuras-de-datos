/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Hash.h
 * @brief Declaración de la clase Hash, que representa la estructura de una tabla de dispersión
 */

#ifndef PR5_HASH_H
#define PR5_HASH_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "EntradaUsuario.h"

/**
 * @brief Declaración anticipada de la clase EntradaUsuario
 */
class EntradaUsuario;

/**
 * @brief Clase que representa una tabla de dispersión para almacenar objetos de tipo Usuario
 */
class ThashUsuario {
private:
    std::vector<EntradaUsuario> tabla; ///< Tabla de dispersión que almacena las entradas.
    unsigned int maxElementos; ///< Número máximo de elementos en la tabla.
    unsigned int numElementos; ///< Número actual de elementos en la tabla.
    float lambda; ///< Factor de carga que controla la eficiencia de la tabla de dispersión.
    int numRedispersiones = 0; ///< Número de redispersiones realizadas

    /**
     * @brief Implementación de la variante del hash doble para resolución de colisiones.
     * @param clave Clave de hash.
     * @param intento Número de intentos de inserción (para manejar colisiones).
     * @return Valor del índice en la tabla calculado.
     */
    [[nodiscard]] unsigned int hashDobleVariante(unsigned long clave, int intento) const {
        unsigned int h1 = (clave * 11400714819323198485ull) % tabla.size();
        unsigned int h2 = (clave ^ 0x5bd1e995) % (tabla.size() - 1);
        return (h1 + intento * (h2 + 1)) % tabla.size();
    }

    /**
     * @brief Implementación de hash cuadrático para resolución de colisiones.
     * @param clave Clave de hash.
     * @param intento Número de intentos de inserción (para manejar colisiones).
     * @return Valor del índice en la tabla calculado.
     */
    [[nodiscard]] unsigned int hashCuadratica(unsigned long clave, int intento) const {
        return (clave + intento * intento) % tabla.size();
    }

    /**
     * @brief Implementación de hash doble estándar para resolución de colisiones.
     * @param clave Clave de hash.
     * @param intento Número de intentos de inserción (para manejar colisiones).
     * @return Valor del índice en la tabla calculado.
     */
    [[nodiscard]] unsigned int hashDoble(unsigned long clave, int intento) const {
        unsigned int h1 = (clave * 2654435761) % tabla.size();
        unsigned int h2 = 1 + (clave % (tabla.size() - 1));
        return (h1 + intento * h2) % tabla.size();
    }

public:

    /**
     * @brief Enumeración de los tipos de hash disponibles.
     */
    enum TipoHash {
        VARIANTE, ///< Variante de hash doble
        CUADRATICA, ///< Hash cuadrático
        DOBLE ///< Hash doble estándar
    };

    TipoHash tipoHash; ///< Tipo de hash utilizado en la tabla de dispersión

    /**
     * @brief Constructor por defecto que inicializa una tabla vacía.
     */
    ThashUsuario() = default;


    /**
     * @brief Constructor que inicializa la tabla de dispersión con un número máximo de elementos y un factor de carga.
     * @param maxElem Número máximo de elementos que puede almacenar la tabla.
     * @param lambda Factor de carga.
     * @param tipo Tipo de hash utilizado.
     */
    explicit ThashUsuario(int maxElem, float lambda = 0.7, TipoHash tipo = VARIANTE);

    /**
     * @brief Constructor de copia para realizar una copia de otra tabla de dispersión.
     * @param thashUsuario Tabla de dispersión a copiar.
     */
    ThashUsuario(const ThashUsuario &thashUsuario);

    /**
     * @brief Sobrecarga del operador de asignación.
     * @param thashUsuario Tabla de dispersión de la cual se copian los valores.
     * @return Referencia a la tabla de dispersión actual.
     */
    ThashUsuario &operator=(const ThashUsuario &thashUsuario);

    /**
     * @brief Destructor de la clase.
     */
    ~ThashUsuario();

    /**
     * @brief Inserta un nuevo usuario en la tabla de dispersión.
     * @param claveHash Clave de hash asociada al usuario.
     * @param usuario Usuario a insertar.
     * @return True si la inserción fue exitosa, false si hubo un error.
     */
    bool insertar(unsigned long claveHash, Usuario &usuario);

    /**
    * @brief Busca un usuario en la tabla de dispersión.
    * @param claveHash Clave de hash del usuario a buscar.
    * @return Puntero al usuario encontrado o nullptr si no se encuentra.
    */
    Usuario *buscar(unsigned long claveHash);

    /**
     * @brief Elimina un usuario de la tabla de dispersión.
     * @param claveHash Clave de hash del usuario a eliminar.
     * @return True si la eliminación fue exitosa, false si no se encuentra el usuario.
     */
    bool borrar(unsigned long claveHash);

    /**
     * @brief Obtiene el número máximo de colisiones durante las operaciones de inserción.
     * @return Número máximo de colisiones registradas.
     */
    unsigned int maxColisiones();

    /**
     * @brief Obtiene el número de elementos con más de 10 colisiones.
     * @return Número de elementos con más de 10 colisiones.
     */
    unsigned int numMax10();

    /**
     * @brief Calcula el promedio de colisiones durante las inserciones.
     * @return Promedio de colisiones.
     */
    float promedioColisiones();

    /**
     * @brief Calcula el factor de carga de la tabla de dispersión.
     * @return Factor de carga actual.
     */
    float factorCarga();

    /**
     * @brief Obtiene el tamaño actual de la tabla.
     * @return Número de entradas en la tabla.
     */
    unsigned int tamTabla();

    /**
     * @brief Muestra el estado actual de la tabla de dispersión.
     */
    void mostrarEstadoTabla();

    /**
     * @brief Calcula el índice de la tabla usando el tipo de hash configurado.
     * @param clave Clave de hash.
     * @param intento Número de intentos de inserción.
     * @return Índice en la tabla.
     */
    [[nodiscard]] unsigned int hash(unsigned long clave, int intento) const {
        switch (tipoHash) {
            case VARIANTE:
                return hashDobleVariante(clave, intento);
            case CUADRATICA:
                return hashCuadratica(clave, intento);
            case DOBLE:
                return hashDoble(clave, intento);
            default:
                return hashDobleVariante(clave, intento);
        }
    }

    /**
     * @brief Configura el tipo de hash a utilizar.
     * @param tipoHash1 Nuevo tipo de hash.
     */
    void configurarTipoHash(TipoHash tipoHash1) {
        tipoHash = tipoHash1;
    }

    /**
     * @brief Implementación del algoritmo djb2 para generar la clave de hash desde una cadena.
     * @param str Cadena de texto para la cual generar el hash.
     * @return Valor del hash generado.
     */
    unsigned long djb2(const std::string &str);

    /**
     * @brief Obtiene una lista de punteros a los usuarios válidos en la tabla (no eliminados).
     * @return Vector de punteros a usuarios válidos.
     */
    std::vector<Usuario *> obtenerUsuariosValidos() const;

    /**
     * @brief Establece un nuevo factor de carga para la tabla de dispersión.
     * @param lambda_ Nuevo factor de carga.
     */
    void setLambda(float lambda_);

    /**
     * @brief Redispersar la tabla de dispersión cuando el factor de carga es demasiado alto.
     * @param tam Nuevo tamaño para la tabla redispersada.
     */
    void redispersar(unsigned int tam);

};


#endif //PR5_HASH_H
