#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

//Genera un arreglo con valores aleatorios entre 0 y 4999.
void generarArreglo(int A[], int N) {
    for (int i = 0; i < N; i++)
        A[i] = rand() % 5000;
}

//MÉTODO SHELLSORT: Int reduce la distancia entre elementos comparados hasta llegar a 1.
void shellsort(int A[], int N){
    int INT, I, AUX;
    bool BAND;

    INT = N + 1; // Tamaño inicial del salto.

    while (INT > 1){
        INT = INT / 2; // Reducir el salto a la mitad.
        BAND = true;

        while (BAND == true){
            BAND = false;
            I = 0;

            while ((I + INT) < N){
                // Intercambia si el elemento está fuera de orden.
                if (A[I] > A[I + INT]){
                    AUX = A[I];
                    A[I] = A[I + INT];
                    A[I + INT] = AUX;
                    BAND= true;

                }
                I = I + 1;
            }
        }
    }
    
}

//Función REDUCE utilizada por QUICKSORT: Se encarga de ubicar el pivote en su posición correcta.
void reduce(int A[], int INI, int FIN, int &POS){
    int IZQ, DER, AUX;
    bool BAND;

    IZQ = INI;
    DER = FIN;
    POS = INI;
    BAND = true;

    while (BAND == true){
         // Mover el puntero derecho hacia la izquierda
        while ((A[POS] <= A[DER]) && (POS != DER))
            DER = DER - 1;
        if (POS == DER)
            BAND = false;
        else {
            // Intercambiar elementos
            AUX = A[POS];
            A[POS] = A[DER];
            A[DER] = AUX;
            POS = DER;
        }
        // Mover puntero izquierdo hacia la derecha
        while ((A[POS] >= A[IZQ]) && (POS > IZQ))
            IZQ = IZQ + 1;
        if (POS == IZQ)
            BAND = false;
        else{
            AUX = A[POS];
            A[POS] = A[IZQ];
            A[IZQ] = AUX;
            POS = IZQ;
        }
    }
}

//METODO QUICKSORT: Usa pila manual (PILA_MENOR y PILA_MAYOR) para simular la recursión.
void quicksort(int A[], int N){
    int TOPE, INI, FIN, POS;

    int PILA_MENOR[N];
    int PILA_MAYOR[N];
    // Insertamos el rango inicial en la "pila"
    TOPE = 0;
    PILA_MENOR[TOPE] = 0;
    PILA_MAYOR[TOPE] = N - 1;
    // Mientras existan subrangos por procesar
    while (TOPE >= 0){
        INI = PILA_MENOR[TOPE];
        FIN = PILA_MAYOR[TOPE];
        TOPE = TOPE - 1;

        reduce(A, INI, FIN, POS);
         // Lado derecho del pivote
        if(INI < (POS -1)){
            TOPE = TOPE + 1;
            PILA_MENOR[TOPE] = POS + 1;
            PILA_MAYOR[TOPE ]= FIN;
        }
    }
}

//METODO BURBUJA MENOR: Recorre desde el final hacia el inicio, haciendo “flotar” los elementos más pequeños.
void burbuja_menor(int A[], int N) {
    int I, J, AUX;

    for (I = 1; I < N; I++) {

        for (J = N - 1; J >= I; J--) {
            if (A[J - 1] > A[J]) {
                AUX = A[J - 1];
                A[J - 1] = A[J];
                A[J] = AUX;
            }
        }
    }
}

//METODO BURBUJA MAYOR: Recorre desde el inicio hacia el final, haciendo “hundirse” los elementos más grandes.
void burbuja_mayor(int A[], int N) {
    int I, J, AUX;

    for (I = N - 2; I >= 0; I--) {

        for (J = 0; J <= I; J++) {
            if (A[J] > A[J + 1]) {
                AUX = A[J];
                A[J] = A[J + 1];
                A[J + 1] = AUX;
            }
        }
    }
}

//METODO INSERCIÓN: Inserta elemento por elemento en su posición correcta.
void insercion(int A[], int N) {
    int I, K, AUX;

    for (I = 1; I < N; I++) {

        AUX = A[I];
        K = I - 1;

        while (K >= 0 && AUX < A[K]) {
            A[K + 1] = A[K];
            K = K - 1;
        }

        A[K + 1] = AUX;
    }
}

//METODO SELECCIÓN: Busca el menor elemento del subarreglo y lo coloca al inicio.
void seleccion(int A[], int N) {
    int I, J, MENOR, AUX;

    for (I = 0; I < N - 1; I++) {

        MENOR = I;

        for (J = I + 1; J < N; J++) {
            if (A[J] < A[MENOR]) {
                MENOR = J;
            }
        }

        if (MENOR != I) {
            AUX = A[I];
            A[I] = A[MENOR];
            A[MENOR] = AUX;
        }
    }
}

