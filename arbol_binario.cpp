#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// Estructura del nodo del árbol
struct Nodo {
    int INFO;      // Información almacenada
    Nodo* IZQ;        // nodo izquierdo
    Nodo* DER;        // nodo derecho
};

// Función para verificar si un valor ya existe en el árbol
bool numeroRepetido(Nodo* raiz, int valor){
    if (raiz == nullptr)
        return false;
    if (raiz->INFO == valor)
        return true;
    // Buscar en hijos izquierdo y derecho
    return numeroRepetido(raiz->IZQ, valor)  || numeroRepetido(raiz->DER, valor);
}

// Función para crear el árbol de forma interactiva, evitando numeros repetidos
void crea_arbol(Nodo*& apnodo) {
    if (apnodo == nullptr) {
        int valor;
        cout << "Ingrese valor para el nodo: ";
        cin >> valor;

        // Evitar valores repetidos
        if (numeroRepetido(apnodo, valor)) {
            cout << "El número ya existe en el árbol. Intente otro valor.\n";
            crea_arbol(apnodo); // vuelve a preguntar el valor
            return;
        }

        apnodo = new Nodo;
        apnodo->INFO = valor;
        apnodo->IZQ = nullptr;
        apnodo->DER = nullptr;
    }

    char resp;

    cout << "¿Existe nodo por izquierda de " << apnodo->INFO << "? (s/n): ";
    cin >> resp;
    if (resp == 's' || resp == 'S') {
        crea_arbol(apnodo->IZQ);
    } else {
        apnodo->IZQ = nullptr;
    }

    cout << "¿Existe nodo por derecha de " << apnodo->INFO << "? (s/n): ";
    cin >> resp;
    if (resp == 's' || resp == 'S') {
        crea_arbol(apnodo->DER);
    } else {
        apnodo->DER = nullptr;
    }
}
// Función para buscar un nodo con valor 'valorDestino' y agregar un nuevo nodo como hijo izquierdo o derecho según se indique
bool buscar(Nodo* actual, int destino, int nuevoValor, string lado) {
    if (actual == nullptr) return false;

    if (actual->INFO == destino) {
        Nodo* nuevo = new Nodo{nuevoValor, nullptr, nullptr};

        if ((lado == "I" || lado == "i") && actual->IZQ == nullptr) {
            actual->IZQ = nuevo;
            return true;
        } else if ((lado == "D" || lado == "d") && actual->DER == nullptr) {
            actual->DER = nuevo;
            return true;
        } else {
            cout << "Ese lado ya está ocupado o la opción es inválida.\n";
            delete nuevo;
            return true; 
        }
    }

    // Buscar en subárboles
    return buscar(actual->IZQ, destino, nuevoValor, lado) || buscar(actual->DER, destino, nuevoValor, lado);
}

// Función para insertar un nuevo valor en el árbol (no permite duplicados)
void insertar(Nodo*& raiz, int nuevoValor) {
    if (raiz == nullptr) {
        raiz = new Nodo{nuevoValor, nullptr, nullptr};
        return;
    }

    if (numeroRepetido(raiz, nuevoValor)) {
        cout << "El número ya existe en el árbol (no se permiten repetidos).\n";
        return;
    }

    int destino;
    string lado;
    cout << "Ingrese el valor del nodo donde desea insertar el nuevo número: ";
    cin >> destino;
    cout << "¿Desea insertar por izquierda o derecha de " << destino << "? (I/D): ";
    cin >> lado;

    if (!buscar(raiz, destino, nuevoValor, lado)) {
        cout << "No se encontró el nodo destino.\n";
    }
}

// Recorridos del árbol

// Preorden: raiz -> Izquierda -> Derecha
void preorden(Nodo* APNODO) {
    if (APNODO != nullptr) {
        cout << APNODO->INFO << " ";
        preorden(APNODO->IZQ);
        preorden(APNODO->DER);
    }
}

// Inorden Izquierda -> raiz -> Derecha
void inorden(Nodo* APNODO) {
    if (APNODO != nullptr) {
        inorden(APNODO->IZQ);
        cout << APNODO->INFO << " ";
        inorden(APNODO->DER);
    }
}

// Posorden Izquierda -> Derecha -> raiz
void posorden(Nodo* APNODO) {
    if (APNODO != nullptr) {
        posorden(APNODO->IZQ);
        posorden(APNODO->DER);
        cout << APNODO->INFO << " ";
    }
}

// Función para eliminar un nodo con el valor especificado poe el ususario (no reestructura árbol)
bool eliminar(Nodo*& raiz, int valor) {
    if (raiz == nullptr)
        return false;

    if (raiz->INFO == valor) {
        delete raiz;
        raiz = nullptr;
        return true;
    }
     // Buscar en subárboles
    return eliminar(raiz->IZQ, valor) || eliminar(raiz->DER, valor);
}

// Función para buscar un nodo y modificar su valor
bool buscar(Nodo* nodo, int viejo, int nuevo) {
    if (nodo == nullptr) return false;

    if (nodo->INFO == viejo) {
        nodo->INFO = nuevo;
        return true;
    }

    // Buscar en hijos
    return buscar(nodo->IZQ, viejo, nuevo) || buscar(nodo->DER, viejo, nuevo);
}

