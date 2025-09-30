#include <iostream>
#include <string>
using namespace std;
// estructura de nodo (estudiante)
struct Nodo {
    string nombre;
    string carrera;
    float promedio;
    Nodo* siguiente;
};

// push: agregar alumno a la cola
void push(Nodo*& frente, Nodo*& final, string nombre, string carrera, float promedio) {
    Nodo* nuevo = new Nodo();
    nuevo->nombre = nombre;
    nuevo->carrera = carrera;
    nuevo->promedio = promedio;
    nuevo->siguiente = nullptr;
    if (frente == nullptr) { 
        frente = nuevo; 
        final = nuevo; 
    } else { 
        final->siguiente = nuevo; 
        final = nuevo; 
    }
    cout << "Estudiante " << nombre << " ha sido agregado a la cola.\n";
    }

    // pop: Eliminar estudiante de la cola 
bool pop(Nodo*& frente, Nodo*& final, string& nombre, string& carrera, float& promedio) {
    if (frente == nullptr) return false; 
    Nodo* aux = frente;
    nombre = aux->nombre;
    carrera = aux->carrera;
    promedio = aux->promedio;
    frente = aux->siguiente; 
    if (frente == nullptr) {
        final = nullptr;
    }
    delete aux; //Se libera de la memoria del nodo 1
    return true;
}
// Verifica si la cola está vacía
void Cola_vacia(Nodo* frente, bool& band) {
    if (frente == nullptr)
        band = true;   // La cola está vacía
    else
        band = false;  // La cola NO está vacía
}

// verificar si la cola está llena (realmente nunca lo estará con listas dinámicas)
void Cola_llena(bool& band) {
    Nodo* prueba = new(nothrow) Nodo;  // intenta reservar memoria
    if (prueba == nullptr)
        band = true;   // No se pudo reservar memoria → la cola está llena (RAM agotada)
    else {
        band = false;  // Hay memoria disponible
        delete prueba; // libera el nodo de prueba
    }
}

// mostrar contenido de la cola
void mostrar(Nodo* frente) {
    if (frente == nullptr) {
        cout << "La cola está vacía.\n";
        return;
    }
    cout << "\nContenido actual de la cola:\n";
    int pos = 1;
    Nodo* actual = frente;
    while (actual != nullptr) {
        cout << pos << ". " << actual->nombre << " | "
            << actual->carrera << " | Promedio: "
            << actual->promedio << endl;
        actual = actual->siguiente;
        pos++;
    }
}

// borrar en una posición específica
bool borrarPosicion(Nodo*& frente, Nodo*& final, int posicion) {
    if (frente == nullptr || posicion < 1) return false;

    Nodo* actual = frente;
    if (posicion == 1) {  
        // borrar el primero
        frente = actual->siguiente;
        if (frente == nullptr) {
            final = nullptr;
        }
        delete actual;
        return true;
    }

    // recorrer hasta la posición anterior
    Nodo* anterior = nullptr;
    int contador = 1;
    while (actual != nullptr && contador < posicion) {
        anterior = actual;
        actual = actual->siguiente;
        contador++;
    }

    if (actual == nullptr) return false; // fuera de rango

    anterior->siguiente = actual->siguiente;
    if (actual == final){
        final = anterior;
    }
    delete actual;
    return true;
}
// liberar todos los nodos al salir
void liberarCola(Nodo*& frente) {
    Nodo* aux;
    while (frente != nullptr) {
        aux = frente;
        frente = frente->siguiente;
        delete aux;
    }
}

int main() {
    Nodo* frente = nullptr;
    Nodo* final = nullptr;
    int opcion;
    string nombre, carrera;
    float promedio;
    int pos;
    bool band;

    do {
        cout << "\n------ MENU COLA DE ESTUDIANTES ------\n";
        cout << "1. Agregar estudiantes (PUSH)\n";
        cout << "2. Eliminar al primer estudiante ingresado (POP)\n";
        cout << "3. Mostrar cola\n";
        cout << "4. Borrar en posición específica (POP)\n";
        cout << "5. Salir\n";
        cout << "------------------------------------------\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Nombre: ";
                getline(cin, nombre);
                cout << "Carrera: ";
                getline(cin, carrera);
                cout << "Promedio: ";
                cin >> promedio;
                cin.ignore();
                push(frente, final, nombre, carrera, promedio);
                break;
            case 2:
                if (pop(frente, final, nombre, carrera, promedio)) {
                    cout << "Se elimino del frente a: "
                        << nombre << " | " << carrera
                        << " | Promedio: " << promedio << endl;
                } else {
                    cout << "La cola está vacía.\n";
                }
                break;
            case 3:
                mostrar(frente);
                break;
            case 4:
                Cola_vacia(frente, band);
                if (band) {
                    cout << "La cola está vacía. No se puede borrar.\n";
                    break;
                }
                cout << "Ingrese la posición a borrar: ";
                cin >> pos;
                if (borrarPosicion(frente, final, pos))
                    cout << "Se borró el estudiante en la posición " << pos << ".\n";
                else
                    cout << "Posición inválida.\n";
                break;
            case 5:
                cout << " Liberando memoria de la cola y saliendo...\n";
                liberarCola(frente);
                final = nullptr;
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 5);

    return 0;
}
