# Reanelcar - Sistema de Gestión de Vehículos Eléctricos Compartidos (Carsharing)

El proyecto PR3 implementa el sistema de gestión de vehículos eléctricos Reanelcar en C++17. Esta práctica está centrada en la eficiente gestión de usuarios, puntos de recarga y la flota de vehículos, haciendo uso de estructuras de datos avanzadas como Árboles AVL, Listas Doblemente Enlazadas y Vectores Dinámicos.

## Características Técnicas del Proyecto

* **Árbol AVL (`AVL.h`):** Búsqueda, inserción y balanceo eficiente de la flota de vehículos por su identificador/matrícula ($O(\log n)$).
* **Lista Doblemente Enlazada e Iterador (`ListaDEnlazada.h`, `Iterador.h`):** Gestión dinámica e iteración sobre los usuarios y estaciones de recarga.
* **Vector Dinámico (`VDinamico.h`):** Almacenamiento continuo con reasignación dinámica de memoria para soporte de operaciones auxiliares.

* **Gestión de Flota y Puntos de Recarga:** Modelado e integración de vehículos (`Coche.h`, `Coche.cpp`) y estaciones de recarga eléctrica (`PuntoRecarga.h`, `PuntoRecarga.cpp`).
* **Gestión de Usuarios:** Almacenamiento de información de usuarios y su vinculación con el sistema (`Usuario.h`, `Usuario.cpp`).
* **Control del Sistema:** Lógica centralizada de negocio en la clase Reanelcar (`Reanelcar.h`, `Reanelcar.cpp`) para coordinar las estructuras de datos y realizar las operaciones principales.

## Estructura Exacta de Archivos (`PR3.zip`)

```text
PR3/
├── CMakeLists.txt         # Configuración de compilación CMake (PR3AVL)
├── main.cpp               # Punto de entrada principal y pruebas
├── Reanelcar.h / .cpp     # Controlador principal del sistema
├── Coche.h / .cpp         # Clase Vehículo y su estado
├── Usuario.h / .cpp       # Datos del usuario y gestión en el sistema
├── PuntoRecarga.h / .cpp  # Estaciones de recarga eléctrica
├── AVL.h                  # Estructura de datos de Árbol AVL balanceado
├── ListaDEnlazada.h       # Estructura de datos de Lista Doblemente Enlazada
├── Iterador.h             # Patrón iterador para la Lista Doblemente Enlazada
├── VDinamico.h            # Plantilla de Vector Dinámico
├── coches.csv             # Dataset de la flota de coches
├── usuarios1.csv          # Dataset de usuarios registrados
├── Documentación          # Archivo de documentación
├── html.zip               # Documentación Doxygen comprimida en formato HTML
└── latex.zip              # Documentación Doxygen comprimida en formato LaTeX
```

## Datasets Incluidos en el ZIP

* **`coches.csv`:** Contiene la información técnica y de estado de los vehículos eléctricos.
* **`usuarios1.csv`:** Contiene la información personal y de registro de los usuarios del sistema.

## Documentacion del Codigo (Doxygen)

El proyecto cuenta con documentacion detallada generada a partir de los comentarios de cabecera y archivos fuente utilizando Doxygen.

La documentacion esta disponible en los siguientes formatos dentro de las carpetas comprimidas `html/` y `latex/`:

- **HTML:** Se puede consultar abriendo el archivo `html/index.html` en cualquier navegador web para acceder a los diagramas de clases, grafos de dependencias e indice de la API.
- **LaTeX:** Disponible en la carpeta `latex/` para compilar la documentacion completa en formato PDF mediante `pdflatex` (ejecutando `make` dentro del directorio `latex`).

## Autores

* **David Fernández Espejo** - dfe00004@red.ujaen.es
* **David Lorente Wagner** - dlw00001@red.ujaen.es
* **Universidad de Jaén (UJA)** - Grado en Ingeniería Informática
