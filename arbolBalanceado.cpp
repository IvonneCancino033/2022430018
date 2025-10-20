#include <iostream> 
#include <fstream> 
#include <string> 
#include <cstdlib> 
#include <sstream>
using namespace std;

//Estructura del nodo del arbol AVL
struct NodoGO {
    string codigo; //Codigo del termino GO
    string funcion; //Funcion del termino GO
    float score; //valor numerico usado como valor clave del nodo
    int FE; //Factor de equilibrio
    NodoGO* IZQ; //Puntero al subarbol izquierdo
    NodoGO* DER; //Puntero al subarbol derecho

};

// Prototipos de funciones
void restructura1(NodoGO*& nodoCabeza, bool& BO);
void restructura2(NodoGO*& nodoCabeza, bool& BO);
void borra(NodoGO** aux1, NodoGO** otro1, bool* BO);

//Funcion para insertar un nuevo nodo al arbol con balanceo
void inserta_balanceado(NodoGO*& NODO, bool& BO, const string& codigoNuevo, const string& funcionNueva, float scoreNuevo) {
    //Si el arbol esta vacio, se crea un nuevo nodo
    if (NODO == nullptr) {
        NODO = new NodoGO{codigoNuevo, funcionNueva, scoreNuevo, 0, nullptr, nullptr};
        BO = true; //Indica que la altura del arbul aumento
    } else if (scoreNuevo < NODO->score) { //Insercion en el subarbol izquierdo
        inserta_balanceado(NODO->IZQ, BO, codigoNuevo, funcionNueva, scoreNuevo);
         // Ajuste del factor de equilibrio y posibles rotaciones
        if (BO) {
            switch (NODO->FE) {
                case 1:
                    NODO->FE = 0;
                    BO = false;
                    break;
                case 0:
                    NODO->FE = -1;
                    break;
                case -1:
                    restructura2(NODO, BO);  // Desbalance a la izquierda
                    break;
            }
        }
         // Insercion en el subarbol derecho
    } else if (scoreNuevo > NODO->score) {
        inserta_balanceado(NODO->DER, BO, codigoNuevo, funcionNueva, scoreNuevo);

        if (BO) {
            switch (NODO->FE) {
                case -1:
                    NODO->FE = 0;
                    BO = false;
                    break;
                case 0:
                    NODO->FE = 1;
                    break;
                case 1:
                    restructura1(NODO, BO);  // Desbalance a la derecha
            }
        }
        // Si el score ya existe, no se inserta
    } else {
        cout << "Ya existe un nodo con ese score\n";
        BO = false;
    }
}

//Reestructura1: rotaciones derecha (DD y DI)
void restructura1(NodoGO*& nodoCabeza, bool& BO) {
    NodoGO *nodo, *nodo1, *nodo2;
    nodo = nodoCabeza;

    if (BO) {
        switch (nodo->FE) {
            case -1:
                nodo->FE = 0;
                break;
            case 0:
                nodo->FE = 1;
                BO = false;
                break;
            case 1:
                nodo1 = nodo->DER;
                // Rotacion Derecha-Derecha (DD)
                if (nodo1->FE >= 0) { 
                    nodo->DER = nodo1->IZQ;
                    nodo1->IZQ = nodo;
                    switch (nodo1->FE) {
                        case 0:
                            nodo->FE = 1;
                            nodo1->FE = -1;
                            BO = false;
                            break;
                        case 1:
                            nodo->FE = 0;
                            nodo1->FE = 0;
                            BO = false;
                            break;
                    }
                    nodo = nodo1;
                     // Rotacion Derecha-Izquierda (DI)
                } else { 
                    nodo2 = nodo1->IZQ;
                    nodo->DER = nodo2->IZQ;
                    nodo2->IZQ = nodo;
                    nodo1->IZQ = nodo2->DER;
                    nodo2->DER = nodo1;
                    // Ajuste de factores de equilibrio
                    if (nodo2->FE == 1)
                        nodo->FE = -1;
                    else
                        nodo->FE = 0;

                    if (nodo2->FE == -1)
                        nodo1->FE = 1;
                    else
                        nodo1->FE = 0;

                    nodo = nodo2;
                    nodo2->FE = 0;
                }
                break;
        }
    }

    nodoCabeza = nodo;
}

