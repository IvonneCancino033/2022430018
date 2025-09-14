#include <iostream>
#include <cstdlib> // para atoi, convierte strings a enteros
using namespace std;

struct Pila {
    int MAX;  // Altura máxima permitida en la pila (capacidad lógica)
    int TOPE; // Indica la posición actual del último contenedor en la pila
    bool BAND; // Bandera que indica si la pila está llena o vacía
    int contenedores [16]; // Arreglo de enteros para almacenar los IDs de los contenedores

    // Verifica si la pila está vacía
    bool Pila_vacia(int TOPE, bool &BAND){
        if (TOPE == 0)
            BAND = true;
        else
            BAND = false;
        return BAND;

    }
    // Verifica si la pila está llena
    bool Pila_llena(int TOPE, int MAX, bool &BAND){
        if (TOPE == MAX)
            BAND = true;
        else 
            BAND = false;
        return BAND;

    }    // Agrega un contenedor a la pila si no está llena
    void Push (bool &BAND, int &TOPE, int MAX, int contenedores[], int DATO){
        Pila_llena(TOPE, MAX, BAND);
        if (BAND == true){
            cout << "Desbordamiento, pila llena\n";
        } else if (BAND == false){
            TOPE = TOPE +1;
            contenedores[TOPE] = DATO;
            cout << "Agregado: \"" << DATO << "\"\n";
        }
    }   // Elimina el contenedor del tope si la pila no está vacía
    int Pop(int contenedores[], int &TOPE, bool &BAND){
        Pila_vacia(TOPE, BAND);
        if (BAND == true){
            cout << "Subdesbordamiento, pila vacia\n";
            return -1;
        } else if (BAND == false){
            int DATO = contenedores[TOPE];
            TOPE = TOPE -1;
            cout << "Retirado: \"" << DATO << "\"\n";
            return DATO;
        }
        return -1; //evita advertencia del compilador
    }
     // Muestra el contenido de la pila desde el tope hacia abajo
    void Mostrar (int contenedores[], int TOPE){
        if (TOPE == 0){
            cout << "La pila está vacía.\n";
        } else{
            cout << "Contenido de la pila:\n";
            for (int i = TOPE; i >= 1; i--) {
                cout << "[ " << contenedores[i] << "]\n";
            }
        }
    }   // Busca un contenedor en la pila y devuelve su nivel si lo encuentra
    bool ubicacion(int contenedorID, int TOPE, int &nivel){
        for (int i = 1; i <= TOPE; i++){
            if (contenedores[i] == contenedorID){
                nivel = i;
                return true;
            }
        }
        return false;
    }
};


