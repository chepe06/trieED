#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "unsortedArrayDictionary.h"
#include "trie.h"

using namespace std;

string minusculas(string str){
     str[0] = tolower(str[0]);
     return str;
}

string quitarIndeseados(string Palabra){
    string aux;
    int Switch = 0;
    const char CaracteresIndeseados[] = { '(', ')', ';', ',', '.', ':', '[', ']', '-', '<', '>', '_', '+', '#', '$', '%', '&', '/' , '«','"'};
    for (int i = 0; i < Palabra.length(); i++)
    {
        for (int j = 0; j < strlen(CaracteresIndeseados); j++)
            //cout << "letra: " << Palabra[i] << " - caracter: " << CaracteresIndeseados[j];
            if (Palabra[i] == CaracteresIndeseados[j]) Switch = 1;

        if (Switch == 0) aux += Palabra[i];
        Switch = 0;
    }
    return aux;
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");

    string archivo;
    //cout << "Ingrese el nombre del archivo junto con su extensión. Por ejemplo 'texto.txt'\nNombre: ";
    //cin >> archivo;
    archivo = "Prueba.txt";
    string linea;

    UnsortedArrayDictionary<int, string> dict;
    Trie arbolPalabras;

    fstream myFile(archivo);

    if(!myFile.is_open()){
       throw runtime_error("Error en la apertura del archivo");
    } else {
        cout << "El archivo se abrió de manera correcta\n\n";
        int aux = 0;
        while (getline(myFile, linea)){ //Mientras encuentre líneas
             cout << linea << "\n";
             dict.insert(aux, linea); //Se almacenan en el diccionario todas las líneas
             aux++; //Se aumenta el número que se usara de llave
        }
        myFile.close();
    }

    cout << "\n";
    dict.print();
    cout << "\n";

    //system("pause");
    List<string> *lineas = dict.getValues();
    List<int> *numeros = dict.getKeys(); numeros->goToStart();
    for (lineas->goToStart(); !lineas->atEnd(); lineas->next()){
        string line = lineas->getElement();
        int num = numeros->getElement();
        istringstream isstream(line);

        while(isstream >> line) { //Separa la linea cada vez que encuentra un espacio
            line = minusculas(line);
            line = quitarIndeseados(line);
            cout << num << " " << line << endl;
            arbolPalabras.insert(num,line);
        }
        numeros->next();
    }

    cout << "\n¿Qué palabra desea buscar?\nPalabra: ";
    string palabra; cin >> palabra;

    cout << "\nLa palabra se encuentra en las siguientes lineas " << endl;
    arbolPalabras.getLines(palabra);

    return 0;

}