//Reestructura2: rotaciones izquierda (II y ID)
void restructura2(NodoGO*& nodoCabeza, bool& BO) {
    NodoGO *nodo, *nodo1, *nodo2;
    nodo = nodoCabeza;

    if (BO) {
        switch (nodo->FE) {
            case 1:
                nodo->FE = 0;
                break;
            case 0:
                nodo->FE = -1;
                BO = false;
                break;
            case -1: // Rotacion Izquierda-Izquierda (II)
                nodo1 = nodo->IZQ; 
                if (nodo1->FE <= 0) { 
                    nodo->IZQ = nodo1->DER;
                    nodo1->DER = nodo;
                    switch (nodo1->FE) {
                        case 0:
                            nodo->FE = -1;
                            nodo1->FE = 1;
                            BO = false;
                            break;
                        case -1:
                            nodo->FE = 0;
                            nodo1->FE = 0;
                            BO = false;
                            break;
                    }
                    nodo = nodo1;
                } else { // Rotacion Izquierda-Derecha (ID)
                    nodo2 = nodo1->DER;
                    nodo->IZQ = nodo2->DER;
                    nodo2->DER = nodo;
                    nodo1->DER = nodo2->IZQ;
                    nodo2->IZQ = nodo1;

                    if (nodo2->FE == -1)
                        nodo->FE = 1;
                    else
                        nodo->FE = 0;

                    if (nodo2->FE == 1)
                        nodo1->FE = -1;
                    else
                        nodo1->FE = 0;

                    nodo = nodo2;
                    nodo2->FE = 0;
                }
                break;
        }
    }

    nodoCabeza = nodo;
}

//Funcion de busqueda de un nodo por score
void busqueda(NodoGO* nodo, float scoreBuscado) {
    if (nodo == nullptr) return;

    busqueda(nodo->IZQ, scoreBuscado);

    if (nodo->score == scoreBuscado) {
        cout << "Nodo encontrado: " << nodo->codigo << " - " << nodo->funcion << " - Score: " << nodo->score << endl;
    }

    busqueda(nodo->DER, scoreBuscado);
}
//Eliminacion de un nodo y rebalanceo del arbol
void eliminacionBalanceado(NodoGO*& nodoCabeza, bool& BO, float scoreEliminar) {
    NodoGO* nodo = nodoCabeza;
    if (nodo != nullptr) {
        if (scoreEliminar < nodo->score) {
            eliminacionBalanceado(nodo->IZQ, BO, scoreEliminar);
            restructura1(nodo, BO);
        } else if (scoreEliminar > nodo->score) {
            eliminacionBalanceado(nodo->DER, BO, scoreEliminar);
            restructura2(nodo, BO);
        } else {
            NodoGO* otro = nodo;
            if (otro->DER == nullptr) {
                nodoCabeza = otro->IZQ;
                delete otro;
                BO = true;
                cout << "Nodo con score " << scoreEliminar << " eliminado correctamente.\n";
            } else if (otro->IZQ == nullptr) {
                nodoCabeza = otro->DER;
                delete otro;
                BO = true;
                cout << "Nodo con score " << scoreEliminar << " eliminado correctamente.\n";
            } else {
                borra(&(otro->IZQ), &otro, &BO);
                restructura1(nodo, BO);
                cout << "Nodo con score " << scoreEliminar << " eliminado correctamente.\n";
            }
        }
    } else {
        cout << "El nodo con score " << scoreEliminar << " NO se encuentra en el árbol\n";
    }
}

//Funcion que borra un nodo con dos hijos (encontrar predecedor y reemplazar datos)
void borra(NodoGO** aux1, NodoGO** otro1, bool* BO) {
    NodoGO* aux = *aux1;
    NodoGO* otro = *otro1;

    if (aux->DER != nullptr) {
        borra(&(aux->DER), &otro, BO);
        restructura2(aux, *BO);
    } else {
        // Copiar datos del nodo más grande del subarbol izquierdo
        otro->codigo = aux->codigo;
        otro->funcion = aux->funcion;
        otro->score = aux->score;

        NodoGO* temp = aux;
        aux = aux->IZQ;
        delete temp;
        *BO = true;
    }

    *aux1 = aux;
    *otro1 = otro;
}

//Funcion que verifica si existe un nodo con un determinado score
bool existeScore(NodoGO* nodo, float scoreBuscado) {
    if (nodo == nullptr) return false;
    if (scoreBuscado == nodo->score) return true;
    return existeScore(nodo->IZQ, scoreBuscado) || existeScore(nodo->DER, scoreBuscado);
}
//Funcion que hace el recorrido para generar el archivo dot
void PreOrdenGO(NodoGO* nodo, ofstream& fp) {
    if (nodo != nullptr) {
         // Etiqueta del nodo con todos sus datos (funcion, codigo, score y FE)
        string label = "Función: " + nodo->funcion + "\\nCódigo: " + nodo->codigo + "\\nScore: " + to_string(nodo->score) + "\\nFE=" + to_string(nodo->FE);

        // Representacion en rectangulo
        fp << "\"" << nodo->codigo << "\" [shape=rectangle, label=\"" << label << "\", style=filled, fillcolor=yellow];\n";
         // Enlaces hacia el hijo izquierdo
        if (nodo->IZQ != nullptr) {
            fp << "\"" << nodo->codigo << "\" -> \"" << nodo->IZQ->codigo << "\";\n";
            PreOrdenGO(nodo->IZQ, fp);
        } else {
            string nullName = nodo->codigo + "i";
            fp << "\"" << nullName << "\" [shape=point];\n";
            fp << "\"" << nodo->codigo << "\" -> \"" << nullName << "\";\n";
        }
        // Enlaces hacia el hijo derecho
        if (nodo->DER != nullptr) {
            fp << "\"" << nodo->codigo << "\" -> \"" << nodo->DER->codigo << "\";\n";
            PreOrdenGO(nodo->DER, fp);
        } else {
            string nullName = nodo->codigo + "d";
            fp << "\"" << nullName << "\" [shape=point];\n";
            fp << "\"" << nodo->codigo << "\" -> \"" << nullName << "\";\n";
        }
    }
}

