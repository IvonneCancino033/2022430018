#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <limits>
using namespace std;

// FUNCIONES AUXILIARES DE INICIALIZACIÓN Y VISUALIZACIÓN


// Inicializa un vector de caracteres con espacios (' ')
void inicializar_vector_caracter(char* vector, int n) {
    for (int i = 0; i < n; i++) vector[i] = ' ';
}

// Muestra la matriz de adyacencia en consola
void mostrar_matriz(int** M, int n) {
    cout << "\nMatriz de adyacencia:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << M[i][j] << "\t";
        cout << endl;
    }
}

// FUNCIONES DEL ALGORITMO DIJKSTRA

// Carga los nombres de los vértices ('a', 'b', 'c', ...)
void leer_nodos(char* V, int n) {
    for (int i = 0; i < n; i++) V[i] = 'a' + i;
}

// Busca el índice de un vértice (ej: 'c' -> 2)
int buscar_indice_caracter(char* V, int n, char c) {
    for (int i = 0; i < n; i++) if (V[i] == c) return i;
    return -1;
}

// Retorna true si un vértice pertenece a un vector
bool pertenece(char c, char* vec, int n) {
    for (int i = 0; i < n; i++) if (vec[i] == c) return true;
    return false;
}

// Actualiza el conjunto de vértices no visitados (VS)
void actualizar_VS(char* V, char* S, char* VS, int n) {
    int k = 0;
    for (int i = 0; i < n; i++) if (!pertenece(V[i], S, n)) VS[k++] = V[i];
    for (; k < n; k++) VS[k] = ' ';
}

// Calcula el mínimo entre la distancia actual y una posible nueva
int calcular_minimo(int dw, int dv, int mvw) {
    if (dw == -1) {
        if (dv != -1 && mvw != -1) return dv + mvw;
        else return -1;
    } else {
        if (dv != -1 && mvw != -1) {
            int suma = dv + mvw;
            return (dw <= suma) ? dw : suma;
        } else return dw;
    }
}

// Actualiza los pesos de los vértices adyacentes
void actualizar_pesos(int* D, char* VS, int** M, char* V, char v, int n) {
    int i = 0;
    int idx_v = buscar_indice_caracter(V, n, v);
    while (VS[i] != ' ' && i < n) {
        int idx_w = buscar_indice_caracter(V, n, VS[i]);
        D[idx_w] = calcular_minimo(D[idx_w], D[idx_v], M[idx_v][idx_w]);
        i++;
    }
}

// Elige el vértice no visitado con menor distancia acumulada
char elegir_vertice(char* VS, int* D, char* V, int n) {
    int menor = -1;
    char vertice = ' ';
    for (int i = 0; i < n && VS[i] != ' '; i++) {
        int idx = buscar_indice_caracter(V, n, VS[i]);
        int peso = D[idx];
        if (peso != -1) {
            if (menor == -1 || peso < menor) {
                menor = peso;
                vertice = VS[i];
            }
        }
    }
    return vertice;
}

// Inicializa el vector de distancias D[] con la fila del origen
void inicializar_vector_D(int* D, int** M, int n, int origen) {
    for (int j = 0; j < n; j++) D[j] = M[origen][j];
}

// FUNCIONES DE MATRIZ Y GRAFO

// Inicializa la matriz con 0 en diagonal y -1 en el resto
void inicializar_matriz(int** M, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = (i == j) ? 0 : -1;
}

// Permite ingresar la matriz manualmente
void ingresar_matriz(int** M, int n) {
    cout << "Ingrese la matriz de distancias (" << n << "x" << n << "):\n";
    cout << "(Use -1 para indicar que NO existe arista entre dos nodos)\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cout << "Distancia " << char('a' + i) << " -> " << char('a' + j) << ": ";
            cin >> M[i][j];
        }
}


// Carga una matriz de ejemplo
void matriz_de_ejemplo(int** M, int n) {
    inicializar_matriz(M, n);
    M[0][1] = 4; M[0][2] = 11;
    M[1][4] = 2; M[1][3] = 6;
    M[2][1] = 3; M[2][3] = 6;
    M[4][3] = 3; M[4][2] = 5;
    cout << "\n Matriz de ejemplo cargada correctamente.\n";
}

// Genera un archivo DOT y un PNG del grafo
void imprimir_grafo(int** M, char* V, int n) {
    ofstream fp("grafo.dot");
    fp << "digraph G {\n";
    fp << "graph [rankdir=LR]\n";
    fp << "node [style=filled fillcolor=\"#00ff005f\"]\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && M[i][j] > 0)
                fp << V[i] << " -> " << V[j] << " [label=" << M[i][j] << "];\n";
    fp << "}\n";
    fp.close();
    system("dot -Tpng grafo.dot -o grafo.png");
    system("eog grafo.png &");
}

// Libera la memoria 
void liberar_matriz(int** M, int n) {
    for (int i = 0; i < n; i++) delete[] M[i];
    delete[] M;
}