//Copiar un arreglo en otro
void copiarArreglo(int dest[], int src[], int N) {
    for (int i = 0; i < N; i++)
        dest[i] = src[i];
}
//Muestra el arreglo completo
void mostrar(int A[], int N) {
    for (int i = 0; i < N; i++)
        cout << "a[" << i << "]=" << A[i] << " ";
    cout << endl;
}

//PROGRAMA PRINCIPAL: Recibe N -> tamaño del vector, s|n -> mostrar o no mostrar contenido
//Aplica TODOS los métodos de ordenamiento y mide su tiempo de ejecución con CHRONO.

int main(int argc, char* argv[]) {
     // Validación de parámetros
    if (argc < 3) {
        cout << "Uso correcto:\n";
    cout << "   ./programa N s|n\n\n";
    cout << "Donde:\n";
    cout << "   N  -> cantidad de elementos del arreglo (numero entero positivo)\n";
    cout << "   s  -> mostrar los arreglos (antes y despues de cada metodo)\n";
    cout << "   n  -> NO mostrar los arreglos, solo los tiempos\n\n";
    cout << "Ejemplo:\n";
    cout << "   ./programa 10000 n\n";
    cout << "   ./programa 50 s\n\n";
    return 1;
    }

    int N = atoi(argv[1]);
    char VER = argv[2][0];

    if (N <= 0) {
        cout << "N debe ser un numero positivo.\n";
        return 1;
    }

    srand(time(NULL));
    // Crear arreglo original
    int *original = new int[N];
    generarArreglo(original, N);
     // Si el usuario elige mostrar el contenido
    if (VER == 's') {
        mostrar(original, N);
        cout << "-----------------------------------------\n";
    }

    cout << "Metodo        | Tiempo\n";
    cout << "-----------------------------------------\n";

    int *A = new int[N];
    long double tiempo;

    // ---------------- BURBUJA MENOR  ----------------
    copiarArreglo(A, original, N);
    auto t1 = high_resolution_clock::now();
    burbuja_menor(A, N);
    auto t2 = high_resolution_clock::now();
    tiempo = duration_cast<milliseconds>(t2 - t1).count();
    cout << "Burbuja       | " << tiempo << " milisegundos\n";

     // ---------------- BURBUJA MAYOR ----------------
    copiarArreglo(A, original, N);
    t1 = high_resolution_clock::now();
    burbuja_mayor(A, N);
    t2 = high_resolution_clock::now();
    tiempo = duration_cast<milliseconds>(t2 - t1).count();
    cout << "Burbuja mayor  | " << tiempo << " milisegundos\n";

    // ---------------- INSERCION --------------
    copiarArreglo(A, original, N);
    t1 = high_resolution_clock::now();
    insercion(A, N);
    t2 = high_resolution_clock::now();
    tiempo = duration_cast<milliseconds>(t2 - t1).count();
    cout << "Insercion     | " << tiempo << " milisegundos\n";

    // ---------------- SELECCION --------------
    copiarArreglo(A, original, N);
    t1 = high_resolution_clock::now();
    seleccion(A, N);
    t2 = high_resolution_clock::now();
    tiempo = duration_cast<milliseconds>(t2 - t1).count();
    cout << "Seleccion     | " << tiempo << " milisegundos\n";

    // ---------------- SHELLSORT --------------
    copiarArreglo(A, original, N);
    t1 = high_resolution_clock::now();
    shellsort(A, N);
    t2 = high_resolution_clock::now();
    tiempo = duration_cast<microseconds>(t2 - t1).count() / 1000.0;
    cout << "Shellsort     | " << tiempo << " milisegundos\n";

    // ---------------- QUICKSORT --------------
    copiarArreglo(A, original, N);
    t1 = high_resolution_clock::now();
    quicksort(A, N);
    t2 = high_resolution_clock::now();
    tiempo = duration_cast<microseconds>(t2 - t1).count() / 1000.0;
    cout << "Quicksort     | " << tiempo << " milisegundos\n";

    cout << "-----------------------------------------\n";

    // Si el usuario pidió mostrar resultados ordenados
    if (VER == 's') {
        copiarArreglo(A, original, N);
        burbuja_menor(A, N);
        cout << "Burbuja ";
        mostrar(A, N);

        copiarArreglo(A, original, N);
        insercion(A, N);
        cout << "Insercion ";
        mostrar(A, N);

        copiarArreglo(A, original, N);
        seleccion(A, N);
        cout << "Seleccion ";
        mostrar(A, N);

        copiarArreglo(A, original, N);
        shellsort(A, N);
        cout << "Shellsort ";
        mostrar(A, N);

        copiarArreglo(A, original, N);
        quicksort(A, N);
        cout << "Quicksort ";
        mostrar(A, N);
    }
    // Liberar memoria
    delete[] A;
    delete[] original;

    return 0;
}