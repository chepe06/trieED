#include <iostream>

#include "words.h"

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    int opc = 0;

    cout << "Hola Main";
    words palabras;
    cout << "Adios Main";

    while(opc != 7){ //Men� de opciones
        cout << "Seleccione una opci�n:\n1) Consultar por prefijo\n2) Buscar palabra\n3) Buscar por cantidad de letras\n4) Palabras m�s utilizadas\n5) Imprimir texto\n6) Imprimir palabras del trie\n7) Salir del programa\n\nOpci�n: ";
        cin >> opc;
        system("cls");
        if(opc == 1){

        } else if(opc == 2){
            //palabras.lineasPalabra();
        } else if(opc == 3){

        } else if(opc == 4){
            int opcAux = 0;
            while(opcAux != 5){ //Men� de opciones 2
                cout << "Seleccione una opci�n:\n1) Agregar palabra a ignorar\n2) Limpiar lista de palabras a ignorar\n3) Ver top\n4) Ver palabras menos utilizadas\n5) Regresar\n\nOpci�n: ";
                cin >> opcAux;
                system("cls");
                if(opcAux == 1){
                    //Agregar palabra a ignorar
                } else if(opcAux == 2){
                    //Limpiar lista de palabras a ignorar
                } else if(opcAux == 3){
                    //Ver top
                } else if(opcAux == 4){
                    //Ver palabras menos utilizadas
                }
            }
        } else if(opc == 5){
            palabras.imprimirDiccionario();
        } else if(opc == 6){
            palabras.imprimirTrie();
        } else if(opc == 7){
            cout << "Saliendo...\n";
        } else {
            cout << "Opci�n inv�lida\n";
            system("pause");
            system("cls");
        }
    }

    return 0;
}
