/*
 * g++ prim_matriz_menu.cpp -o prim -std=c++11
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>   // Para usar INT_MAX
#include <limits>    // Para validación de entradas con cin
using namespace std;

// FUNCIÓN letraNodo: Devuelve una letra correspondiente al índice del nodo, por ejemplo: 0 -> 'a', 1 -> 'b', 2 -> 'c'.
char letraNodo(int i) {
    return 'a' + i;  
}

// FUNCIÓN inicializar_matriz: Crea una matriz NxN con valor -1 en todas sus posiciones y representa que inicialmente no hay conexión entre nodos.
void inicializar_matriz(int **matriz, int n) {
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
            matriz[fila][col] = -1;
        }
    }
}

// FUNCIÓN mostrar_matriz: Imprime la matriz de adyacencia completa en pantalla
void mostrar_matriz(int **matriz, int n) {
    cout << endl;
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
            cout << matriz[fila][col] << "\t";
        }
        cout << endl;
    }
}

// FUNCIÓN ingresar_matriz: Permite al usuario ingresar manualmente los valores de la matriz de distancias (pesos de las aristas). El usuario puede ingresar: Un número positivo -> peso entre nodos y  0 o -1 -> sin conexión.
void ingresar_matriz(int **matriz, int n) {
    cout << "\nIngrese los valores de la matriz de distancias (" << n << "x" << n << "):\n";
    cout << "(Use 0 o -1 cuando no exista conexión entre nodos)\n";
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
            cin >> matriz[fila][col];
        }
    }
}

// FUNCIÓN generar_grafo_matriz_original: El grafo muestra todos los nodos y aristas originales con sus pesos.
void generar_grafo_matriz_original(int **matriz, int n) {
    ofstream fp("grafo.txt");
    fp << "graph G {\n";
    fp << "rankdir=LR;\n";
    fp << "node [style=filled, fillcolor=lightgreen, fontname=\"Arial\"];\n";

    // Crear nodos
    for (int i = 0; i < n; i++) {
        fp << letraNodo(i) << " [label=\"" << letraNodo(i) << "\"];\n";
    }

    // Crear aristas (solo una por cada par i < j)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matriz[i][j] > 0) {
                fp << letraNodo(i) << " -- " << letraNodo(j)
                << " [label=\"" << matriz[i][j] << "\", color=black, penwidth=1.5];\n";
            }
        }
    }

    fp << "}\n";
    fp.close();
    // Generar imagen del grafo con Graphviz
    system("dot -Tpng grafo.txt -o grafo.png");
    system("eog grafo.png &");
    cout << "\nGrafo original generado como 'grafo.png'.\n";
}

// FUNCIÓN generar_grafo_arbol_minimo: Crea el grafo que representa el Árbol de Expansión Mínimo (MST), obtenido mediante el algoritmo de Prim.
void generar_grafo_arbol_minimo(int **matriz, int parent[], int n) {
    ofstream fp("mst.txt");
    fp << "graph MST {\n";
    fp << "rankdir=LR;\n";
    fp << "node [style=filled, fillcolor=lightblue, fontname=\"Arial\"];\n";

    // Nodos del árbol
    for (int i = 0; i < n; i++) {
        fp << letraNodo(i) << " [label=\"Nodo " << letraNodo(i) << "\"];\n";
    }

    // Aristas seleccionadas por el algoritmo de Prim
    for (int i = 1; i < n; i++) {
        int u = parent[i];
        fp << letraNodo(u) << " -- " << letraNodo(i)
        << " [label=\"" << matriz[u][i]
        << "\", color=red, penwidth=2.5];\n";
    }

    fp << "}\n";
    fp.close();
    // Generar imagen del árbol mínimo
    system("dot -Tpng mst.txt -o mst.png");
    system("eog mst.png &");
    cout << "\n Grafo del camino Mínimo generado como 'mst.png'.\n";
}


//FUNCIÓN prim: Implementa el algoritmo de Prim para encontrar el Árbol de Expansión Mínimo (MST) a partir de la matriz de adyacencia.
void prim(int **matriz, int n, int parent []) {
    int *key = new int[n]; // Pesos mínimos conocidos
    bool *inU = new bool[n]; // Si el nodo ya está en el MST

    // Inicialización
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        inU[i] = false;
        parent[i] = -1;
    }

    key[0] = 0; // inicio desde el nodo 0
     // Construcción del MST
    for (int count = 0; count < n - 1; count++) {
        int minKey = INT_MAX;
        int u = -1;

        // buscar el nodo con la menor clave
        for (int v = 0; v < n; v++) {
            if (!inU[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        inU[u] = true;

        // actualizar claves de los nodos adyacentes
        for (int v = 0; v < n; v++) {
            if (matriz[u][v] > 0 && !inU[v] && matriz[u][v] < key[v]) {
                parent[v] = u;
                key[v] = matriz[u][v];
            }
        }
    }

    // Mostrar conjunto L (las aristas seleccionadas)
    cout << "\nConjunto L (aristas seleccionadas):\n";
    int total = 0;
    for (int i = 1; i < n; i++) {
        cout << letraNodo(parent[i]) << " - " << letraNodo(i)
            << "  peso: " << matriz[parent[i]][i] << endl;
        total += matriz[parent[i]][i];
    }
    cout << "Costo total del graFo mínimo: " << total << endl;

    // Generar grafo del MST
    generar_grafo_arbol_minimo(matriz, parent, n);

    delete[] key;
    delete[] inU;
}
// FUNCIÓN liberar_matriz: Libera la memoria dinámica asociada a la matriz NxN.
void liberar_matriz(int **matriz, int n) {
    if (matriz) {
        for (int i = 0; i < n; i++) {
            delete[] matriz[i];  // Libera cada fila
        }
        delete[] matriz;  // Libera el arreglo de punteros
        cout << "\n Memoria de la matriz liberada correctamente.\n";
    }
}

//FUNCIÓN main: Controla el flujo del programa mediante un menú interactivo.
int main(int argc, char **argv) {
    // Validar parámetro N
    if (argc < 2) {
        cout << "Uso: ./prim N\n";
        return -1;
    }

    int n = atoi(argv[1]);
    if (n < 3) {
        cout << "El número de nodos debe ser mayor que 2.\n";
        return -1;
    }

    // Crear matriz NxN
    int **matriz = new int*[n];
    for (int i = 0; i < n; i++)
        matriz[i] = new int[n];

    int *parent = new int[n]; 
    bool matriz_ingresada = false;
    int opcion;

    inicializar_matriz(matriz, n);

    // Menú principal
    do {
        cout << "\n------- MENÚ PRINCIPAL --------\n";
        cout << "1. Ingresar matriz de distancias\n";
        cout << "2. Mostrar matriz\n";
        cout << "3. Generar grafo original (Graphviz)\n";
        cout << "4. Ejecutar algoritmo de Prim\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        

          // Validación de entrada del menú
        if (!(cin >> opcion)) {
            cout << "\n Entrada inválida. Por favor, ingrese un número entre 1 y 5.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue;
        }
        // Control de opciones
        switch (opcion) {
            case 1:
                ingresar_matriz(matriz, n);
                matriz_ingresada = true;
                break;
            case 2:
                if (matriz_ingresada)
                    mostrar_matriz(matriz, n);
                else
                    cout << "Debe ingresar la matriz primero.\n";
                break;
            case 3:
                if (matriz_ingresada)
                    generar_grafo_matriz_original(matriz, n);
                else
                    cout << "Ingrese la matriz antes de generar el grafo.\n";
                break;
            case 4:
                if (matriz_ingresada) {
                    prim(matriz, n, parent);
                } else {
                    cout << "Ingrese la matriz antes de ejecutar Prim.\n";
                }
                break;
            
        }

    } while (opcion != 5);
    // Liberar memoria antes de salir
    liberar_matriz(matriz, n);

    return 0;
}
