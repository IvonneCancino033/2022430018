
#  Laboratorio 6 — Algoritmo de Dijkstra (Camino Mínimo)

## 👩‍💻 Autor

**Nombre:** Ivonne Cancino  
**Asignatura:** Algoritmos y Estructura de Datos  
**Carrera:** Ingeniería Civil en Bioinformática  
**Universidad:** Universidad de Talca - Facultad de Ingeniería  

---

##  Descripción

Este laboratorio implementa el **algoritmo de Dijkstra** para encontrar los **caminos más cortos** desde un vértice origen hacia todos los demás en un **grafo dirigido y ponderado**, representado mediante **matrices de adyacencia**.

El programa permite al usuario:

-  Ingresar manualmente los valores de la matriz de distancias.  
-  Generar el **grafo original** con **Graphviz**.  
-  Calcular las **distancias mínimas** desde un vértice origen usando **Dijkstra**.  
-  Mostrar los vectores de estado (**S**, **VS**, **D**, **P**).  
-  Generar el **grafo con los caminos mínimos** (`grafo.png`).  
-  Validar correctamente todas las entradas del usuario.  

---

##  Estructura del proyecto

```
📂 Laboratorio6
│
├── algoritmo_Dijkstra.cpp        # Código fuente principal
│
├── README.md                     # Documento explicativo del laboratorio
│
└── 📂 output/                    # Archivos generados por el programa
    ├── algoritmo_Dijkstra        # Ejecutable compilado
    ├── grafo.dot                 # Archivo DOT generado por Graphviz
    ├── grafo.png                 # Imagen del grafo original
    └── grafo.txt                 # Código textual del grafo original
```

---

##  Requisitos del sistema

Para ejecutar correctamente este laboratorio, instala las siguientes herramientas en **Linux**:

```bash
sudo apt update
sudo apt install g++ graphviz eog
```
| Herramienta | Función |
|--------------|----------|
| **g++** | Compilador de C++ |
| **Graphviz** | Genera las imágenes del grafo (`grafo.png`) |
| **eog** | Abre automáticamente las imágenes generadas |

---

##  Compilación y ejecución

###  Compilación:
```bash
g++ algoritmo_Dijkstra.cpp -o output/algoritmo_Dijkstra -std=c++11
```

###  Ejecución:
```bash
./output/algoritmo_Dijkstra N
```
> Donde **N** es el número de nodos (entero positivo mayor que 2).

**Ejemplo:**
```bash
./output/algoritmo_Dijkstra 5
```

---

##  Menú del programa

Al ejecutar el programa, se despliega el siguiente menú interactivo:

```
========= MENÚ PRINCIPAL =========
1. Ingresar matriz de distancias
2. Mostrar matriz
3. Generar grafo original (Graphviz)
4. Ejecutar algoritmo de Dijkstra
5. Salir
6. Cargar matriz de ejemplo
Seleccione una opción:
```

###  Descripción de opciones

| Opción | Descripción |
|--------|--------------|
| **1** | Permite ingresar manualmente los pesos entre nodos (`0` o `-1` si no hay conexión). |
| **2** | Muestra la matriz ingresada en formato tabular. |
| **3** | Genera el grafo original (`grafo.png`) con los pesos. |
| **4** | Ejecuta el algoritmo de Dijkstra desde un vértice elegido y muestra los resultados. |
| **5** | Finaliza el programa y libera la memoria. |
| **6** | Carga una matriz de ejemplo para pruebas rápidas. |

---

##  Estructura del código

El programa utiliza una **matriz de adyacencia n×n** para representar los pesos entre vértices.

###  Funciones principales

| Función | Descripción |
|----------|--------------|
| `letraNodo(int i)` | Asigna una letra a cada vértice (`0→a`, `1→b`, etc.). |
| `inicializar_matriz(int**, int)` | Inicializa la matriz con valores `-1`. |
| `ingresar_matriz(int**, int)` | Permite al usuario ingresar los pesos entre vértices. |
| `mostrar_matriz(int**, int)` | Muestra la matriz completa en pantalla. |
| `generar_grafo_original(int**, int)` | Crea el grafo original con Graphviz. |
| `Algoritmo de dijkstra(int**, int, char)` | Implementa el algoritmo de Dijkstra desde el vértice origen. |
| `mostrar_resultados(...)` | Muestra los vectores de distancias y predecesores. |
| `generar_grafo_resultado(...)` | Genera el grafo con las aristas del camino mínimo. |
| `liberar_matriz(int**, int)` | Libera la memoria dinámica al finalizar el programa. |

---

##  Ejemplo de ejecución

### Entrada (5 nodos)
```
Ingrese los valores de la matriz de distancias (5x5):
(Use -1 cuando no exista conexión)
0 6 -1 1 -1
6 0 5 2 2
-1 5 0 -1 5
1 2 -1 0 1
-1 2 5 1 0
```

### Salida esperada
```
Ingrese índice del vértice origen (0-4): 0

--- Resultado final ---
Distancias mínimas desde a:
a → b = 3 | Camino: a → d → b
a → c = 7 | Camino: a → d → e → c
a → d = 1 | Camino: a → d
a → e = 2 | Camino: a → d → e
```

El programa generará automáticamente las imágenes:

-  **grafo.png** → Grafo original con todos los pesos.  
-  **grafo.png (actualizado)** → Grafo con los caminos mínimos desde el vértice origen (con aristas rojas).  

---

##  Explicación del algoritmo de Dijkstra

El algoritmo de **Dijkstra** calcula el **camino más corto** desde un vértice origen hacia todos los demás:

1. Inicializa las distancias con infinito (`∞`), excepto la del vértice origen (`0`).  
2. Selecciona el vértice con la menor distancia no visitado.  
3. Actualiza las distancias de sus vecinos según los pesos.  
4. Marca el vértice como visitado.  
5. Repite hasta visitar todos los vértices.  

El resultado final muestra las **distancias mínimas** y los **caminos recorridos** desde el vértice origen.

---

##  Validaciones implementadas
 Se verifica que **N > 2** antes de iniciar.  
 El menú valida que las entradas sean numéricas.  
 Se comprueba que la matriz haya sido ingresada antes de ejecutar Dijkstra.  
 Se valida el vértice elegido como origen.  
 Se libera toda la memoria antes de terminar.  
 Se generan correctamente los archivos `.dot`, `.txt` y `.png`.  

---

##  Limpieza y manejo de memoria

Antes de salir, el programa ejecuta:

```cpp
liberar_matriz(matriz, n);
```

Esto asegura que toda la memoria usada por la matriz sea liberada correctamente, evitando **fugas de memoria**.

---

##  Conclusión

Este programa cumple con los **objetivos del Laboratorio 6**, implementando el **algoritmo de Dijkstra** mediante **matrices**, validando correctamente los datos y generando visualizaciones gráficas del **grafo original** y de los **caminos mínimos** con **Graphviz**.

---

##  Archivos generados

| Archivo           | Descripción                                                             |
|-------------------|--------------------------------------------------------------------------|
| **grafo.dot**     | Archivo DOT que describe el grafo original en formato Graphviz.          |
| **grafo.txt**     | Versión textual del grafo.                                               |
| **grafo.png**     | Imagen del grafo (se actualiza al ejecutar Dijkstra con caminos mínimos).|
| **algoritmo_Dijkstra** | Ejecutable compilado del programa.                                  |