// MENÚ PRINCIPAL 

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Uso: ./algoritmo_Dijkstra N" << endl;
        return -1;
    }

    int n = atoi(argv[1]);
    if (n < 3) {
        cout << "El número de nodos debe ser mayor que 2.\n";
        return -1;
    }

     // Reservar memoria 
    int** matriz = new int*[n];
    for (int i = 0; i < n; i++) matriz[i] = new int[n];

    int* D = new int[n];
    char* V = new char[n];
    char* S = new char[n];
    char* VS = new char[n];

    leer_nodos(V, n);
    inicializar_matriz(matriz, n);
    inicializar_vector_caracter(S, n);
    inicializar_vector_caracter(VS, n);

    bool matriz_ingresada = false;
    int opcion;
    int origen = 0;

     // Menú principal interactivo
    do {
        cout << "\n------- MENÚ PRINCIPAL --------\n";
        cout << "1. Ingresar matriz de distancias\n";
        cout << "2. Mostrar matriz\n";
        cout << "3. Generar grafo original (Graphviz)\n";
        cout << "4. Ejecutar algoritmo de Dijkstra\n";
        cout << "5. Cargar matriz de ejemplo\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            cout << "\nEntrada inválida. Por favor, ingrese un número entre 1 y 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (opcion) {
            case 1:
                ingresar_matriz(matriz, n);
                matriz_ingresada = true;
                break;

            case 2:
                if (matriz_ingresada)
                    mostrar_matriz(matriz, n);
                else
                    cout << "Debe ingresar o cargar la matriz primero.\n";
                break;

            case 3:
                if (matriz_ingresada)
                    imprimir_grafo(matriz, V, n);
                else
                    cout << "Ingrese o cargue la matriz antes de generar el grafo.\n";
                break;

            case 4: {
                if (!matriz_ingresada) {
                    cout << "Debe ingresar o cargar una matriz antes de ejecutar Dijkstra.\n";
                    break;
                }
                cout << "Ingrese índice del vértice origen (0-" << n - 1 << "): ";
                cin >> origen;
                if (origen < 0 || origen >= n) {
                    cout << "Índice fuera de rango.\n";
                    break;
                }
                // Inicialización de estructuras
                inicializar_vector_caracter(S, n);
                inicializar_vector_caracter(VS, n);
                for (int i = 0; i < n; i++) D[i] = -1;
                
                int* previo = new int[n];
                for (int i = 0; i < n; i++) previo[i] = -1;
                
                // Estado inicial
                inicializar_vector_D(D, matriz, n, origen);
                S[0] = V[origen];
                actualizar_VS(V, S, VS, n);

                cout << "\n--- Estado inicial ---\n";
                cout << "S: " << S << "\nVS: " << VS << "\nD: ";
                for (int i = 0; i < n; i++) cout << D[i] << " ";
                cout << "\n\n";
                
                // Algoritmo de Dijkstra
                for (int k = 0; k < n - 1; k++) {
                    char v = S[k];
                    if (v == ' ') break;
                    actualizar_pesos(D, VS, matriz, V, v, n);
                    char w = elegir_vertice(VS, D, V, n);
                    if (w == ' ') break;
                    int idx_v = buscar_indice_caracter(V, n, v);
                    int idx_w = buscar_indice_caracter(V, n, w);
                    previo[idx_w] = idx_v;
                    int lenS = 0;
                    while (lenS < n && S[lenS] != ' ') lenS++;
                    if (lenS < n) S[lenS] = w;
                    actualizar_VS(V, S, VS, n);
                    
                }
                // Mostrar resultados finales
                cout << "\n--- Resultado final ---\n";
                cout << "Distancias mínimas desde " << V[origen] << ":\n";
                for (int i = 0; i < n; i++) {
                    if (i == origen) continue;
                    cout << V[origen] << " → " << V[i] << " = ";
                    if (D[i] <= 0) cout << "∞";
                    else cout << D[i];
                    cout << " | Camino: ";
                    // Reconstrucción del camino
                    string camino = "";
                    int actual = i;
                    while (actual != -1) {
                        string nodo(1, V[actual]);
                        if (camino.empty()) camino = nodo;
                        else camino = nodo + " → " + camino;
                        actual = previo[actual];
                    }
                    cout << camino << "\n";
                }
                // Generar grafo resaltando caminos mínimos
                ofstream file("grafo.dot");
                file << "digraph G {\n rankdir=LR;\n node [shape=circle];\n";
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (matriz[i][j] > 0) {
                            bool esCamino = (previo[j] == i);
                            file << " " << V[i] << " -> " << V[j]
                                << " [label=\"" << matriz[i][j] << "\""
                                << (esCamino ? ", color=red, penwidth=2.0" : "")
                                << "];\n";
                        }
                    }
                }
                file << " " << V[origen] << " [style=filled, fillcolor=lightcoral];\n";
                file << "}\n";
                file.close();
                // Generar imagen y abrir
                system("dot -Tpng grafo.dot -o grafo.png");
                system("eog grafo.png &");

                delete[] previo;
                break;
            }

            case 5:
                matriz_de_ejemplo(matriz, n);
                matriz_ingresada = true;
                break;

            case 6:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opción no válida. Intente nuevamente.\n";
                break;
        }
    } while (opcion != 6);

    // Liberar memoria 
    liberar_matriz(matriz, n);
    delete[] D;
    delete[] V;
    delete[] S;
    delete[] VS;

    return 0;
}
