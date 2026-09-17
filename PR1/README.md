# Práctica 1 - Estructura de Datos

El proyecto PR1 implementa las bases de la gestión de memoria e inserción eficiente mediante la plantilla de clase de Vector Dinámico (`VDinamico.h`) en C++. La práctica está estructurada en dos partes o subproyectos (`PR1_1EEDD` y `PR1_2EEDD`) para probar de forma incremental el comportamiento del vector dinámico y sus distintas operaciones.

## Características Técnicas del Proyecto

* **Vector Dinámico (`VDinamico.h`):** Implementación de una plantilla (template) de vector con capacidad de redimensionamiento automático de memoria según las necesidades de inserción/borrado.
* **Separación de Proyectos (`PR1_1EEDD` y `PR1_2EEDD`):** 
  * `PR1_1EEDD`: Primera fase/subproyecto para verificación y pruebas básicas del vector dinámico.
  * `PR1_2EEDD`: Segunda fase/subproyecto con algoritmos avanzados o casos de prueba adicionales sobre la misma estructura.
* **Sistema de Compilación CMake:** Cada subproyecto cuenta con su propio archivo `CMakeLists.txt` para su compilación e integración de forma independiente.

## Estructura Exacta de Archivos (`PR1EEDD.zip`)

```text
PR1EEDD/
├── IMPORTANTE.txt          # Indicaciones y notas importantes de la práctica
├── PR1_1EEDD/              # Subproyecto Parte 1
│   ├── CMakeLists.txt      # Configuración de compilación CMake para PR1_1
│   ├── main.cpp            # Punto de entrada y pruebas de la Parte 1
│   └── VDinamico.h         # Plantilla del Vector Dinámico (Parte 1)
└── PR1_2EEDD/              # Subproyecto Parte 2
    ├── CMakeLists.txt      # Configuración de compilación CMake para PR1_2
    ├── main.cpp            # Punto de entrada y pruebas de la Parte 2
    └── VDinamico.h         # Plantilla del Vector Dinámico (Parte 2)
```

## Contenido de las Partes

1. **`PR1_1EEDD`:** Se implementan los métodos fundamentales del vector dinámico (constructores, destructor, operador de asignación, reasignación de capacidad y acceso a elementos).
2. **`PR1_2EEDD`:** Ampliación y pruebas adicionales para asegurar el correcto funcionamiento, gestión eficiente del espacio de memoria y rendimiento en operaciones sobre el vector dinámico.

## Autores

* **David Fernández Espejo** - dfe00004@red.ujaen.es
* **David Lorente Wagner** - dlw00001@red.ujaen.es
* **Universidad de Jaén (UJA)** - Grado en Ingeniería Informática
