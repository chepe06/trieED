#ifndef WORDS_H
#define WORDS_H

//#include <iostream>
#include <fstream>
//#include <sstream>
#include <string.h>
#include "unsortedArrayDictionary.h"
#include "trie.h"

class words
{
private:
    string *archivo = nullptr;
    string linea;
    UnsortedArrayDictionary<int, string> dict;
    Trie arbolPalabras;

public:
    words(){
        //cout << "Ingrese el nombre del archivo junto con su extensión. Por ejemplo '"C:/Users/PC/Desktop/Prueba.txt";'\nNombre: ";
        //cin >> file;
        string file = "C:/Users/XPC/Desktop/texto.txt";
        archivo = &file;
        llenarDiccionario();
    }

    void llenarDiccionario()
    {
        fstream myFile(*archivo);

        if(!myFile.is_open()){
            throw runtime_error("Error en la apertura del archivo"); //Quitar para que imprima el error y vuelva a pedir la ruta del archivo
            //cout << "Error en la apertura del archivo\nIngrese el nombre del archivo junto con su extensión. Por ejemplo '"C:/Users/PC/Desktop/Prueba.txt";'\nNombre: ";
            //cin >> file;
        }
        else{
            cout << "El archivo " <<  *archivo << " se abrió de manera correcta\n\n";
            int aux = 0;
            while (getline(myFile, linea)){ //Mientras encuentre líneas
                //cout << linea << "\n";
                dict.insert(aux, linea); //Se almacenan en el diccionario todas las líneas
                aux++; //Se aumenta el número que se usara de llave
            }
            myFile.close();
        }
    }

    void imprimirDiccionario(){
        dict.print();
        system("pause");
        system("cls");
    }




};

#endif // WORDS_H
