#include <iostream>
#include <string>
#include <fstream>
using namespace std;


// Estructura que representa a un paciente en la lista
struct Patient {
    string Nombre;
    int Edad;
    float Peso;
    float Altura;
    Patient* next; // Puntero al siguiente paciente

};

Patient* createPatient(const string& Nombre_, int Edad_, float Peso_, float Altura_); // crear paciente
void addPatient(Patient** head, Patient* newPatient);
void printPatients(Patient* head);
void promedioEdad (Patient* head);
void promedioPeso (Patient* head);
void calculoIMC(Patient* head);
bool deletePatient(Patient*& head, int pos);
void freepatients(Patient* head);
void cargarArchivo(Patient*& head, const string& nombreArchivo);


// Crea un nuevo paciente con los datos proporcionados
Patient* createPatient(const string& Nombre_, int Edad_, float Peso_, float Altura_){
    Patient* newPatient = new Patient;
    newPatient->Nombre = Nombre_; // Asigna nombre
    newPatient->Edad = Edad_;      // Asigna edad                           
    newPatient->Peso = Peso_;  // Asigna peso
    newPatient->Altura = Altura_;  // Asigna Altura                       
    newPatient->next = nullptr;  // Asigna siguiente nodo como nulo
    return newPatient;


}
// Agrega un nuevo paciente al final de la lista
void addPatient (Patient** head, Patient* newPatient) {
    if (*head == nullptr){
        *head = newPatient; // La lista está vacía un nuevo paciente es la cabeza
    } else {
        Patient* current = *head;
         // Avanzar hasta el final de la lista
        while (current ->next != nullptr) {
            current = current ->next;
        }
        current ->next = newPatient; // Agregar al final
    }
    
}

// Imprime todos los pacientes en la lista
void printPatients(Patient* head){
    cout << "Pacientes registrados: \n\n";
    Patient* current = head;
    int index = 0;
    while (current != nullptr){
        cout << "Paciente #" << index << "\n";
        cout << "\tNombre: "<< current->Nombre << "\n"
        <<"\tEdad: "<< current->Edad << " años\n"
        <<"\tPeso: "<< current->Peso << " kg\n"
        <<"\tAltura: "<< current->Altura << " m\n"
        << "\t+----------------------------+\n\n";
        current = current ->next;
        index++;
    }
}

// Calcula y muestra el promedio de edad de los pacientes
void promedioEdad (Patient* head) {
    int sumarEdad = 0;
    int contador = 0;
    
    Patient* current = head;
    while (current != nullptr){
        sumarEdad += current->Edad;
        contador++;
        current = current->next;
    }
    if (contador > 0){
        float promedio = (float)sumarEdad / contador;
        cout << "Promedio de edad: " << promedio << " años.\n";
    } else {
        cout << "No hay pacientes registrados.\n";
    }
}

// Calcula y muestra el promedio de peso de los pacientes
void promedioPeso (Patient* head) {
    float sumarPeso = 0;
    int contador = 0;
    
    Patient* current = head;
    while (current != nullptr){
        sumarPeso += current->Peso;
        contador++;
        current = current->next;
    }
    if (contador > 0){
        float promedio = sumarPeso / contador;
        cout << "Promedio de peso: " << promedio << " kg.\n";
    } else {
        cout << "No hay pacientes registrados.\n";
    }
}

// Calcula e imprime el IMC y estado nutricional de cada paciente
void calculoIMC(Patient* head){
    Patient* current = head;
    cout << "Cálculo de IMC \n\n";

    while (current != nullptr){
        float imc = current->Peso / (current->Altura * current->Altura);
        cout << "Paciente: " << current->Nombre << endl;
        cout << "IMC: " << imc << " kg/m^2" << endl;

        if (imc < 18.5){
            cout << "Estado: Bajo peso.\n";
        } else if (imc < 25){
            cout << "Estado: Normal.\n";
        } else if (imc < 30){
            cout << "Estado: Sobrepeso.\n";
        } else if (imc < 35){
            cout << "Estado: Obesidad I.\n";
        } else if (imc < 40){
            cout << "Estado: Obesidad II.\n";
        } else{
            cout << "Estado: Obesidad III.\n";
        }
        cout << "+----------------------------+\n\n";
        current = current->next;
    }
    
}

