#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std; 
//estructura de nodo 
struct Nodo { 
    string resn;  // Nombre del residuo
    string resid; // Identificador
    Nodo* siguiente; 
};


// push: agregar residuo al final de la lista
void push(Nodo*& cabecera, Nodo*& final, string resn, string resid) {
    Nodo* nuevo = new Nodo;
    nuevo->resn = resn;
    nuevo->resid = resid;
    nuevo->siguiente = nullptr;
    
    if (cabecera == nullptr) { 
        cabecera = nuevo;
        final = nuevo;
    } else { 
        final->siguiente = nuevo;
        final = nuevo;
    }
    cout << "Residuo " << resn <<  resid << " ha sido agregado a la lista.\n";
    }


// mostrar contenido de la lista de residuos
void mostrar(Nodo* cabecera) {
    if (cabecera == nullptr) {
        cout << "La lista está vacía.\n";
        return;
    }
    cout << "\nSecuencia primaria de la proteína::\n";
    int pos = 1;
    Nodo* actual = cabecera;
    while (actual != nullptr) {
        cout << pos << ". " << actual->resn << " | " << actual->resid;
        if (actual->siguiente != nullptr){
            cout <<" -> ";
        }
        actual = actual->siguiente;
        pos++;
    }
    cout << endl;
}


    //Eliminar un residuo en una posición específica
bool borrarPosicion(Nodo*& cabecera, Nodo*& final, int posicion) {
    if (cabecera == nullptr || posicion < 1) return false;

    Nodo* actual = cabecera;
    if (posicion == 1) {  
        // borrar el primero 
        cabecera = actual->siguiente;
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
    if (actual->siguiente == nullptr){
        final = anterior;
    }
    delete actual;
    return true;
}

// liberar todos los nodos de la lista al salir
void liberarCola(Nodo*& cabecera, Nodo*& final ) {
    Nodo* aux;
    while (cabecera != nullptr) {
        aux = cabecera;
        cabecera = cabecera->siguiente;
        delete aux;
    }
    final = nullptr;
}

void generarDot(Nodo* cabecera, const string& outputDot, const string& outputPng){
    ofstream outfile;
	
	outfile.open(outputDot); // abre o crea el archivo
    if (!outfile.is_open()) {
        cerr << "No se pudo crear el archivo " << outputDot << "\n";
        return;
    }

    // Escribir encabezado de Graphviz
    outfile << "digraph G {\n";
    outfile << "rankdir = LR;\n";
    outfile << "node [style=filled fillcolor=yellow];\n";

    Nodo* actual = cabecera;
    while (actual != nullptr){
        outfile  << "\"" << actual->resn << actual->resid << "\";\n";
        actual = actual->siguiente;
    }
    actual = cabecera;
    while (actual != nullptr && actual->siguiente != nullptr) {
        outfile << "\"" << actual->resn << actual->resid << "\" -> \"" 
                << actual->siguiente->resn << actual->siguiente->resid << "\";\n";
        actual = actual->siguiente;
    }
    outfile << "}\n";
	outfile.close();

    cout << "+ Archivo graphviz generado: " << outputDot << "\n";

    string comando = "dot -Tpng " + outputDot + " -o " + outputPng;
    int resultado;
    resultado = system(comando.c_str());

    if (resultado == 0){
        cout << "+ Imagen graphviz generada: " << outputPng << "\n";
    } else {
        cout << "+ [ERROR]: Revise que esté instalado el software graphviz. Revise el comando de generacion de imagen. Revise el archivo input para la generacion de imagen. \n"; 

    }

}
//se carga el archivo 2PTN_resids_chainA_Format_Ubiq.pdb
void cargarArchivo(Nodo*& cabecera, Nodo*& final, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string resn;
        string resid;

        while (archivo >> resn >> resid) { 
            push(cabecera, final, resn, resid);
        }

        archivo.close();
        cout << "Residuos cargados desde '" << nombreArchivo << "' correctamente.\n";
    } else {
        cout << "No se pudo abrir el archivo '" << nombreArchivo << "'. Verifique que existe.\n";
    }
}

