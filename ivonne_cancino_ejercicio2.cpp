#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// Estructura que representa a un paciente en la lista
struct Patient {
    string Nombre;
    int Edad;
    float Peso;
    float Altura;
    Patient* next; // Puntero al siguiente paciente

};


Patient* createPatient(string& Nombre_, int Edad_, float Peso_, float Altura_); // crear paciente
void addPatient(Patient** head, Patient* newPatient);
void printPatient(Patient* head);
void freepatients(Patient* head);
bool deletePatientAtPosition(Patient*& head, int pos);


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
        *head = newPatient; // La lista está vacía
    } else {
        Patient* current = *head;
        while (current ->next != nullptr) {
            current = current ->next;
        }
        current ->next = newPatient;
    }
    
}

// Imprime todos los pacientes en la lista
void printPatients(Patient* head){
    cout << "Pacientes: \n\n";
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

// Elimina al paciente en la posición indicada (0 es la cabeza)
bool deletePatient(Patient*& head, int posicion){
    if (!head || posicion < 0 ) return false; 
    
    // Caso especial: eliminar cabeza
    if (posicion == 0) {
        Patient* tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }
    // Buscar el nodo anterior al que queremos eliminar
    Patient* cur = head;
    for (int i = 0; cur && i < posicion - 1; ++i){
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





// Función principal que demuestra el uso de todas las funciones
int main(){
    Patient* head = nullptr;  // Cabeza de la lista
    Patient* newPatient;
    // Se crean e insertan pacientes en la lista
    newPatient = createPatient("Ivonne Cancino", 21, 60.0, 1.52);
    addPatient(&head, newPatient);
    cout << "Paciente agregado: Ivonne Cancino\n";

    newPatient = createPatient("Mateo Robles", 21, 80.6, 1.80);
    addPatient(&head, newPatient);
    cout << "Paciente agregado: Mateo Robles\n";

    newPatient = createPatient("Jesus Rojas", 25, 75.6, 1.65);
    addPatient(&head, newPatient);
    cout << "Paciente agregado: Jesus Rojas\n";
    
    // Mostrar lista antes de eliminar
    printPatients(head);

     // Eliminar paciente en posición 1 (Mateo Robles)
    cout << "Eliminando paciente en posición 1...\n";
    bool eliminado = deletePatient(head, 1);

    if (eliminado) {
        cout << "Paciente eliminado correctamente.\n";
    } else{
        cout << "No se pudo eliminar el paciente en esa posición.\n";
    }
    // Mostrar lista después de eliminar
    printPatients(head);
    // Se libera la memoria usada por la lista
    freePatients(head);

    return 0;


}