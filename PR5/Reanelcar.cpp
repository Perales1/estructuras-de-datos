/**
 * @author David Fernández Espejo dfe00001@red.ujaen.es
 * @author David Lorente Wagner dlw00001@red.ujaen.es
 * @file Reanelcar.cpp
 * @brief Implementación de la clase Reanelcar
 */

#include <cmath>
#include "Reanelcar.h"

class ThashUsuario;

bool Reanelcar::esprimo(int num) {
    if (num <= 1) return false;
    for (int i = 2; i < sqrt(num); ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

int Reanelcar::siguientePrimo(int num) {
    while (!esprimo(num)) {
        num++;
    }
    return num;
}

/**
 * @brief Implementación del algoritmo djb2 para generar la clave de hash desde una cadena.
 * @param str Cadena de texto para la cual generar el hash.
 * @return Valor del hash generado.
 */
unsigned long djb2(const std::string &str) {
    unsigned long hash = 5381;

    for (char c: str) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}


Reanelcar::Reanelcar() = default;

Reanelcar::Reanelcar(std::map<std::string, Coche> &coches) : coches(coches) {}

Reanelcar::Reanelcar(std::map<std::string, Coche> &coches, std::list<Usuario> &usuarios,
                     std::vector<PuntoRecarga> &puntoRecarga) : coches(coches), usuarios(usuarios),
                                                                sitios(puntoRecarga) {
    for (Usuario &usuario: this->usuarios) {
        usuario.setLinkReanelcar(this);
    }
}

Reanelcar::Reanelcar(std::map<std::string, Coche> &coches, std::list<Usuario> &usuarios,
                     std::vector<PuntoRecarga> &puntoRecarga, ThashUsuario &usersNif) : coches(coches),
                                                                                        usuarios(usuarios),
                                                                                        sitios(puntoRecarga),
                                                                                        usersNif(usersNif) {
    float lambda = 0.7;
    usersNif = ThashUsuario(usuarios.size(), lambda, ThashUsuario::VARIANTE);
    for (Usuario &usuario: this->usuarios) {
        usuario.setLinkReanelcar(this);
        unsigned long hashKey = usersNif.djb2(usuario.getNif());
        usersNif.insertar(hashKey, usuario);
    }
}

void Reanelcar::configurarTablaHash(float lambda, ThashUsuario::TipoHash tipo) {
    int totalUsuarios = usuarios.size();
    int tamanioTabla = siguientePrimo(std::ceil(totalUsuarios / lambda));

    usersNif = ThashUsuario(tamanioTabla, lambda);
    usersNif.configurarTipoHash(tipo);

    for (Usuario &usuario: usuarios) {
        unsigned long hashkey = usersNif.djb2(usuario.getNif());
        usersNif.insertar(hashkey, usuario);
    }

    std::cout << "Tabla hash de usuarios configurada:" << std::endl;
    usersNif.mostrarEstadoTabla();
}

void Reanelcar::configurarTablaHashAuto(ThashUsuario::TipoHash tipo) {
    int totalUsuarios = usuarios.size();

    int tamanioTabla = siguientePrimo(static_cast<int>(totalUsuarios * 1.33f));

    float lambda = static_cast<float>(totalUsuarios) / tamanioTabla;

    usersNif = ThashUsuario(tamanioTabla, lambda);
    usersNif.configurarTipoHash(tipo);

    for (Usuario &usuario: usuarios) {
        unsigned long hashkey = usersNif.djb2(usuario.getNif());
        usersNif.insertar(hashkey, usuario);
    }

    std::cout << "Tabla hash configurada con lambda = " << lambda << std::endl;
    std::cout << "Factor de carga calculado: " << lambda << std::endl;
    usersNif.mostrarEstadoTabla();
}

Reanelcar::Reanelcar(std::map<std::string, Coche> &coches, std::list<Usuario> &usuarios) : coches(coches),
                                                                                           usuarios(
                                                                                                   usuarios) {}


Reanelcar::~Reanelcar() = default;

std::list<Usuario> Reanelcar::buscarUsuarioPorNombre(std::string &nombre) {
    std::list<Usuario> resultado;
    std::list<Usuario>::iterator iterador = usuarios.begin();
    while (iterador != usuarios.end()) {
        Usuario &usuario = *iterador;
        if (usuario.getNombre() == nombre) {
            resultado.push_back(usuario);
        }
        ++iterador;
    }
    return resultado;
}

Usuario *Reanelcar::buscarUsuarioPorNif(std::string &nif) {
    std::list<Usuario>::iterator iterador = usuarios.begin();
    while (iterador != usuarios.end()) {
        Usuario &usuario = *iterador;
        if (usuario.getNif() == nif) {
            return &usuario;
        }
        ++iterador;
    }
    return nullptr;
}

Coche *Reanelcar::buscarCochePorMatricula(std::string &matricula) {
    std::map<std::string, Coche>::iterator iterador = coches.find(matricula);
    return iterador != coches.end() ? &iterador->second : nullptr;
}

bool Reanelcar::colocarCochePR(Coche *coche_, PuntoRecarga *pr) {
    if (!pr || !coche_) {
        std::cerr << "Error: Punto de carga o coche invalido." << std::endl;
        return false;
    }

    if (pr->getNumCoches() >= pr->getMax()) {
        std::cerr << "Error: Punto de recarga lleno para el coche con matricula " << coche_->getIdMatricula()
                  << std::endl;
        return false;
    }

    coche_->aparcar(pr);

    if (pr->addCoche(coche_)) {
        return true;
    } else {
        std::cerr << "Error: No se pudo añadir el coche " << coche_->getIdMatricula() << " al punto de recarga."
                  << std::endl;
        return false;
    }
}

std::map<std::string, Coche> &Reanelcar::getCoches() {
    return coches;
}

void Reanelcar::insertacoche(Coche &coche) {
    coches[coche.getIdMatricula()] = coche;
}

void Reanelcar::insertausuario(Usuario &usuario) {
    usuarios.push_back(usuario);
}

Coche *Reanelcar::alquilar(Usuario &u, int idprorigen, int idprdes, Fecha &fini) {

    if (idprorigen < 0 || idprdes < 0) {
        std::cerr << "Error: IDs de punto de recarga inválidos" << std::endl;
        return nullptr;
    }

    PuntoRecarga *puntoSalida = nullptr;
    for (PuntoRecarga &punto: sitios) {
        if (punto.getId() == idprorigen) {
            puntoSalida = &punto;
            break;
        }
    }

    if (!puntoSalida) {
        std::cerr << "Error: Punto de recarga de origen no encontrado." << std::endl;
        return nullptr;
    }

    if (puntoSalida->getNumCoches() == 0) {
        std::cerr << "Error: No hay coches disponibles en el punto de origen." << std::endl;
        return nullptr;
    }

    Coche *cocheAlquilado = puntoSalida->getMaxBateria();
    if (!cocheAlquilado) {
        std::cerr << "Error: No se pudo obtener un coche del punto de recarga." << std::endl;
        return nullptr;
    }

    if (cocheAlquilado->getIdMatricula().empty()) {
        std::cerr << "Error: El coche seleccionado no tiene una matricula valida." << std::endl;
        return nullptr;
    }

    u.setCochealquilado(cocheAlquilado);

    return cocheAlquilado;
}

PuntoRecarga *Reanelcar::obtenerPRmenosCoches() {
    if (sitios.empty()) {
        return nullptr;
    }

    PuntoRecarga *puntoConMenosCoches = &sitios[0];
    int minCoches = puntoConMenosCoches->getNumCoches();

    for (PuntoRecarga &punto: sitios) {
        if (punto.getNumCoches() < minCoches) {
            puntoConMenosCoches = &punto;
            minCoches = punto.getNumCoches();
        }
    }

    return puntoConMenosCoches;
}


void Reanelcar::setCoches(std::map<std::string, Coche> &coches_) {
    Reanelcar::coches = coches_;
}

std::list<Usuario> &Reanelcar::getUsuarios() {
    return usuarios;
}

void Reanelcar::setUsuarios(std::list<Usuario> &usuarios_) {
    Reanelcar::usuarios = usuarios_;
}

std::vector<PuntoRecarga> &Reanelcar::getSitios() {
    return sitios;
}

void Reanelcar::setSitios(std::vector<PuntoRecarga> &sitios_) {
    Reanelcar::sitios = sitios_;
}

PuntoRecarga *Reanelcar::getPuntoRecargaID(int id) {
    for (PuntoRecarga &sitio: sitios) {
        if (sitio.getId() == id) {
            return &sitio;
        }
    }
    return nullptr;
}

void Reanelcar::agregarPuntosRecarga(PuntoRecarga &punto) {
    sitios.push_back(punto);
}


std::vector<std::pair<Usuario, Trayecto>> Reanelcar::trayectosEnFecha(Fecha f) {
    std::vector<std::pair<Usuario, Trayecto>> trayectosEnFecha;

    for (Usuario &usuario: usuarios) {
        for (auto &parTrayecto: usuario.getTrayectos()) {
            Trayecto *trayecto = parTrayecto.second;

            if (trayecto->getfechaInicio().verDia() == f.verDia() &&
                trayecto->getfechaInicio().verMes() == f.verMes() &&
                trayecto->getfechaInicio().verAnio() == f.verAnio()) {

                trayectosEnFecha.emplace_back(usuario, *trayecto);
            }
        }
    }

    return trayectosEnFecha;
}

bool Reanelcar::borrarUsuarioTHash(const std::string &nif) {
    unsigned long hashkey = djb2(nif);
    Usuario *usuario = usersNif.buscar(hashkey);
    if (!usuario) {
        std::cerr << " Usuario con NIF: " << nif << " no encontrado. " << std::endl;
        return false;
    }

    usuario->eliminarTrayectos();

    Coche *cochealquilado = usuario->getCochealquilado();
    if (cochealquilado) {
        usuario->setCochealquilado(nullptr);
    }

    for (auto it = usuarios.begin(); it != usuarios.end(); ++it) {
        if (it->getNif() == nif) {
            usuarios.erase(it);
            std::cout << " Usuario con NIF: " << nif << " eliminado correctamente. " << std::endl;
            return true;
        }
    }

    std::cerr << " Usuario con NIF: " << nif << " no se encontro en la lista para eliminar. " << std::endl;
    return false;
}

void Reanelcar::mostrarEstadoTabla() {
    std::cout << " Estado de la tabla de usuarios: " << std::endl;
    usersNif.mostrarEstadoTabla();
}

std::vector<std::string> Reanelcar::buscarUsuariosConW(char letra) {
    std::vector<Usuario *> usuarios = usersNif.obtenerUsuariosValidos();
    std::vector<std::string> nifsConInicial;

    for (Usuario* const &usuarioptr: usuarios) {
        if (usuarioptr != nullptr && !usuarioptr->getNombre().empty() && usuarioptr->getNombre()[0] == letra) {
            nifsConInicial.push_back(usuarioptr->getNif());
        }
    }
    return nifsConInicial;
}

Usuario *Reanelcar::buscarUsrNifThash(std::string &nif) {
    unsigned long claveHash = usersNif.djb2(nif);
    return usersNif.buscar(claveHash);
}

std::list<Usuario> Reanelcar::buscarUsuarioPorNombreInicial(const std::string &prefijo) {
    std::list<Usuario> resultado;
    for (Usuario &usuario: usuarios) {
        if (usuario.getNombre().substr(0, prefijo.size()) == prefijo) {
            resultado.push_back(usuario);
        }
    }
    return resultado;
}

//NOTA: Daba error si no se hacía con método propio
void Reanelcar::mostrarTrayectosUsuariosWi(std::string &prefijo, int retraso) {
    std::list<Usuario> usuariosWi = buscarUsuarioPorNombreInicial(
            prefijo);
    int contador = 0;

    for (Usuario &usuario: usuariosWi) {
        if (contador >= 10) break;

        Coche *coche = usuario.getCochealquilado();
        if (!coche) {
            std::cerr << "El usuario " << usuario.getNombre() << " no tiene un coche alquilado." << std::endl;
            continue;
        }

        Trayecto *ultimoTrayecto = usuario.getUltimoTrayecto();
        if (!ultimoTrayecto) {
            std::cerr << "El usuario " << usuario.getNombre() << " no tiene trayectos registrados." << std::endl;
            continue;
        }

        PuntoRecarga *puntoDestino = ultimoTrayecto->getDestination();
        if (!puntoDestino) {
            std::cerr << "Punto de recarga de destino no encontrado para el trayecto del usuario "
                      << usuario.getNombre() << std::endl;
            continue;
        }

        usuario.aparcaCoche(coche, puntoDestino, retraso);

        std::cout << "Usuario: " << usuario.getNombre() << " (NIF: " << usuario.getNif() << ")" << std::endl;
        usuario.mostrarTrayectosConRetraso();
        std::cout << "--------------------------------------------" << std::endl;

        contador++;
    }
}

void Reanelcar::eliminarYReinsertarUsuario(std::string &nifabuscar) {
    std::cout << "Eliminando usuario con NIF: " << nifabuscar << std::endl;
    bool eliminado = borrarUsuarioTHash(nifabuscar);
    if (eliminado) {
        std::cout << "Usuario con NIF: " << nifabuscar << " eliminado con exito." << std::endl;
    } else {
        std::cout << "ERROR: El usuario con NIF: " << nifabuscar << " no pudo ser eliminado." << std::endl;
        return;
    }

    std::cout << "Reinsertando el usuario con NIF: " << nifabuscar << std::endl;
    std::string nombreabuscar = "Wallas Bampford";
    Usuario usuarioReinsercion(nombreabuscar, nifabuscar);
    insertausuario(usuarioReinsercion);

    Usuario *usuarioReinsertado = usersNif.buscar(djb2(nifabuscar));
    if (usuarioReinsertado) {
        std::cout << "Usuario reinsertado con exito. Nombre: " << usuarioReinsertado->getNombre() << std::endl;

        std::cout << "Trayectos del usuario (deberian estar vacios): " << std::endl;
        if (usuarioReinsertado->getTrayectos().empty()) {
            std::cout << "No tiene trayectos." << std::endl;
        } else {
            for (std::pair<const Fecha, Trayecto *> &trayecto: usuarioReinsertado->getTrayectos()) {
                std::cout << "Trayecto ID: " << trayecto.first << std::endl;
            }
        }
    } else {
        std::cout << "ERROR: No se pudo reinsertar el usuario correctamente." << std::endl;
        return;
    }

    std::cout << "Estado de la tabla despues de la reinsercion: " << std::endl;
    usersNif.mostrarEstadoTabla();
}

void Reanelcar::eliminarUsuariosPorNombre(std::string &prefijo) {
    std::cout << "Numero de usuarios antes de la eliminacion: " << usuarios.size() << std::endl;

    for (auto it = usuarios.begin(); it != usuarios.end();) {
        if (it->getNombre().substr(0, prefijo.length()) == prefijo) {
            unsigned long claveHash = djb2(it->getNif());

            if (usersNif.borrar(claveHash)) {
                std::cout << "Usuario con NIF: " << it->getNif() << " eliminado." << std::endl;
                it = usuarios.erase(it);
            } else {
                std::cout << "No se pudo eliminar el usuario con NIF: " << it->getNif() << std::endl;
                ++it;
            }
        } else {
            ++it;
        }
    }

    std::cout << "Numero de usuarios despues de la eliminacion: " << usuarios.size() << std::endl;

    std::cout << "Estado de la tabla despues de la eliminacion: " << std::endl;
    usersNif.mostrarEstadoTabla();
}

void Reanelcar::mostrarTrayectosUsuariosWil(const std::string &prefijo, int retraso) {
    std::list<Usuario> usuariosWil = buscarUsuarioPorNombreInicial(prefijo);
    int contador = 0;

    for (Usuario &usuario: usuariosWil) {
        if (contador >= usuariosWil.size()) break;

        Coche *coche = usuario.getCochealquilado();
        if (!coche) {
            std::cerr << "El usuario " << usuario.getNombre() << " no tiene un coche alquilado." << std::endl;
            continue;
        }

        Trayecto *ultimoTrayecto = usuario.getUltimoTrayecto();
        if (!ultimoTrayecto) {
            std::cerr << "El usuario " << usuario.getNombre() << " no tiene trayectos registrados." << std::endl;
            continue;
        }

        PuntoRecarga *puntoDestino = ultimoTrayecto->getDestination();
        if (!puntoDestino) {
            std::cerr << "Punto de recarga de destino no encontrado para el trayecto del usuario "
                      << usuario.getNombre() << std::endl;
            continue;
        }

        usuario.aparcaCoche(coche, puntoDestino, retraso);

        std::cout << "Usuario: " << usuario.getNombre() << " (NIF: " << usuario.getNif() << ")" << std::endl;
        std::cout << "Ultimo trayecto:" << std::endl;
        std::cout << "  Origen: " << ultimoTrayecto->getOrigin()->getId() << std::endl;
        std::cout << "  Destino: " << ultimoTrayecto->getDestination()->getId() << std::endl;
        std::cout << "  Coche alquilado: " << coche->getIdMatricula() << std::endl;
        std::cout << "  Fecha inicio: " << ultimoTrayecto->getfechaInicio().cadena() << std::endl;
        std::cout << "  Fecha fin: " << ultimoTrayecto->getfechaFin().cadena() << std::endl;
        std::cout << "--------------------------------------------" << std::endl;

        contador++;
    }
}

void Reanelcar::forzarRedispersion() {
    float nuevoLambda = 0.1;
    unsigned nuevoTam = siguientePrimo(std::ceil(usersNif.tamTabla() * 1.3));
    usersNif.redispersar(nuevoTam);
    usersNif.setLambda(nuevoLambda);
}