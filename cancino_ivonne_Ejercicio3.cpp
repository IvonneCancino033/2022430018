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
void promedioEdad (Patient* head);
void promedioPeso (Patient* head);
void calculoIMC(Patient* head);
void freepatients(Patient* head);


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
        cout << "La lista de pacientes está vacía.\n";
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
        cout << "La lista de pacientes está vacía.\n";
    }
}

// Calcula e imprime el IMC y estado nutricional de cada paciente
void calculoIMC(Patient* head){
    Patient* current = head;
    cout << "Cálculo de IMC para cada paciente:\n\n";

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
    promedioEdad(head);
    promedioPeso(head);
    calculoIMC(head);
    // Se libera la memoria usada por la lista
    freePatients(head);

    

    return 0;


}