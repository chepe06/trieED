#include <iostream>

#include "words.h"
#include "windows.h"

using namespace std;

int main()
{
    //setlocale(LC_CTYPE, "Spanish");
    SetConsoleCP(1252); SetConsoleOutputCP(1252);
    string opc = "0";

    cout << "Bienvenido, se va a procesar el documento txt que indique a continuación\n\n";

    words palabras;
    system("pause");
    system("cls");

    while(opc != "5"){ //Menú de opciones
        cout << "Seleccione una opción:\n1) Consultar por prefijo\n2) Buscar palabra\n3) Buscar por cantidad de letras\n4) Palabras más utilizadas\n5) Salir del programa\n\nOpción: ";
        cin >> opc;
        system("cls");
        if(opc == "1"){
            palabras.prefijos();
        } else if(opc == "2"){
            palabras.lineasPalabra();
        } else if(opc == "3"){
            palabras.letras();
        } else if(opc == "4"){
            string opcAux = "0";
            while(opcAux != "5"){ //Menú de opciones 2
                cout << "Seleccione una opción:\n1) Agregar palabra a ignorar\n2) Limpiar lista de palabras a ignorar\n3) Ver top\n4) Ver palabras menos utilizadas\n5) Regresar\n\nOpción: ";
                cin >> opcAux;
                system("cls");
                if(opcAux == "1"){
                    palabras.agregarIgnorados();
                } else if(opcAux == "2"){
                    palabras.borrarIgnorados();
                } else if(opcAux == "3"){
                    palabras.top(true);
                } else if(opcAux == "4"){
                    palabras.top(false);
                } else if(opcAux == "5"){
                } else {
                    cout << "Opción inválida\n";
                    system("pause");
                    system("cls");
                }
            }
        } else if(opc == "5"){
            palabras.borrarIgnorados();
            cout << "Saliendo...\n";
        } else {
            cout << "Opción inválida\n";
            system("pause");
            system("cls");
        }
    }

    return 0;
}
