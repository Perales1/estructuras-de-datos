# Reanelcar - Sistema de Gestion de Vehiculos Electricos Compartidos (Carsharing)

Reanelcar es un sistema integral de simulacion y gestion para un servicio de carsharing (alquiler de coches electricos compartidos) desarrollado en C++17.

El proyecto combina indexacion geoespacial, tablas de dispersion personalizadas, estructuras jerarquicas y generacion de imagenes rasterizadas (mapas PPM) para optimizar la busqueda de vehiculos, puntos de recarga y el calculo de trayectos de usuarios.

---

## Caracteristicas Principales

- Indexacion Geoespacial (Malla Regular 2D): Busqueda rapida e inercial de vehiculos y puntos de recarga en un mapa bidimensional utilizando coordenadas UTM.
- Tabla de Dispersion (Hash Table) de Usuarios: Indexacion eficiente de usuarios mediante claves de NIF con gestion de colisiones y dispersion dinamica.
- Gestion de Flota (Map / Arboles AVL): Organizacion de vehiculos ordenados por matricula para accesos rapidos O(log n).
- Simulacion de Trayectos y Bateria: Registro de desplazamientos, calculo de consumo energetico, recargas automaticas y tiempos de trayecto.
- Generacion Visual de Mapas (formato PPM): Exportacion de mapas de calor e imagenes donde se representan las posiciones de los coches, usuarios y areas de servicio.
- Documentacion Tecnica Completa: Incluye documentacion detallada del codigo generada de forma automatica con Doxygen.

---

## Estructuras de Datos y Complejidad

El diseno del sistema prioriza la eficiencia algoritmica seleccionando la estructura de datos optima para cada caso de uso:

| Modulo / Entidad | Estructura de Datos | Complejidad Busqueda | Proposito / Beneficio |
|---|---|---|---|
| Busqueda Geografica | MallaRegular<T> (Espacial 2D) | O(1) promedio | Busqueda por proximidad espacial y celdas contiguas |
| Gestion de Usuarios | ThashUsuario (Tabla Hash) | O(1) promedio | Acceso instantaneo al perfil de usuario mediante NIF |
| Flota de Coches | std::map<string, Coche> (Red-Black / AVL) | O(log n) | Mantener la flota ordenada por matricula |
| Puntos de Recarga | std::vector<PuntoRecarga> | O(1) acceso directo | Almacenamiento continuo en memoria de estaciones |
| Historial Trayectos | std::list<Trayecto> | O(1) insercion | Insercion eficiente de nuevos viajes en el historial |

---

## Arquitectura del Proyecto

Casilla.h
Celdas de la Malla Regular Espacial

Coche.h / Coche.cpp
Entidad Vehiculo (bateria, estado, posicion UTM)

EntradaUsuario.h / EntradaUsuario.cpp
Nodo de la tabla Hash para usuarios

Hash.h / Hash.cpp
Implementacion de la Tabla Hash (ThashUsuario)

MallaRegular.h
Plantilla (Template) de Malla Espacial 2D

PuntoRecarga.h / PuntoRecarga.cpp
Estaciones de recarga electrica

Reanelcar.h / Reanelcar.cpp
Controlador principal del sistema

Trayecto.h / Trayecto.cpp
Registro de desplazamientos

Usuario.h / Usuario.cpp
Entidad Usuario (datos personales, historial)

UTM.h / UTM.cpp
Representacion de Coordenadas Universal Transverse Mercator

fecha.h / fecha.cpp
Utilidad de gestion de fechas y horas

img.h / img.cpp
Modulo de renderizado y exportacion del mapa (PPM)

main.cpp
Carga de datos CSV y ejecucion de pruebas

CMakeLists.txt
Configuracion de compilacion CMake

html/ y latex/
Carpetas con la documentacion del proyecto generada mediante Doxygen (Formatos HTML y LaTeX).

---

## Documentacion del Codigo (Doxygen)

El proyecto cuenta con documentacion detallada generada a partir de los comentarios de cabecera y archivos fuente utilizando Doxygen.

La documentacion esta disponible en los siguientes formatos dentro de las carpetas comprimidas html/ y latex/

- HTML: Se puede consultar abriendo el archivo Documentacion/html/index.html en cualquier navegador web para acceder a los diagramas de clases, grafos de dependencias e indice de la API.
- LaTeX: Disponible en la carpeta Documentacion/latex/ para compilar la documentacion completa en formato PDF mediante pdflatex (ejecutando make dentro del directorio latex).

---

## Formato de Entrada de Datos

El sistema carga de forma masiva los datos iniciales mediante archivos de texto plano / CSV incluidos en la raiz:

- coches_v2.csv: Listado de coches (Matricula, Marca, Modelo, Coordenadas UTM, Bateria).
- usuarios1.csv: Registro de usuarios (NIF, Nombre, Direccion, Contrasena).
- puntos_recarga.csv: Ubicacion geografica de estaciones de recarga rapida.
- destino.csv: Puntos de destino simulados para el calculo de rutas.

---

## Salida Visual (Mapa PPM)

Tras procesar la ubicacion de los vehiculos y las solicitudes de usuarios, el programa genera un mapa rasterizado en el archivo mapaResultado.ppm que permite visualizar la distribucion geografica de la flota y los puntos de demanda sobre el area cubierta por la malla regular.

---

## Autores

- David Fernandez Espejo - dfe00004@red.ujaen.es
- David Lorente Wagner - dlw00001@red.ujaen.es

Universidad de Jaen (UJA) - Grado en Ingenieria Informatica