// Elimina al paciente en la posición indicada (0 es la cabeza)
bool deletePatient(Patient*& head, int pos){
    if (!head || pos < 0 ) return false; 
    
    // Caso especial: eliminar cabeza (primer paciente)
    if (pos == 0) {
        Patient* tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }
    // Buscar el nodo anterior al que queremos eliminar
    Patient* cur = head;
    for (int i = 0; cur && i < pos - 1; ++i){
        cur = cur->next;
    }
     // Posición inválida
    if (!cur || !cur->next) return false;
    
    // Reenlazar y eliminar
    Patient* eliminar = cur->next;
    cur->next = eliminar->next;
    delete eliminar;
    return true;

}

//Libera la memoria ocupada por la lista de pacientes
void freePatients(Patient* head){
    Patient* current = head;
    while (current != nullptr){
        Patient* next = current->next;
        delete current;
        current = next;
    }
    cout << "Memoria liberada correctamente.\n";
}

// Carga pacientes desde un archivo de texto
void cargarArchivo(Patient*& head, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()){
        string nombre;
        int edad;
        float peso;
        float altura;
         // Leer línea por línea mientras haya datos
        while (archivo >> nombre >> edad >> peso >> altura){
            Patient* nuevo = createPatient(nombre, edad, peso, altura);
            addPatient(&head, nuevo);
        }
        archivo.close();
        cout << "Pacientes cargados desde el archivo '" << nombreArchivo << "' correctamente.\n";
    }else{
        cout << "No se pudo abrir el archivo '" << nombreArchivo << "'. Verifique que existe.\n";
    }

}

// Función principal con menú para interactuar con la gestión de pacientes
int main(){
    Patient* head = nullptr;
    int opcion;

do {
    cout << "\n------ MENU GESTION DE PACIENTES ------\n";
    
        cout << "[1]. Agregar paciente\n";
        cout << "[2]. Eliminar paciente por posicion\n";
        cout << "[3]. Ver pacientes\n";
        cout << "[4]. Calcular promedio de edad\n";
        cout << "[5]. Calcular promedio de peso\n";
        cout << "[6]. Calcular IMC de pacientes\n";
        cout << "[7]. Cargar pacientes desde archivo CSV\n";
        cout << "[0]. Salir\n";
        cout << "------------------------------------------\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "Has elegido la opción 1." << endl;
                string nombre;
                int edad;
                float peso;
                float altura;

                cout << "Ingrese nombre: ";
                cin >> nombre;
                cout << "Ingrese edad: ";
                cin >> edad;
                cout << "Ingrese peso (kg): ";
                cin >> peso;
                cout << "Ingrese altura (m): ";
                cin >> altura;

                Patient* nuevo = createPatient(nombre, edad, peso, altura);
                addPatient(&head, nuevo);
                cout << "Paciente agregado exitosamente.\n";
                break;
            }
            case 2: {
                cout << "Has elegido la opción 2." << endl;
                int posicion;
                cout << "Ingrese posicion del paciente a eliminar: ";
                cin >> posicion;
                if (deletePatient(head, posicion))
                    cout << "Paciente eliminado correctamente.\n";
                else
                    cout << "No se pudo eliminar (posicion invalida).\n";
                break;
            }
            case 3:
                cout << "Has elegido la opción 3." << endl;
                printPatients(head);
                break;

            case 4: 
                cout << "Has elegido la opción 4." << endl;
                promedioEdad(head);
                break;

            case 5:
                cout << "Has elegido la opción 5." << endl;
                promedioPeso(head);
                break;

            case 6:
                cout << "Has elegido la opción 6." << endl;
                calculoIMC(head);
                break;

            case 7:{
                cout << "Has elegido la opción 7." << endl;
                string archivo = "/home/ivonne/Documentos/algoritmo/lab/pacientes.txt";
                cargarArchivo(head, archivo);
                break;
            }

            case 0:
                cout << "Saliendo del programa\n";
                break;
            
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
    freePatients(head); // Liberar memoria antes de terminar
    return 0;
}
        

        
