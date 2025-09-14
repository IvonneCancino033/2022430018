#include <iostream>
using namespace std;

struct Pila {
    int MAX;  // Capacidad lógica de la pila (máximo número de elementos permitidos)
    int TOPE; // Indica la posición del último elemento en la pila (0 si está vacía)
    bool BAND; // Bandera usada para indicar si la pila está llena o vacía
    int enteros [5]; // Arreglo que almacena los elementos de la pila (tamaño físico 5)

    //Verifica si la pila está vacía
    bool Pila_vacia(int TOPE, bool &BAND){
        if (TOPE == 0) //no hay elementos en la pila
            BAND = true;
        else
            BAND = false;
        return BAND;

    }
    //Verifica si la pila está llena
    bool Pila_llena(int TOPE, int MAX, bool &BAND){
        if (TOPE == MAX) //ya no se pueden agregar más elementos
            BAND = true;
        else 
            BAND = false;
        return BAND;

    }
    //Agrega un número a la pila (si no está llena), caso de desbordamiento (overflow)
    void Push (bool &BAND, int &TOPE, int MAX, int enteros[], int DATO){
        Pila_llena(TOPE, MAX, BAND);
        if (BAND == true){
            cout << "Desbordamiento, pila llena\n";
        } else if (BAND == false){
            TOPE = TOPE +1;
            enteros[TOPE] = DATO;
            cout << "Agregado: \"" << DATO << "\"\n";
        }
    }
    //Elimina el último número de la pila (si no está vacía), caso de subdesbordamiento (underflow)
    int Pop(int enteros[], int &TOPE, bool &BAND){
        Pila_vacia(TOPE, BAND);
        if (BAND == true){
            cout << "Subdesbordamiento, pila vacia\n";
            return -1;
        } else if (BAND == false){
            int DATO = enteros[TOPE];
            TOPE = TOPE -1;
            cout << "Retirado: \"" << DATO << "\"\n";
            return DATO;
        }
        return -1;
    }
    //Muestra el contenido de la pila de arriba hacia abajo
    void Mostrar (int enteros[], int TOPE){
        if (TOPE == 0){
            cout << "La pila está vacía.\n";
        } else{
            cout << "Contenido de la pila:\n";
            for (int i = TOPE; i >= 1; i--) {
                cout << "- " << enteros[i] << "\n";
            }
        }
    }
};
//Define un objeto pila y configura sus valores iniciales
int main() {
    Pila pila;
    pila.MAX = 5;
    pila.TOPE = 0;
    pila.BAND = false;

    int opcion;
    int numero;

    do {
        cout << "\n------ MENU INGRESE UN NUMERO A LA PILA (MAXIMO DE LA PILA 100) ------\n";


        cout << "\nMenu:\n";
        cout << "[1]. Agregar/Push (Agregar numero)\n";
        cout << "[2]. Remover/Pop (Retirar numero)\n";
        cout << "[3]. Ver pila\n";
        cout << "[4]. Salir\n";
        cout << "------------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese el numero a agregar: ";
                cin >> numero;
                pila.Push(pila.BAND, pila.TOPE, pila.MAX, pila.enteros, numero);
                break;
            case 2:
                pila.Pop(pila.enteros, pila.TOPE, pila.BAND);
                break;
            case 3:
                pila.Mostrar(pila.enteros, pila.TOPE);
                break;
            case 4:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}