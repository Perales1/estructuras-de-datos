# Reanelcar - Sistema de Gestión de Vehículos Eléctricos Compartidos (Carsharing)

El proyecto PR2 implementa el sistema de gestión de vehículos eléctricos Reanelcar en C++17. Esta práctica está centrada en la eficiente gestión de usuarios y de la flota de vehículos, haciendo uso de estructuras de datos como Listas Doblemente Enlazadas y Vectores Dinámicos.

## Características Técnicas del Proyecto

* **Lista Doblemente Enlazada e Iterador (`ListaDEnlazada.h`, `Iterador.h`):** Gestión dinámica e iteración sobre los usuarios y la flota de vehículos.
* **Vector Dinámico (`VDinamico.h`):** Almacenamiento continuo con reasignación dinámica de memoria para soporte de operaciones auxiliares.
* **Gestión de Flota:** Modelado e integración de vehículos (`Coche.h`).
* **Gestión de Usuarios:** Almacenamiento de información de usuarios y su vinculación con el sistema (`Usuario.h`, `Usuario.cpp`).
* **Control del Sistema:** Lógica centralizada de negocio en la clase Reanelcar (`Reanelcar.h`, `Reanelcar.cpp`) para coordinar las estructuras de datos y realizar las operaciones principales.

## Estructura Exacta de Archivos (`PR2.zip`)

```text
PR2/
└── PR2/
    ├── CMakeLists.txt         # Configuración de compilación CMake
    ├── main.cpp                # Punto de entrada principal y pruebas
    ├── main2.cpp               # Pruebas secundarias y adicionales del sistema
    ├── Reanelcar.h / .cpp      # Controlador principal del sistema
    ├── Coche.h                 # Clase Vehículo y su estado
    ├── Usuario.h / .cpp        # Datos del usuario y gestión en el sistema
    ├── ListaDEnlazada.h        # Estructura de datos de Lista Doblemente Enlazada
    ├── Iterador.h              # Patrón iterador para la Lista Doblemente Enlazada
    ├── VDinamico.h             # Plantilla de Vector Dinámico
    ├── coches.csv              # Dataset de la flota de coches
    ├── usuarios1.csv           # Dataset de usuarios registrados
    ├── Documentacion          # Archivo de documentación
    ├── html.zip                # Documentación Doxygen comprimida en formato HTML
    └── latex.zip               # Documentación Doxygen comprimida en formato LaTeX
```

## Datasets Incluidos en el ZIP

* **`coches.csv`:** Contiene la información técnica y de estado de los vehículos eléctricos.
* **`usuarios1.csv`:** Contiene la información personal y de registro de los usuarios del sistema.

## Documentación del Código (Doxygen)

El proyecto cuenta con documentación detallada generada a partir de los comentarios de cabecera y archivos fuente utilizando Doxygen.

La documentación está disponible en los siguientes formatos dentro de las carpetas comprimidas `html.zip` y `latex.zip`:

- **HTML:** Se puede consultar abriendo el archivo `html/index.html` tras descomprimir `html.zip` en cualquier navegador web para acceder a los diagramas de clases, grafos de dependencias e índice de la API.
- **LaTeX:** Disponible tras descomprimir `latex.zip` en la carpeta `latex/` para compilar la documentación completa en formato PDF mediante `pdflatex` (ejecutando `make` dentro del directorio `latex`).

## Autores

* **David Fernández Espejo** - dfe00004@red.ujaen.es
* **David Lorente Wagner** - dlw00001@red.ujaen.es
* **Universidad de Jaén (UJA)** - Grado en Ingeniería Informática