//se guardan las modifcaciones que se le realizen al archivo cargado
void guardarArchivo(Nodo* cabecera, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo para guardar.\n";
        return;
    }

    Nodo* actual = cabecera;
    while (actual != nullptr) {
        archivo << actual->resn << " " << actual->resid << "\n";
        actual = actual->siguiente;
    }

    archivo.close();
    cout << "Lista guardada en '" << nombreArchivo << "' correctamente.\n";
}


int main(int argc, char* argv[]) {
    Nodo* lista = nullptr;
    Nodo* final = nullptr;
    int opcion;
    string resn, resid;
    int pos;
    string archivoEntrada;

    if (argc == 2) {
        archivoEntrada = argv[1];
        cout << "Archivo de entrada: " << archivoEntrada << endl;
    } else {
        cout << "Uso: " << argv[0] << " <archivo_residuos>\n";
        return 1; // termina si no hay archivo
    }


    do{
        cout << "\n------ MENU SECUENCIA DE PROTEÍNA ------\n";
        cout << "1. Insertar un nuevo residuo al final de la secuencia.\n";
        cout << "2. Modificar el resn de un residuo (Mutación aminoacídica).\n";
        cout << "3. Eliminar un residuo en una posición específica.\n";
        cout << "4. Mostrar la lista de residuos en consola.\n";
        cout << "5. Exportar la lista a un archivo Graphviz (.dot).\n";
        cout << "6. Generar imagen con Graphviz.\n";
        cout << "7. Cargar residuos desde archivo.\n";
        cout << "8. Guardar los cambios en el archivo. \n";
        cout << "9. Salir del programa.\n";
        cout << "------------------------------------------\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: // Insertar
                cout << "Nombre del residuo: ";
                cin >> resn;
                cout << "Número de residuo: ";
                cin >> resid;
                push(lista, final, resn, resid);
                break;

            case 2: { // Mutación
                cout << "Ingrese la posición del residuo a modificar: ";
                cin >> pos;
                Nodo* actual = lista;
                int contador = 1;
                while (actual != nullptr && contador < pos) {
                    actual = actual->siguiente;
                    contador++;
                }
                if (actual != nullptr) {
                    cout << "Residuo actual: " << actual->resn << " " << actual->resid << endl;
                    cout << "Nuevo nombre (resn): ";
                    cin >> resn;
                    actual->resn = resn;
                    cout << "Mutación realizada.\n";
                } else {
                    cout << "Posición inválida.\n";
                }
                break;
            }

            case 3: // Eliminar por posición
                cout << "Ingrese la posición a borrar: ";
                cin >> pos;
                if (borrarPosicion(lista, final, pos))
                    cout << "Residuo en posición " << pos << " eliminado.\n";
                else
                    cout << "Posición inválida o lista vacía.\n";
                break;

            case 4: // Mostrar lista
                mostrar(lista);
                break;

            case 5: // Exportar .dot
                generarDot(lista, "primary_structure.dot", "primary_structure.png");
                break;

            case 6: { // Generar imagen desde .dot
                string comando = "dot -Tpng primary_structure.dot -o primary_structure.png";
                int resultado = system(comando.c_str());
                if (resultado == 0) {
                    cout << "Imagen generada correctamente.\n";
                    system("xdg-open primary_structure.png");
                }else{
                    cout << "Error al ejecutar Graphviz.\n";
                }
                break;
            }


            case 7:
                cargarArchivo(lista, final, archivoEntrada);
                break;

            case 8:
                 guardarArchivo(lista, archivoEntrada); // guarda usando el mismo archivo que cargaste
                break;
            case 9:
                cout << "Liberando memoria y saliendo...\n";
                liberarCola(lista, final);
                break;
        }

    } while (opcion != 9);

    return 0;
}