//Funcion para cargar datos desde un archivo csv y crear el arbol AVL
void cargarGODesdeCSV(NodoGO*& raiz, const string& archivoCSV) {
    ifstream archivo(archivoCSV);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo '" << archivoCSV << "'\n";
        return;
    }

    string linea;
    getline(archivo, linea); // Ignorar cabecera del CSV


    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string codigo, funcion, scoreStr;

        getline(ss, codigo, ',');
        getline(ss, funcion, ',');
        getline(ss, scoreStr);

        float score = stof(scoreStr); // Convertir a numero

        bool BO = false;
        inserta_balanceado(raiz, BO, codigo, funcion, score);
    }

    archivo.close();
}
//Funcion para liberar memoria del arbol completo
void liberarArbol(NodoGO* nodo) {
    if (nodo) {
        liberarArbol(nodo->IZQ);
        liberarArbol(nodo->DER);
        delete nodo;
    }
}
//Funcion que genera el grafo del arbol con graphviz
void GenerarGrafoGO(NodoGO* raiz) {
    if (!raiz) return;

    ofstream fp("grafo.txt");
    fp << "digraph G {\n";
    fp << "rankdir=TB;\n";
    fp << "node [style=filled, fillcolor=yellow, fontname=\"Arial\"];\n";

    string label = raiz->codigo + "\\n" + to_string(raiz->score) + "\\nFE=" + to_string(raiz->FE);
    fp << "nullraiz [shape=point];\n";
    fp << "nullraiz -> \"" << raiz->codigo << "\";\n";
    fp << "\"" << raiz->codigo << "\" [label=\"" << label << "\"];\n";

    PreOrdenGO(raiz, fp);

    fp << "}\n";
    fp.close();

    system("dot -Tpng grafo.txt -o grafo.png");
    system("eog grafo.png &");
    cout << "Grafo generado como 'grafo.png'.\n";
}

//Funcion principal
int main(int argc, char* argv[]) {
    if (argc != 2) { 
        cout << "Uso: " << argv[0] << " archivo.csv\n"; 
        return 1; 
    } 
    NodoGO* raiz = nullptr; 
    string archivo = argv[1]; 
    cargarGODesdeCSV(raiz, archivo); 
    int opcion;
    do {
        cout << "\n--- MENÚ TÉRMINOS GO EN ÁRBOL AVL ---\n";
        cout << "1. Crear árbol desde archivo CSV\n";
        cout << "2. Insertar nuevo término GO\n";
        cout << "3. Buscar término GO\n";
        cout << "4. Generar grafo (Graphviz)\n";
        cout << "5. Eliminar término GO\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();  // Limpio el buffer 

        switch (opcion) {
            case 1: {
                cout << "Ingrese el nombre del archivo CSV: ";
                string nuevoArchivo;
                getline(cin, nuevoArchivo);

                // Borrar arbol anterior
                liberarArbol(raiz);
                raiz = nullptr;

                cargarGODesdeCSV(raiz, nuevoArchivo);
                cout << "Árbol creado desde archivo exitosamente.\n";
                break;
            }

            case 2: {
                string codigo, funcion;
                float score;
                cout << "Ingrese el código GO: ";
                getline(cin, codigo);
                cout << "Ingrese la función: ";
                getline(cin, funcion);
                cout << "Ingrese el score: ";
                cin >> score;
                cin.ignore();

                if (existeScore(raiz, score)) {
                    cout << "Ya existe un nodo con ese score. No se puede insertar.\n";
                } else {
                    bool BO = false;
                    inserta_balanceado(raiz, BO, codigo, funcion, score);
                    cout << "Nodo insertado correctamente.\n";
                }
                break;
            }

            case 3: {
                float scoreBuscar;
                cout << "Ingrese el score a buscar: ";
                cin >> scoreBuscar;
                cin.ignore();
                busqueda(raiz, scoreBuscar);
                break;
            }

            case 4:
                GenerarGrafoGO(raiz);
                break;

            case 5: {
                cout << "Ingrese el score a eliminar: ";
                float scoreEliminar;
                cin >> scoreEliminar;
                cin.ignore();
                bool BO = false;
                eliminacionBalanceado(raiz, BO, scoreEliminar);
                break;
            }

            case 0:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }

    } while (opcion != 0);

    liberarArbol(raiz);  // Liberar memoria al salir
    return 0;
}