// Función para modificar un valor en el árbol, evitando duplicados
void modificar(Nodo* raiz, int viejo, int nuevo) {
    if (numeroRepetido(raiz, nuevo)) {
        cout << "El nuevo valor ya existe en el árbol. No se permiten duplicados.\n";
        return;
    }

    if (buscar(raiz, viejo, nuevo)) {
        cout << "Valor modificado: " << viejo << " → " << nuevo << endl;
    } else {
        cout << "El valor " << viejo << " no se encontró en el árbol.\n";
    }
}

// Función para generar la imagen del árbol con Graphviz
void recorrerDot(Nodo* nodo, ofstream& outfile) {
    if (nodo != nullptr) {
        // dibujar nodo principal
        outfile << nodo->INFO << ";\n";

        // Enlace hacia el hijo izquierdo
        if (nodo->IZQ != nullptr) {
            outfile << nodo->INFO << " -> " << nodo->IZQ->INFO << ";\n";
            recorrerDot(nodo->IZQ, outfile);
        } else {
            outfile << "\"" << nodo->INFO << "i\" [shape=point];\n";
            outfile << nodo->INFO << " -> \"" << nodo->INFO << "i\";\n";
        }

        // Enlace hacia el hijo derecho
        if (nodo->DER != nullptr) {
            outfile << nodo->INFO << " -> " << nodo->DER->INFO << ";\n";
            recorrerDot(nodo->DER, outfile);
        } else {
            outfile << "\"" << nodo->INFO << "d\" [shape=point];\n";
            outfile << nodo->INFO << " -> \"" << nodo->INFO << "d\";\n";
        }
    }
}

// Función para generar archivo DOT y convertirlo a PNG usando Graphviz
void generarDot(Nodo* raiz, const string& outputDot, const string& outputPng) {
    ofstream outfile(outputDot);
    if (!outfile.is_open()) {
        cerr << "No se pudo crear el archivo " << outputDot << "\n";
        return;
    }

    outfile << "digraph G {\n";
    outfile << "rankdir = TB;\n"; 
    outfile << "node [style=filled fillcolor=yellow, shape=ellipse];\n";
    outfile << "edge [arrowhead=vee];\n";


    recorrerDot(raiz, outfile); 
    outfile << "}\n";
    outfile.close();

    cout << "+ Archivo Graphviz generado: " << outputDot << "\n";

    string comando = "dot -Tpng " + outputDot + " -o " + outputPng;
    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "+ Imagen Graphviz generada: " << outputPng << "\n";
        system(("eog " + outputPng + " &").c_str());
    } else {
        cout << "[ERROR]: No se pudo generar la imagen. Verifique si Graphviz está instalado.\n";
    }
}

// Función para liberar la memoria del árbol completo
void liberarArbol(Nodo*& raiz) {
    if (raiz != nullptr) {
        liberarArbol(raiz->IZQ);  // liberar subárbol izquierdo
        liberarArbol(raiz->DER);  // liberar subárbol derecho
        delete raiz;              // liberar nodo actual
        raiz = nullptr;   
    }
}

int main() {
    Nodo* raiz = nullptr;
    int opcion, valor, nuevoValor;

    do {
        cout << "\n--- MENU ARBOL BINARIO DE NUMEROS ENTEROS ---\n";
        cout << "1. Crear arbol\n";
        cout << "2. Eliminar\n";
        cout << "3. Modificar\n";
        cout << "4. Mostrar Preorden\n";
        cout << "5. Mostrar Inorden\n";
        cout << "6. Mostrar Posorden\n";
        cout << "7. Generar Graphviz\n";
        cout << "8. insertar un nuevo numero\n";
        cout << "0. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                liberarArbol(raiz); // limpiar árbol anterior si existe
                cout << "Construcción interactiva del árbol:\n";
                crea_arbol(raiz);
                break;
            case 2:
                cout << "Ingrese el número a eliminar: ";
                cin >> valor;
                if (!eliminar(raiz, valor))
                    cout << "El valor no se encuentra en el árbol.\n";
                else
                    cout << "Valor eliminado correctamente.\n";
                break;

            case 3:
                cout << "Ingrese el valor a modificar: ";
                cin >> valor;
                cout << "Ingrese el nuevo valor: ";
                cin >> nuevoValor;
                modificar(raiz, valor, nuevoValor);
                break;

            case 4:
                cout << "\n--- PREORDEN ---\n";
                preorden(raiz); cout << endl;
                break;

            case 5:
                cout << "\n--- INORDEN ---\n";
                inorden(raiz); cout << endl;
                break;

            case 6:
                cout << "\n--- POSORDEN ---\n";
                posorden(raiz); cout << endl;
                break;

            case 7:
                generarDot(raiz, "grafo.txt", "grafo.png");
                break;
            
            case 8: 
                if (raiz == nullptr) {
                    cout << "Primero debe crear el árbol (opción 1).\n";
                } else {
                    cout << "Ingrese el nuevo valor a insertar: ";
                    cin >> nuevoValor;
                    insertar(raiz, nuevoValor);
                }
                break;

            case 0:
                liberarArbol(raiz);
                cout << "Memoria liberada, programa terminado.\n...\n";
                break;

            default:
                cout << "Opción no válida.\n";
        }
    } while (opcion != 0);

    return 0;
}
