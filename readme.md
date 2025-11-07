#  Laboratorio 7 — Árbol de Expansión Mínimo (Algoritmo de Prim)

## 👩‍💻 Autor

**Nombre:** Ivonne Cancino  
**Asignatura:** Algoritmos y Estructura de Datos  
**Carrera:** Ingeniería Civil en Bioinformática  
**Universidad:** Universidad de Talca - Facultad de Ingeniería  

---

##  Descripción

Este laboratorio implementa el **algoritmo de Prim** para encontrar el **grafo abarcador de costo mínimo (MST)** en un **grafo no dirigido y ponderado**, utilizando **matrices de adyacencia**.

El programa permite al usuario:

-  Ingresar manualmente los valores de la matriz de distancias.  
-  Generar el **grafo original** con **Graphviz**.  
-  Calcular el **camino mínimo de expansión (MST)** usando el algoritmo de **Prim**.  
-  Mostrar el contenido del **conjunto L** (aristas seleccionadas y pesos).  
-  Generar el **grafo del árbol mínimo (mst.png)**.  
-  Validar correctamente todas las entradas del usuario.  

---

##  Estructura del proyecto

```
📂 Laboratorio7_Prim
│
├── 📂 src/                      # Código fuente del programa
│   └── algoritmo_prim.cpp       # Implementación del algoritmo de Prim
│
├── 📂 bin/                      # Ejecutables generados al compilar
│   └── algoritmo_prim           # Ejecutable principal del programa
│
├── 📂 output/                   # Archivos generados por el programa
│   ├── grafo.txt                # Código DOT del grafo original
│   ├── grafo.png                # Imagen del grafo original
│   ├── mst.txt                  # Código DOT del camino mínimo
│   └── mst.png                  # Imagen del grafo de expansión mínima
│
└── 📜 README.md                 # Documento explicativo del laboratorio

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
| **Graphviz** | Genera las imágenes de los grafos (`grafo.png`, `mst.png`) |
| **eog (Eye of GNOME)** | Abre automáticamente las imágenes generadas |

---

## Compilación y ejecución

###  Compilación:
```bash
g++ src/algoritmo_prim.cpp -o bin/algoritmo_prim -std=c++11

```

###  Ejecución:
```bash
./algoritmo_prim 
```
> Donde **N** es el número de nodos (entero positivo mayor que 2).

**Ejemplo:**
```bash
./algoritmo_prim 3
```

---

##  Menú del programa

Al ejecutar el programa, se despliega el siguiente menú interactivo:

```
========= MENÚ PRINCIPAL =========
1. Ingresar matriz de distancias
2. Mostrar matriz
3. Generar grafo original (Graphviz)
4. Ejecutar algoritmo de Prim
5. Salir
Seleccione una opción:
```

###  Descripción de opciones

| Opción | Descripción |
|--------|--------------|
| **1** | Permite ingresar manualmente los pesos entre nodos (`0` o `-1` si no hay conexión). |
| **2** | Muestra la matriz ingresada en formato tabular. |
| **3** | Genera el grafo original (`grafo.png`) con los pesos. |
| **4** | Ejecuta el algoritmo de Prim, mostrando el conjunto **L** y generando el grafo del camino mínimo (`mst.png`). |
| **5** | Finaliza el programa y libera la memoria. |

---

##  Estructura del código

El programa utiliza una **matriz de adyacencia n×n** para representar los pesos entre nodos.

###  Funciones principales

| Función | Descripción |
|----------|--------------|
| `letraNodo(int i)` | Asigna una letra a cada nodo (`0→a`, `1→b`, etc.). |
| `inicializar_matriz(int**, int)` | Inicializa la matriz con valores `-1`. |
| `ingresar_matriz(int**, int)` | Permite al usuario ingresar los pesos entre nodos. |
| `mostrar_matriz(int**, int)` | Muestra la matriz completa en pantalla. |
| `generar_grafo_matriz_original(int**, int)` | Crea el grafo original con Graphviz. |
| `prim(int**, int, int[])` | Implementa el algoritmo de Prim para generar el Grafo mínimo. |
| `generar_grafo_arbol_minimo(int**, int[], int)` | Genera el grafo del camino mínimo (MST). |
| `liberar_matriz(int**, int)` | Libera la memoria al finalizar el programa. |

---

##  Ejemplo de ejecución — Conjunto L

### Entrada (3 nodos)
```
Ingrese los valores de la matriz de distancias (3x3):
(Use 0 o -1 cuando no exista conexión)
0 5 8
5 0 2
8 2 0
```

### Salida esperada
```
Conjunto L (aristas seleccionadas):
b - c  peso: 2
a - b  peso: 5
Costo total del camino mínimo: 7
```

El programa generará automáticamente las imágenes:

-  **grafo.png** → Grafo original con todos los pesos.  
-  **mst.png** → Grafo de expansión mínima (resultado de Prim).  

---

##  Explicación del algoritmo de Prim

El algoritmo de **Prim** construye un **Grafo de expansión mínima (MST)** de la siguiente manera:

1. Comienza desde un nodo inicial.  
2. Selecciona la **arista de menor peso** que conecta un nodo dentro del Grafo con uno fuera.  
3. Repite el proceso hasta incluir todos los nodos.  
4. El resultado final es el conjunto **L**, que contiene las aristas del Grafo de costo mínimo.  

---

##  Validaciones implementadas

 Se verifica que **N > 2** antes de iniciar.  
 El menú valida que las entradas sean numéricas.  
 Se comprueba que la matriz haya sido ingresada antes de generar grafos o ejecutar Prim.  
 Se libera toda la memoria antes de terminar.  
 Se generan correctamente los archivos `.txt` y `.png`.  

---

## 🧹 Limpieza y manejo de memoria

Antes de salir, el programa ejecuta:

```cpp
liberar_matriz(matriz, n);
```

Esto asegura que toda la memoria usada por la matriz sea liberada correctamente, evitando **fugas de memoria**.

---

##  Conclusión

Este programa cumple con todos los **objetivos del Laboratorio 7**, aplicando el **algoritmo de Prim** mediante **matrices**, validando correctamente los datos, y generando visualizaciones gráficas del **grafo original** y del **grafo de costo mínimo** usando **Graphviz**.

---

##  Ejemplo de flujo de trabajo con Git

```bash
git init
git add .
git commit -m "Laboratorio 7 completado"
git branch -M main
git push -u origin main
```

---

##  Imágenes generadas
| Archivo       | Descripción                                                             |
| ------------- | ----------------------------------------------------------------------- |
| **grafo.txt** | Archivo DOT que representa el grafo original.                           |
| **grafo.png** | Imagen del grafo original generada con Graphviz.                        |
| **mst.txt**   | Archivo DOT del grafo de Expansión Mínimo.                              |
| **mst.png**   | Imagen del grafo de Expansión Mínimo (resultado del algoritmo de Prim). |
