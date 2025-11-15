#  Laboratorio 8 --- Métodos de Ordenamiento y Medición de Tiempos

## 👩‍💻 Autor

**Nombre:** Ivonne Cancino\
**Asignatura:** Algoritmos y Estructura de Datos\
**Carrera:** Ingeniería Civil en Bioinformática\
**Universidad:** Universidad de Talca - Facultad de Ingeniería

--------------------------------------------------------------------

##  Descripción

Este laboratorio implementa y compara el rendimiento de **cinco métodos
de ordenamiento**, midiendo sus tiempos de ejecución utilizando la
librería **`<chrono>`**.

Métodos implementados:

-   🔵 Burbuja menor y mayor
-   🟢 Inserción
-   🟣 Selección
-   🟡 Shellsort
-   🔴 Quicksort (con pila manual)

El programa permite al usuario:
```
-    Medir el tiempo que demora cada metodo.
-    Elegir si desea ver o no el contenido de los arreglos.
-   Definir el tamaño del arreglo aleatorio (*N*) desde la línea de
    comandos.
```
------------------------------------------------------------------------

## Estructura del proyecto

    📂 laboratorio 8
     ┣ 📜 metodos_ordenamiento.cpp
     ┣ 📜 README.md
     ┗ 📂 output

------------------------------------------------------------------------

##  Requisitos

Instalar g++ en Linux:

``` bash
sudo apt update
sudo apt install g++
```

------------------------------------------------------------------------

##  Compilación y ejecución

### Compilar:

``` bash
g++ metodos_ordenamiento.cpp -o metodos_ordenamiento -std=c++11
```

### Ejecutar:

    ./metodos_ordenamiento N s|n

### Parámetros:

  Parámetro   Significado
  ----------- -----------------------------------
  **N**       Cantidad de elementos del arreglo,
  **s**       Mostrar los arreglos y 
  **n**       No mostrar arreglos, solo tiempos

Ejemplos:

    ./metodos_ordenamiento 10000 n
    ./metodos_ordenamiento 10 s

------------------------------------------------------------------------

##  Funcionamiento del programa

1.  Genera un arreglo aleatorio de tamaño **N**.
2.  Copia el arreglo para que cada método trabaje con los mismos
    valores.
3.  Mide el tiempo de ejecución de cada ordenamiento usando `chrono`.
4.  Si el usuario elige `s`, muestra los arreglos ordenados por cada
    método.
5.  Imprime una tabla de tiempo:

```
    Metodo        | Tiempo
    -----------------------------------------
    Burbuja       | 280 milisegundos
    Burbuja mayor | 270 milisegundos
    Insercion     | 120 milisegundos
    Seleccion     | 150 milisegundos
    Shellsort     | 7.5 milisegundos
    Quicksort     | 0.3 milisegundos
    -----------------------------------------
```

------------------------------------------------------------------------

## Métodos implementados
```
 🔵 Burbuja menor (mètodo ordenamiento interno complejidad cuadràtico)

El más pequeño "flota" hacia el inicio del arreglo.

🔵 Burbuja mayor (mètodo ordenamiento interno complejidad cuadràtico)

El más grande "se hunde" hacia el final del arreglo.

🟢 Inserción (mètodo ordenamiento interno complejidad cuadràtico)

Inserta cada elemento en su posición ordenada.

🟣 Selección (mètodo ordenamiento interno complejidad cuadràtico)

Busca el mínimo del subarreglo y lo ubica en su posición final.

🟡 Shellsort (mètodo ordenamiento interno complejidad logarìtmica)

Ordenamiento mejorado basado en inserciones con saltos decrecientes.

🔴 Quicksort (mètodo ordenamiento interno complejidad logarìtmica)

Versión sin recursión que usa dos pilas para manejar los subarreglos.
```
------------------------------------------------------------------------

## Ejemplo de salida con `N = 10` y `s`

    a[0]=4499 a[1]=2634 ... a[9]=1515
    -----------------------------------------
    Metodo        | Tiempo
    -----------------------------------------
    Burbuja       | 0 milisegundos
    Burbuja mayor | 0 milisegundos
    Insercion     | 0 milisegundos
    Seleccion     | 0 milisegundos
    Shellsort     | 0.002 milisegundos
    Quicksort     | 0.001 milisegundos
    -----------------------------------------
    Burbuja a[0]=110 a[1]=210 ... a[9]=4499
    Insercion a[0]=110 a[1]=210 ... a[9]=4499
    Selection a[0]=110 ... a[9]=4499
    Shellsort a[0]=110 ... a[9]=4499
    Quicksort a[0]=110 ... a[9]=4499

------------------------------------------------------------------------

## Validaciones del programa
```
-Verifica que N > 0
-Verifica que el usuario entregue s o n
-Siempre usa el mismo arreglo original para todos los métodos
-Libera memoria (`delete[]`)
-Mide el tiempo usando `chrono` en milisegundos
```
------------------------------------------------------------------------

## Conclusión

Este laboratorio permite comparar el rendimiento de distintos mètodos
de ordenamiento.

Se observa que:

```
-   Burbuja, Inserción y Selección son muy lentos para valores grandes
    (O(n²)).
-   Shellsort mejora significativamente los tiempos.
-   Quicksort es el método más eficiente (O(n log n)).
```
------------------------------------------------------------------------