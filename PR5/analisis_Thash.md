# **Análisis de tablas de dispersión**

* *David Fernández Espejo*
* *David Lorente Wagner*

## **Tamaño de tabla: 23687**

| Función        | Máximo de colisiones | Factor de carga | Promedio de colisiones | Inserciones con > 10 colisiones |
|----------------|:--------------------:|:---------------:|:----------------------:|:-------------------------------:|
| **VARIANTE**   |          8           |      0.65       |        0.306269        |                0                |
| **CUADRATICA** |          9           |      0.65       |        0.328967        |                0                |
| **DOBLE**      |          9           |      0.65       |        0.30367         |                0                |

---

## **Tamaño de tabla: [21647]**

| Función        | Máximo de colisiones | Factor de carga | Promedio de colisiones | Inserciones con > 10 colisiones |
|----------------|:--------------------:|:---------------:|:----------------------:|:-------------------------------:|
| **VARIANTE**   |          11          |      0.68       |        0.354765        |                1                |
| **CUADRATICA** |          9           |      0.68       |        0.367163        |                0                |
| **DOBLE**      |          9           |      0.68       |        0.335966        |                0                |

---

## **Justificación de la configuración elegida**

Hemos optado por la configuración con dispersión tipo "DOBLE" y factor de carga 0.65, que tiene un promedio de
colisiones
de 0.30367 y el menor número máximo de colisiones de 9. Además es una configuración que no presenta inserciones con más
de 10 colisiones. Otra opción posible sería la configuración con dispersión tipo "VARIANTE", pero tiene un promedio de
colisiones mayor que el de la configuración "DOBLE" siendo este de 0.306269. Además, la configuración "VARIANTE"
presenta un número elevado de colisiones cuando el factor de carga es tan sólo de 0.68.

## **Prueba de Rendimiento**

Realizando múltiples pruebas de rendimiento con la búsqueda de la tabla hash con configuración de dispersión tipo "
DOBLE"
frente a la búsqueda mediante la lista doblemente enlazada, en el total de los casos es mucho más veloz la búsqueda
mediante la tabla hash que mediante la lista doblemente enlzada, con unos tiempo entre 24 y 40 milisegundos frente a
tiempos
superiores a los 2000 milisegundos usando la lista doblemente enlazada.