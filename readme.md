
#  Laboratorio 9 — Tablas Hash y Resoluciòn de Colisiones

## 👩‍💻 Autor

**Nombre:** Ivonne Cancino  
**Asignatura:** Algoritmos y Estructura de Datos  
**Carrera:** Ingeniería Civil en Bioinformática  
**Universidad:** Universidad de Talca - Facultad de Ingeniería  

---

##  Descripción

Este laboratorio implementa  **tablas hash** con diferentes mètodos de **resoluciòn de colisiones** , permitiendo el ingreso y la bùsqueda de valores enteros. 

El programa permite al usuario:

-  Seleccionar el **mètodo de resoluciòn de colisiones** al iniciar el programa.  
      - Reasignaciòn Prueba Lineal (L).
      - Reasignaciòn Prueba Cuadràtica (C)
      - Doble Direcciòn Hash (D)
      - Encadenamiento (E)
- Insertar valores en la tabla hash.  
- Buscar valores en la tabla hash.  
- Mostrar el  **contenido de la tabla** y las **istas enlazadas** (si corresponde).  
- Indicar las posiciones iniciales, colisiones y desplazamientos finales durante insercion o busqueda.  

---
##  Estructura del proyecto

```
📂 Laboratorio_9
 ┣ 📜 metodos_busqueda.cpp      Código fuente principal
 ┣ 📜 README.md                Documento explicativo
 ┗ 📂 output                     Ejecutables compilados
```

---
##  Requisitos del sistema

Para ejecutar correctamente este laboratorio, instala las siguientes herramientas en **Linux**:

```bash
sudo apt update
sudo apt install g++ (compilador de C++)
```
---

##  Compilación y ejecución

###  Compilación:
```bash
g++ hash_main.cpp -o hash -std=c++11
```

###  Ejecución:
```bash
./metodos_busqueda {L|C|D|E}
```
> Donde **{L|C|D|E}** selecciona el mètodo de resolucion de colisiones.

**Ejemplo:**
```
./metodos_busqueda L
```

---
##  Menú del programa

Al ejecutar el programa, se despliega el siguiente menú interactivo:

```
========= MENÚ =========
Mètodo: (Se menciona el escogido por el usuario)

1) Insertar valor
2) Buscar valor
0) Salir
========================
Seleccione una opción:
```
###  Descripción de opciones

| Opción | Descripción |
|--------|--------------|
| **1** | Permite ingresar un valor entero en la tabla hash. |
| **2** | Permite buscar un valor en la tabla hash, mostrando colisiones y desplazamientos. |
| **3** | Finaliza el programa. 
---
##  Estructura del código

El programa utiliza:
- Un **arreglo de tamaño N = 20** para almacenar los valores (tabla hash).
- **Listas enlazadas** para el mètodo de encadenamiento.
- Diferentes funciones de insercòn y bùsqueda segùn el mètodo elegido.

###  Funciones principales

| Función | Descripción |
|----------|--------------|
| `H(int k)` | Funciòn hash principal (mòdulo o divisòn). |
| `H2(int k)` | Función hash secundaria para doble hashing. |
| `Reasignacion_prueba_lineal` | Inserta un valor usando desplazamiento lineal en caso de colisión. |
| `Reasignacion_prueba_Cuadratica` | Inserta un valor usando desplazamiento cuadrático. |
| `Reasignacion_doble_direccion` | Inserta un valor usando doble dirección hash. |
| `Encandenamiento` |Inserta un valor en listas enlazadas si hay colisión. |
| `Buscar_Lineal` | Busca un valor usando prueba lineal. |
| `Buscar_cuadratica` |Busca un valor usando prueba cuadrática. |
| `Buscar_doble` |Busca un valor usando doble hashing. |
| `Buscar_Encadenamiento` |Busca un valor en las listas enlazadas. |
| `imprimirArreglo` |Muestra la tabla hash. |
| `imprimirListas` |Muestra las listas enlazadas (solo método E). |

---
##  Ejemplo de ejecución — Mètodo Lineal

### Entrada 
```
Valor a insertar: 25
Valor a insertar: 45
Valor a insertar: 65
```
### Salida esperada 
```
Insertado sin colisión en posición 5
Colisión en 5 — aplicando REASIGNACIÓN PRUEBA LINEAL...
Desplazado a posición final 6
```
### Tabla hash
```
[5] 25
[6] 45
[7] 65
```
##  Explicación del algoritmo de Prim

El algoritmo de **Prim** construye un **árbol de expansión mínima (MST)** de la siguiente manera:

1. **Prueba Lineal (L)**: Se busca la siguiente posición libre secuencialmente.  
2. **Prueba Cuadrática (C)**: Se desplaza siguiendo un patrón cuadrático (i^2). 
3. **Doble Dirección Hash (D)**: Se combina la función hash principal y secundaria para calcular saltos. 
4. **Encadenamiento (E)**: Se forman listas enlazadas en cada índice con colisiones.

---
##  Validaciones implementadas

-  La tabla inicializa todas las posiciones como vacías. 
- Se comprueba si la tabla está llena antes de insertar. 
- Se indica claramente cada colisión y desplazamiento.
- Las búsquedas reportan posición y pasos hasta encontrar o determinar que no existe. 
- En el encadenamiento, los nodos se agregan al final de la lista.

---
##  Conclusión

Este programa cumple con todos los **objetivos del Laboratorio 9**, permitiendo:
- Comparar los distintos métodos de resolución de colisiones.
- Visualizar el comportamiento de las inserciones y búsquedas.
- Mostrar colisiones, desplazamientos y contenido de la tabla.
---