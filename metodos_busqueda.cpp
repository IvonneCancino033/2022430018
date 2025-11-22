#include <iostream>
#include <cstdlib>
using namespace std;

#define N 20 // Tamaño de la tabla hash
#define VACIO -1  // Valor que indica que una posición está vacía


// Estructura del nodo para el Encadenamiento
struct Nodo {
    int info;
    Nodo* sig; // Puntero al siguiente nodo de la lista
};

// Función hash principal
int H(int k) {
    return k % N; // Calcula la posición en la tabla usando módulo
}
// Función hash secundaria para doble hashing
int H2(int k) {
    return 1 + (k % (N - 1)); // Asegura un salto distinto de 0
}

//   REASIGNACIÓN PRUEBA LINEAL (L)
int reasignacion_Prueba_Lineal(int V[], int k) {

    int d = H(k); // Posición inicial
    if (V[d] == VACIO) { // Si la posición está vacía
        V[d] = k;
        cout << "Insertado sin colisión en posición " << d << "\n";
        return d;
    }

    cout << "Colisión en " << d << " — aplicando REASIGNACIÓN PRUEBA LINEAL...\n";

    int dx = (d + 1) % N; // Desplazamiento lineal

    while (dx != d && V[dx] != VACIO) { // Busca posición libre
        dx = (dx + 1) % N;
    }

    if (dx == d) { // Tabla llena
        cout << "ERROR: tabla llena.\n";
        return -1;
    }

    V[dx] = k;

    cout << "Desplazado a posición final " << dx << "\n";
    return dx;
}

//   REASIGNACIÓN PRUEBA CUADRÁTICA (C)
int reasignacion_Prueba_Cuadratica(int V[], int k) {

    int d = H(k);
    if (V[d] == VACIO) { 
        V[d] = k;
        cout << "Insertado sin colisión en posición " << d << "\n";
        return d;
    }

    cout << "Colisión en " << d << " — aplicando REASIGNACIÓN PRUEBA CUADRÁTICA...\n";

    int i = 1;
    int dx;

    while (i < N) { // Desplazamiento cuadrático
        dx = (d + i * i) % N;

        if (V[dx] == VACIO) {
            V[dx] = k;
            cout << "Desplazado a posición final " << dx << "\n";
            return dx;
        }

        i++;
    }

    cout << "ERROR: tabla llena.\n";
    return -1;
}

//   REASIGNACIÓN DOBLE DIRECCIÓN HASH (D)
int reasignacion_Doble_Direccion(int V[], int k) {

    int d = H(k);
    int salto = H2(k); // Segundo hash para el salto

    if (V[d] == VACIO) {
        V[d] = k;
        cout << "Insertado sin colisión en posición " << d << "\n";
        return d;
    }

    cout << "Colisión en " << d << " — aplicando REASIGNACIÓN DOBLE DIRECCIÓN HASH...\n";

    int dx = (d + salto) % N;

    while (dx != d && V[dx] != VACIO) {
        dx = (dx + salto) % N;
    }

    if (dx == d) {
        cout << "ERROR: tabla llena.\n";
        return -1;
    }

    V[dx] = k;

    cout << "Desplazado a posición final " << dx << "\n";
    return dx;
}

//   ENCADENAMIENTO (E)
int encadenamiento(int T[], Nodo* L[], int k) {

    int d = H(k);
    Nodo* nuevo = new Nodo{k, nullptr};

    if (L[d] == nullptr) { // Si la lista está vacía
        L[d] = nuevo;
        cout << "Insertado en lista sin colisión (posición " << d << ")\n";
        return d;
    }

    cout << "Colisión en " << d << " — agregando al final de la lista...\n";
    // Recorre hasta el final de la lista
    Nodo* q = L[d];
    while (q->sig != nullptr)
        q = q->sig;

    q->sig = nuevo; // Agrega el nuevo nodo al final

    cout << "Insertado al final de la lista en índice " << d << "\n";
    return d;
}


//   IMPRESIONES

void imprimirArreglo(int V[]) {
    cout << "\n--- TABLA HASH ---\n";
    for (int i = 0; i < N; i++) {
        if (V[i] == VACIO) cout << "[" << i << "] ---\n";
        else cout << "[" << i << "] " << V[i] << "\n";
    }
}

void imprimirListas(Nodo* L[]) {
    cout << "\n--- LISTAS DE ENCADENAMIENTO ---\n";
    for (int i = 0; i < N; i++) {
        cout << "[" << i << "] ";
        Nodo* q = L[i];

        if (!q) {
            cout << "---\n";
            continue;
        }

        while (q != nullptr) {
            cout << q->info << " -> ";
            q = q->sig;
        }
        cout << "NULL\n";
    }
}

//   BÚSQUEDAS (CON COLISIONES Y DESPLAZAMIENTOS)



