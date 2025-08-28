#include<iostream>

void verificarpar(int numeroUsuario){
    if (numeroUsuario % 2 == 0){
        std::cout << numeroUsuario << "  es numero par." << std::endl;
    } else {
        std::cout << numeroUsuario << "  es numero impar." << std::endl;
    }
}


int main(){
    
    int numeroUsuario;

    std::cout <<"Ingrese un numero entero: ";
    std::cin >> numeroUsuario;
    std::cout << "Has introducido el número: " << numeroUsuario << std::endl;

    verificarpar(numeroUsuario);

    std::cout <<"Verificar los numeros del 1 al 10";
    for (int i = 1; i <= 10; ++i) {
        verificarpar(i);
    }
    
    return 0;
}


