#include<iostream>
#include <string>

int longitud_string(const std::string& texto) {
    return texto.size();
}

int main() {
    std::string palabra;
    std::cout << "Introduce una palabra: ";
    std::cin >> palabra; 

    int largo = longitud_string(palabra);
    std::cout << "El largo de la palabra es: " << largo << std::endl;


    std::string frase_fija = "jesus rey de reyes";
    largo = longitud_string(frase_fija);
    std::cout << "La palabra es: " << frase_fija << std::endl;
    std::cout << "El largo de la palabra es: " << largo << std::endl;
    


}