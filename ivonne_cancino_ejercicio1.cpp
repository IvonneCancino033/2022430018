#include <iostream>
#include <string>
using namespace std;

// Definición de la estructura 'Paciente' que almacena información básica de una persona
struct Paciente {
    string Nombre;
    int Edad;
    float Peso;
    float Altura;

};

int main() {
    // Se crea un array de 3 pacientes con valores predefinidos
    Paciente pacientes [3] = {
        {"Ivonne Cancino", 21, 60.0, 1.52},
        {"Mateo Robles", 21, 80.6, 1.80},
        {"Jesus Rojas", 25, 75.6, 1.65}
    };


    cout << "Centro de atencion primaria" << endl;
    // Se recorre el array de pacientes con un bucle for
    for (int i = 0; i < 3; i++){
        // En cada iteración, se muestra la información del paciente actual
        cout << "Paciente: " << pacientes[i].Nombre <<", Edad: " << pacientes[i].Edad << ", Peso: " << pacientes[i].Peso <<"kg"<< ", Altura: " << pacientes[i].Altura << "m" << endl;
    }
    
    return 0;

};