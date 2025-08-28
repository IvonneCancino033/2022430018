#include<iostream>

double square(double x) 
{ 
    
    return x*x; 
}

void print_square(double x)
{
        std::cout << "El cuadrado de " << x << " es " << square(x) << '\n';

}

int main() 
{
    print_square(8);
    print_square(10);
}