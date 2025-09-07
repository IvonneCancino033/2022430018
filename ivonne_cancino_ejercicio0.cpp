#include <iostream>
#include <string>
using namespace std;

// Definición de una estructura para representar un paciente
struct Paciente {
    string Nombre;
    int Edad;
    float Peso;
    float Altura;

};

int main(){
    // Declaración e inicialización de tres pacientes con datos fijos
    Paciente paciente1 = {"Ivonne Cancino", 21, 60.0, 1.52};
    Paciente paciente2 = {"Roberto Robles", 21, 80.6, 1.80};
    Paciente paciente3 = {"Joan Rojas", 25, 75.6, 1.65};



    // Impresión de la información de los pacientes
    cout << "Centro de atencion primaria" << endl;
    cout << "Paciente: "<< paciente1.Nombre << ", Edad: "<< paciente1.Edad << ", Peso: " << paciente1.Peso << "kg, Altura: "<< paciente1.Altura<< "m"<< endl; 
    cout << "Paciente: "<< paciente2.Nombre << ", Edad: "<< paciente2.Edad << ", Peso: " << paciente2.Peso << "kg, Altura: "<<paciente2.Altura<< "m"<<endl; 
    cout << "Paciente: "<< paciente3.Nombre << ", Edad: "<< paciente3.Edad << ", Peso: " << paciente3.Peso << "kg, Altura: "<<paciente3.Altura<< "m"<<endl; 

    return 0;
}