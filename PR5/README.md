# Reanelcar — Sistema de Gestión de Carsharing

El proyecto **PR5** implementa el sistema de gestión de vehículos eléctricos **Reanelcar** en **C++17**. Esta práctica está centrada en la integración y análisis de eficiencia de la Tabla Hash (`ThashUsuario`) para la gestión de usuarios, así como el manejo de trayectos, puntos de recarga y geolocalización UTM.

---

## Autores y Afiliación

* **David Fernández Espejo** (`dfe00004@red.ujaen.es`)
* **David Lorente Wagner** (`dlw00001@red.ujaen.es`)
* **Institución:** Universidad de Jaén (UJA)

---

## Características Técnicas Reales del Proyecto

* **Tabla de Dispersión Personalizada (`ThashUsuario`):** Implementación propia de tabla hash para la búsqueda y gestión óptima de usuarios mediante su NIF (`Hash.h`, `Hash.cpp`, `EntradaUsuario.h`, `EntradaUsuario.cpp`).
* **Documento de Análisis Algorítmico:** Incluye el análisis teórico de dispersión en el archivo `analisis_Thash.md`.
* **Gestión de Flota y Puntos de Recarga:** Modelado de vehículos (`Coche.h`), estaciones de recarga (`PuntoRecarga.h`) y registro de trayectos (`Trayecto.h`).
* **Geolocalización UTM:** Representación de ubicaciones geográficas mediante coordenadas UTM (`UTM.h`).
* **Control del Sistema:** Lógica centralizada de negocio en la clase `Reanelcar` (`Reanelcar.h`, `Reanelcar.cpp`).

---

## Estructura Exacta de Archivos (`PR5.zip`)

```text
PR5/
├── CMakeLists.txt         # Configuración de compilación CMake
├── main.cpp               # Punto de entrada principal
├── main2.cpp              # Punto de entrada alternativo/pruebas
├── Reanelcar.h / .cpp     # Controlador principal del sistema
├── Coche.h / .cpp         # Clase Vehículo y su estado
├── Usuario.h / .cpp       # Datos del usuario y su historial
├── EntradaUsuario.h / .cpp# Entrada/Nodo para la Tabla Hash
├── Hash.h / .cpp          # Implementación de la Tabla Hash (ThashUsuario)
├── PuntoRecarga.h / .cpp  # Estaciones de recarga eléctrica
├── Trayecto.h / .cpp      # Registro de viajes realizado por los usuarios
├── UTM.h                  # Clase para coordenadas geográficas UTM
├── fecha.h / .cpp         # Utilidades de gestión de fechas y horas
├── analisis_Thash.md      # Informe de análisis teórico de la Tabla Hash
├── coches_v2.csv          # Dataset de la flota de coches
├── usuarios1.csv          # Dataset de usuarios
├── puntos_recarga.csv     # Dataset de puntos de recarga
├── Documentación          # Archivo de documentación
├── html/                  # Documentación Doxygen generada en HTML
└── latex/                 # Documentación Doxygen generada en LaTeX
```

*(Nota: No existen archivos de malla regular ni librerías PPM/img en este zip; las estructuras principales giran en torno a la Tabla Hash, vectores, listas y la gestión de Reanelcar).*

---

## Datasets Incluidos en el ZIP

* `coches_v2.csv`: Contiene la información de los vehículos.
* `usuarios1.csv`: Contiene la información de los usuarios registrados.
* `puntos_recarga.csv`: Ubicación de los puntos de recarga eléctrica.
