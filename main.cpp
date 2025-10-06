#include <iostream>
#include <string>
#include <limits>// Para limpiar el buffer de entrada (cin.ignore)
#include <cstdlib> //para exit



int* ids = nullptr;        
double* pesos = nullptr;   
std::string* destinos = nullptr; 
int* prioridades = nullptr; 
char* estados = nullptr;   

const int CAPACIDAD_FIJA = 50; 
int total_paquetes = 0;   
int indice_frente = 0;   

void iniciar_arreglos() {
    total_paquetes = 0;
    indice_frente = 0;
    
    try {
        ids = new int[CAPACIDAD_FIJA];
        pesos = new double[CAPACIDAD_FIJA];
        destinos = new std::string[CAPACIDAD_FIJA];
        prioridades = new int[CAPACIDAD_FIJA];
        estados = new char[CAPACIDAD_FIJA];
        std::cout << "Memoria para " << CAPACIDAD_FIJA << " paquetes lista." << std::endl;
    } catch (const std::bad_alloc& e) {
        std::cerr << "error No hay memoria << std::endl;
        std::exit(1); 
    }
}

void borrar_memoria() {
    delete[] ids;
    delete[] pesos;
    delete[] destinos;
    delete[] prioridades;
    delete[] estados;
    
    ids = nullptr;
    pesos = nullptr;
    destinos = nullptr;
    prioridades = nullptr; 
    estados = nullptr;
    
    std::cout << "\nMemoria libre." << std::endl;
}

void poner_paquete() {
    if (total_paquetes >= CAPACIDAD_FIJA) {
        std::cout << "\nerror Capacidad máxima de " << CAPACIDAD_FIJA << " paquetes alcanzada." << std::endl;
        return;
    }

    std::cout << "\nNuevo Paquete" << std::endl;
    
    ids[total_paquetes] = total_paquetes + 1000; 
    std::cout << "ID: " << ids[total_paquetes] << std::endl;

    std::cout << "Dime el Peso (kg): ";
    std::cin >> pesos[total_paquetes];
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    std::cout << "Dime el Destino: ";
    std::getline(std::cin, destinos[total_paquetes]);

    std::cout << "Dime la Prioridad (1-3): ";
    std::cin >> prioridades[total_paquetes];
    
    estados[total_paquetes] = 'E'; 

    std::cout << "\nPaquete " << ids[total_paquetes] << " agregado" << std::endl;
    total_paquetes++;
}

void sacar_paquete() {
    while (indice_frente < total_paquetes && estados[indice_frente] == 'D') {
        indice_frente++;
    }

    if (indice_frente >= total_paquetes) {
        std::cout << "La cola está vacía no hay nada para despachar" << std::endl;
        indice_frente = 0; 
        total_paquetes = 0;
        return;
    }

    std::cout << "\nDespachando:" << std::endl;
    std::cout << "ID: " << ids[indice_frente] 
         << ", Ciudad: " << destinos[indice_frente] 
         << ", Peso: " << pesos[indice_frente] << " kg." << std::endl;

    estados[indice_frente] = 'D';
    indice_frente++; 
}

void ver_proximo() {
    while (indice_frente < total_paquetes && estados[indice_frente] == 'D') {
        indice_frente++;
    }

    if (indice_frente >= total_paquetes) {
        std::cout << "No hay paquetes esperando" << std::endl;
        return;
    }

    std::cout << "\nPróximo paquete es:" << std::endl;
    std::cout << "ID: " << ids[indice_frente] << std::endl;
    std::cout << "Peso: " << pesos[indice_frente] << " kg" << std::endl;
    std::cout << "Destino: " << destinos[indice_frente] << std::endl;
    std::cout << "Prioridad: " << prioridades[indice_frente] << std::endl;
    std::cout << "Estado: En Cola" << std::endl;
}

void buscar_por_ciudad() {
    std::string ciudad_buscada;
    std::cout << "\nBúsqueda" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cout << "Dime la ciudad: ";
    std::getline(std::cin, ciudad_buscada);

    int paquetes_en_cola = 0;
    double peso_total = 0.0;

    for (int i = 0; i < total_paquetes; i++) {
        if (estados[i] == 'E' && destinos[i] == ciudad_buscada) {
            paquetes_en_cola++;
            peso_total += pesos[i];
        }
    }

    std::cout << "\nReporte para: " << ciudad_buscada << std::endl;
    std::cout << "Paquetes EN COLA: " << paquetes_en_cola << std::endl;

    if (paquetes_en_cola > 0) {
        double promedio = peso_total / paquetes_en_cola;
        std::cout << "Peso promedio: " << promedio << " kg" << std::endl;
    } else {
        std::cout << "Nada en cola para esa ciudad" << std::endl;
    }
}

void ver_todos() {
    std::cout << "\nLista completa de paquetes" << std::endl;
    std::cout << "N° / ID / Peso / Destino / Prioridad / Estado" << std::endl;
    for (int i = 0; i < total_paquetes; i++) {
        std::cout << i << "  / " << ids[i] << " / " << pesos[i] << " / " << destinos[i] << " / " << prioridades[i] << " / " << estados[i];
        if (i == indice_frente && estados[i] == 'E') {
            std::cout << " <== FRENTE";
        }
        std::cout << std::endl;
    }
    std::cout << "Total En Cola: " << total_paquetes - indice_frente << std::endl;
}

void mostrar_menu() {
    std::cout << "\n\nMenu logistico" << std::endl;
    std::cout << "1. Meter Paquete a la Cola" << std::endl;
    std::cout << "2. Sacar Paquete" << std::endl;
    std::cout << "3. Ver el Próximo a Despachar" << std::endl;
    std::cout << "4. Buscar Paquetes por Ciudad" << std::endl;
    std::cout << "5. Ver Todos los Paquetes" << std::endl;
    std::cout << "6. Salir del Programa" << std::endl;
    std::cout << "\n";
    std::cout << "Capacidad Total: " << CAPACIDAD_FIJA << " / Paquetes Registrados: " << total_paquetes << std::endl;
    std::cout << "Elige una opción: ";
}

int main() {
    iniciar_arreglos();
    int opcion;

    do {
        mostrar_menu();
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            opcion = 0; 
            std::cout << "No pusiste un número hazlo de nuevo" << std::endl;
            continue;
        }

        switch (opcion) {
            case 1:
                poner_paquete();
                break;
            case 2:
                sacar_paquete();
                break;
            case 3:
                ver_proximo();
                break;
            case 4:
                buscar_por_ciudad();
                break;
            case 5:
                ver_todos();
                break;
            case 6:
                break;
            default:
                std::cout << "Opcion mal mi chavo tienes que elegir 1 a 6." << std::endl;
        }
    } while (opcion != 6);

    borrar_memoria();
    return 0;
}
