# Reanelcar - Sistema de Gestión de Vehículos Eléctricos Compartidos (Carsharing)

El proyecto implementa el sistema integral de simulación y gestión para el servicio de carsharing **Reanelcar** en **C++17**. Esta práctica combina indexación geoespacial mediante Malla Regular 2D, tablas de dispersión personalizadas (`ThashUsuario`), estructuras jerárquicas y generación de imágenes rasterizadas (mapas PPM) para optimizar la búsqueda de vehículos, puntos de recarga y el cálculo de trayectos.

## Características Técnicas del Proyecto

* **Indexación Geoespacial (Malla Regular 2D):** Búsqueda rápida e inercial de vehículos y puntos de recarga en un mapa bidimensional utilizando coordenadas UTM (`MallaRegular.h`, `Casilla.h`).
* **Tabla de Dispersión Personalizada (`ThashUsuario`):** Indexación eficiente de usuarios mediante su NIF con gestión de colisiones y dispersión dinámica (`Hash.h`, `Hash.cpp`, `EntradaUsuario.h`, `EntradaUsuario.cpp`).
* **Gestión de Flota e Historial:** Organización de vehículos ordenados por matrícula en árbol balanceado (`std::map`), puntos de recarga (`PuntoRecarga.h`) y registro de trayectos (`Trayecto.h`).
* **Generación Visual de Mapas (PPM):** Exportación de imágenes rasterizadas en `mapaResultado.ppm` para la visualización de la flota y área cubierta (`img.h`, `img.cpp`).
* **Control del Sistema:** Lógica centralizada de negocio en la clase `Reanelcar` (`Reanelcar.h`, `Reanelcar.cpp`).

## Estructura Exacta de Archivos

```text
PR6/
├── CMakeLists.txt         # Configuración de compilación CMake
├── main.cpp               # Punto de entrada principal y carga de datos
├── Reanelcar.h / .cpp     # Controlador principal del sistema
├── Coche.h / .cpp         # Clase Vehículo (batería, estado, posición UTM)
├── Usuario.h / .cpp       # Datos del usuario e historial de trayectos
├── EntradaUsuario.h / .cpp# Entrada/Nodo para la Tabla Hash
├── Hash.h / .cpp          # Implementación de la Tabla Hash (ThashUsuario)
├── MallaRegular.h         # Plantilla (Template) de Malla Espacial 2D
├── Casilla.h              # Celdas de la Malla Regular Espacial
├── PuntoRecarga.h / .cpp  # Estaciones de recarga eléctrica
├── Trayecto.h / .cpp      # Registro de desplazamientos
├── UTM.h / .cpp           # Representación de Coordenadas UTM
├── fecha.h / .cpp         # Utilidades de gestión de fechas y horas
├── img.h / .cpp           # Módulo de renderizado y exportación de mapas PPM
├── coches_v2.csv          # Dataset de la flota de coches
├── usuarios1.csv          # Dataset de usuarios registrados
├── puntos_recarga.csv     # Dataset de puntos de recarga eléctrica
├── destino.csv            # Dataset de puntos de destino simulados
├── Documentación          # Archivo de documentación
├── html/                  # Documentación Doxygen generada en HTML
└── latex/                 # Documentación Doxygen generada en LaTeX
```

## Formato de Entrada de Datos

El sistema carga de forma masiva los datos iniciales mediante archivos de texto plano / CSV incluidos en la raiz:

- coches_v2.csv: Listado de coches (Matricula, Marca, Modelo, Coordenadas UTM, Bateria).
- usuarios1.csv: Registro de usuarios (NIF, Nombre, Direccion, Contrasena).
- puntos_recarga.csv: Ubicacion geografica de estaciones de recarga rapida.
- destino.csv: Puntos de destino simulados para el calculo de rutas.
## Documentacion del Codigo (Doxygen)

El proyecto cuenta con documentacion detallada generada a partir de los comentarios de cabecera y archivos fuente utilizando Doxygen.

La documentacion esta disponible en los siguientes formatos dentro de las carpetas comprimidas html/ y latex/

- HTML: Se puede consultar abriendo el archivo html/index.html en cualquier navegador web para acceder a los diagramas de clases, grafos de dependencias e indice de la API.
- LaTeX: Disponible en la carpeta latex/ para compilar la documentacion completa en formato PDF mediante pdflatex (ejecutando make dentro del directorio latex).

## Salida Visual (Mapa PPM)

Tras procesar la ubicacion de los vehiculos y las solicitudes de usuarios, el programa genera un mapa rasterizado en el archivo mapaResultado.ppm que permite visualizar la distribucion geografica de la flota y los puntos de demanda sobre el area cubierta por la malla regular.

## Autores

- David Fernandez Espejo - dfe00004@red.ujaen.es
- David Lorente Wagner - dlw00001@red.ujaen.es

Universidad de Jaen (UJA) - Grado en Ingenieria Informatica