int main(int argc, char* argv[]) {
    int n = 0, m = 0;
     //Entrada de argumentos desde la consola
    if (argc == 3) {
        n = atoi(argv[1]);
        m = atoi(argv[2]);
        if (n <= 0 || m <= 0 || n > 16 || m > 16) {
            cout << "Argumentos inválidos.\n";
            n = 0;
            m = 0;
        } else {
            cout << "Usando argumentos desde consola:\n";
        }
    }

    // Entrada de datos manual
    while (n <= 0 || m <= 0 || n > 16 || m > 16) {
        cout << "Ingrese altura máxima de las pilas (n, max 16): ";
        cin >> n;
        cout << "Ingrese cantidad de pilas (m, max 16): ";
        cin >> m;
        if (n <= 0 || m <= 0 || n > 16 || m > 16){
            cout << "Valores inválidos, por favor ingrese números entre 1 y 16.\n";
        }
    }

    cout << "\nAltura máxima de las pilas (n): " << n << "\n";
    cout << "Cantidad de pilas (m): " << m << "\n\n";
    //Inicialización de pilas
    Pila pilas[16];
    for (int i = 0; i < m; i++){
        pilas[i].MAX = n;
        pilas[i].TOPE = 0;
        pilas[i].BAND = false;
    }
    //Agregar contenedores
    int IDcontenedor = 1;
    char respuesta = 's';

    while (respuesta == 's' || respuesta == 'S' ){
        int pilaEscogida;
        cout << "\nIngrese el número de la pila (1 a " << m << ") donde desea agregar el contenedor " << IDcontenedor << ": ";
        cin >> pilaEscogida;

        if (pilaEscogida < 1 || pilaEscogida > m){
            cout << "Número de pila inválido.\n";
            continue;
        }
        if (pilas[pilaEscogida - 1].Pila_llena(pilas[pilaEscogida - 1].TOPE, pilas[pilaEscogida - 1].MAX, pilas[pilaEscogida - 1].BAND)) {
            cout << "La pila " << pilaEscogida << " está llena. Elija otra pila.\n";
            continue;
        }     // Agrega el contenedor
        pilas[pilaEscogida - 1].Push(pilas[pilaEscogida - 1].BAND, pilas[pilaEscogida - 1].TOPE, pilas[pilaEscogida - 1].MAX, pilas[ pilaEscogida - 1].contenedores, IDcontenedor);
        IDcontenedor++;
        // Mostrar estado actual
        cout << "\nEstado actual de las pilas:\n";
        for (int i = 0; i < m; i++) {
            cout << "PILA " << i + 1 << ":\n";
            pilas[i].Mostrar(pilas[i].contenedores, pilas[i].TOPE);
            cout << endl;
        }
        cout << "¿Desea agregar otro contenedor? (s/n): ";
        cin >> respuesta;
    }
    while (true){
        //Eliminar un contenedor
    int eliminarContenedor;
    cout << "\nIngrese el número del contenedor a eliminar o 0 para salir: ";
    cin >> eliminarContenedor;

    if (eliminarContenedor == 0) {
        cout << "Saliendo del programa...\n";
        break;
    }
    
    int Pilainicial = -1;
    int nivel = -1;
    // Buscar el contenedor en todas las pilas
    for (int i = 0; i < m; i++){
        if (pilas[i].ubicacion(eliminarContenedor, pilas[i].TOPE, nivel)){
            Pilainicial = i;
            break;
        }
    }

    if (Pilainicial == -1){
        cout << "Contenedor no encontrado.\n";
        continue;
    }

    cout << "\nMoviendo contenedores para liberar el contenedor " << eliminarContenedor << "...\n";
     // Mover contenedores que están encima del que se va a eliminar
    for (int i = pilas[Pilainicial].TOPE; i > nivel; i--){
        int temp = pilas[Pilainicial].Pop(pilas[Pilainicial].contenedores, pilas[Pilainicial].TOPE, pilas[Pilainicial].BAND);

        bool moverContenedor = false;
        int siguientePila = (Pilainicial + 1) % m;
        int intentos = 0;
        // Buscar otra pila con espacio para mover los contenedores
        while (intentos < m - 1){
            if (!pilas[siguientePila].Pila_llena(pilas[siguientePila].TOPE, pilas[siguientePila].MAX, pilas[siguientePila].BAND)){
                pilas[siguientePila].Push(pilas[siguientePila].BAND, pilas[siguientePila].TOPE, pilas[siguientePila].MAX, pilas[siguientePila].contenedores, temp);
                cout << " Movido contenedor " << temp << " de pila " << Pilainicial + 1 << " a pila " << siguientePila + 1 << "\n";
                moverContenedor = true;
                break;
            }
            siguientePila = (siguientePila + 1) % m;
            intentos++;
        }
        if (!moverContenedor){
            cout << " No hay espacio lateral para mover el contenedor " << temp << ". Cancelando.\n";
            break;
        }
    }
        

    int eliminado = pilas[Pilainicial].Pop(pilas[Pilainicial].contenedores, pilas[Pilainicial].TOPE, pilas[Pilainicial].BAND);
    cout << "Contenedor " << eliminado << " eliminado de la PILA" << Pilainicial + 1 << "\n";

    cout << "\nEstado final de los contenedores:\n";
    for (int i = 0; i < m; i++){
        cout << "PILA" << i + 1 << ": ";
        pilas[i].Mostrar(pilas[i].contenedores, pilas[i].TOPE);
        cout << endl;
    }

    cout << "Presione Enter para continuar...\n";
    cin.ignore();
    cin.get();  
    }

    return 0;
}