// BÚSQUEDA LINEAL (L)
int buscar_Lineal(int V[], int k) {

    int d = H(k);
    cout << "Buscando " << k << " (Prueba Lineal)...\n";

    if (V[d] == k) {
        cout << "Encontrado sin desplazamiento en posición " << d << "\n";
        return d;
    }

    int dx = (d + 1) % N;
    int pasos = 1;

    while (dx != d && V[dx] != VACIO && V[dx] != k) {
        cout << "Colisión durante búsqueda en posición " << dx << "\n";
        dx = (dx + 1) % N;
        pasos++;
    }

    if (V[dx] == k) {
        cout << "Encontrado después de " << pasos << " desplazamientos en posición " << dx << "\n";
        return dx;
    }

    cout << "No encontrado después de " << pasos << " desplazamientos.\n";
    return -1;
}


// BÚSQUEDA CUADRÁTICA (C)
int buscar_Cuadratica(int V[], int k) {

    int d = H(k);
    cout << "Buscando " << k << " (Prueba Cuadrática)...\n";

    if (V[d] == k) {
        cout << "Encontrado sin desplazamiento en posición " << d << "\n";
        return d;
    }

    int i = 1;
    int dx;

    while (i < N) {
        dx = (d + i * i) % N;

        cout << "Desplazamiento cuadrático i=" << i << " hacia posición " << dx << "\n";

        if (V[dx] == k) {
            cout << "Encontrado después de " << i << " desplazamientos en posición " << dx << "\n";
            return dx;
        }

        if (V[dx] == VACIO)
            break;

        i++;
    }

    cout << "No encontrado después de " << i-1 << " desplazamientos.\n";
    return -1;
}

// BÚSQUEDA DOBLE DIRECCIÓN (D)
int buscar_Doble(int V[], int k) {

    int d = H(k);
    int salto = H2(k);

    cout << "Buscando " << k << " (Doble Hash)...\n";
    cout << "Salto = " << salto << "\n";

    if (V[d] == k) {
        cout << "Encontrado sin desplazamiento en posición " << d << "\n";
        return d;
    }

    int dx = (d + salto) % N;
    int pasos = 1;

    while (dx != d && V[dx] != VACIO && V[dx] != k) {
        cout << "Colisión durante búsqueda en posición " << dx << "\n";
        dx = (dx + salto) % N;
        pasos++;
    }

    if (V[dx] == k) {
        cout << "Encontrado después de " << pasos << " desplazamientos en posición " << dx << "\n";
        return dx;
    }

    cout << "No encontrado después de " << pasos << " desplazamientos.\n";
    return -1;
}


// BÚSQUEDA ENCADENAMIENTO (E)
int buscar_Encadenamiento(Nodo* L[], int k) {

    int d = H(k);
    Nodo* q = L[d];
    int pasos = 0;

    cout << "Buscando " << k << " en lista enlazada (bucket " << d << ")...\n";

    while (q != nullptr && q->info != k) {
        cout << "Avance en lista (colisión)...\n";
        q = q->sig;
        pasos++;
    }

    if (q == nullptr) {
        cout << "No encontrado después de " << pasos << " desplazamientos.\n";
        return -1;
    }

    cout << "Encontrado después de " << pasos << " desplazamientos en lista.\n";
    return d;
}


//MAIN
int main(int argc, char* argv[]) {

    if (argc < 2) { // Verifica que se haya pasado el método
        cout << "Uso: ./hash {L|C|D|E}\n";
        return 0;
    }

    char metodo = argv[1][0];

    int V[N]; // Arreglo hash
    Nodo* L[N]; // Listas para encadenamiento

    // Inicializar
    for (int i = 0; i < N; i++) {
        V[i] = VACIO; 
        L[i] = nullptr;
    }

    int opcion, k;
     // Menú
    do {
        cout << "\n======== MENU ========\n";
        cout << "Método: ";
        // Ejecutar acción según opción
        switch (metodo) {
            case 'L': cout << "Reasignación Prueba Lineal\n"; break;
            case 'C': cout << "Reasignación Prueba Cuadrática\n"; break;
            case 'D': cout << "Reasignación Doble Dirección Hash\n"; break;
            case 'E': cout << "Encadenamiento\n"; break;
        }

        cout << "1) Insertar valor\n";
        cout << "2) Buscar valor\n";
        cout << "0) Salir\n";
        cout << "=======================\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {

        case 1:
            cout << "Valor a insertar: ";
            cin >> k;

            if (metodo == 'L') reasignacion_Prueba_Lineal(V, k);
            else if (metodo == 'C') reasignacion_Prueba_Cuadratica(V, k);
            else if (metodo == 'D') reasignacion_Doble_Direccion(V, k);
            else if (metodo == 'E') encadenamiento(V, L, k);

            imprimirArreglo(V);
            if (metodo == 'E') imprimirListas(L);
            break;

        case 2:
            cout << "Valor a buscar: ";
            cin >> k;

            if (metodo == 'L') buscar_Lineal(V, k);
            else if (metodo == 'C') buscar_Cuadratica(V, k);
            else if (metodo == 'D') buscar_Doble(V, k);
            else if (metodo == 'E') buscar_Encadenamiento(L, k);

            break;
        }

    } while (opcion != 0);

    return 0;
}
