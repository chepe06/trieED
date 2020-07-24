#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "unsortedArrayDictionary.h"

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "Spanish");

    string archivo;
    //cout << "Ingrese el nombre del archivo junto con su extensi�n. Por ejemplo 'texto.txt'\nNombre: ";
    //cin >> archivo;
    archivo = "Prueba.txt";
    string linea;

    UnsortedArrayDictionary<int, string> dict;

    fstream myFile(archivo);

    if(!myFile.is_open()){
       throw runtime_error("Error en la apertura del archivo");
    } else {
        cout << "El archivo se abri� de manera correcta\n\n";
        int aux = 0;
        while (getline(myFile, linea)){ //Mientras encuentre l�neas
             cout << linea << "\n";
             dict.insert(aux, linea); //Se almacenan en el diccionario todas las l�neas
             aux++; //Se aumenta el n�mero que se usara de llave
        }
        myFile.close();
    }

    cout << "\n";
    dict.print();
    cout << "\n";

    //system("pause");
    List<string> *lineas = dict.getValues();
    for (lineas->goToStart(); !lineas->atEnd(); lineas->next()){
        string line = lineas->getElement();
        istringstream isstream(line);

        while(isstream >> line) {
            cout << line << endl;
        }

    }
    return 0;

}
