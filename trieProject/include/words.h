#ifndef WORDS_H
#define WORDS_H

//#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "unsortedArrayDictionary.h"
#include "trie.h"
#include "List.h"

class words
{
private:
    string *archivo = nullptr;
    string linea;
    UnsortedArrayDictionary<int, string> dict;
    Trie arbolPalabras;
    ArrayList<string> *listaIgnorados = new ArrayList<string>(1024);

public:
    words()
    {
        //cout << "Ingrese el nombre del archivo junto con su extensión. Por ejemplo '"C:/Users/PC/Desktop/Prueba.txt";'\nNombre: ";
        //cin >> file;
        string file = "Libros/WarPeace.txt";
        archivo = &file;
        llenarListaIgnorados();
        llenarDiccionario();
        llenarTrie();
    }

    void llenarDiccionario()
    {
        fstream myFile(*archivo);

        if(!myFile.is_open())
        {
            throw runtime_error("Error en la apertura del archivo"); //Quitar para que imprima el error y vuelva a pedir la ruta del archivo
            //cout << "Error en la apertura del archivo\nIngrese el nombre del archivo junto con su extensión. Por ejemplo '"C:/Users/PC/Desktop/Prueba.txt";'\nNombre: ";
            //cin >> file;
        }
        else
        {
            cout << "El archivo " <<  *archivo << " se abrió de manera correcta\n\n";
            int aux = 0;
            while (getline(myFile, linea))  //Mientras encuentre líneas
            {
                //cout << linea << "\n";
                if(linea != "")  //Se eliminan líneas en blanco
                {
                    //cout << aux << " " << linea << endl;
                    dict.insert(aux++, linea); //Se almacenan en el diccionario todas las líneas
                    //aux++; //Se aumenta el número que se usara de llave
                }
            }
            myFile.close();
        }
    }

    void imprimirDiccionario()
    {
        dict.print();
        system("pause");
        system("cls");
    }

    void llenarListaIgnorados()
    {
        fstream myFile("ignorar.txt");
        string linea;

        if(!myFile.is_open())
        {
            throw runtime_error("Error en la apertura del archivo");
        }
        else
        {
            //int aux = 0;
            while (getline(myFile, linea))  //Mientras encuentre líneas
            {
                //cout << linea << "\n";
                listaIgnorados->append(linea);
            }
            myFile.close();
        }
    }

    void imprimirTrie()
    {
        List<string> *lineas = dict.getValues();
        List<int> *numeros = dict.getKeys();
        numeros->goToStart();
        for (lineas->goToStart(); !lineas->atEnd(); lineas->next())
        {
            string line = lineas->getElement();
            int num = numeros->getElement();
            istringstream isstream(line);

            while(isstream >> line)   //Separa la linea cada vez que encuentra un espacio
            {
                line = minusculas(line);
                line = quitarIndeseados(line);
                if(!comprobarIgnorado(line))  //Si no está en la lista de ignorados
                {
                    if(line != "")
                        cout << num << " " << line << endl;
                }
            }
            numeros->next();
        }
        system("pause");
        system("cls");
    }

    string minusculas(string str)
    {
        str[0] = tolower(str[0]);
        return str;
    }

    bool comprobarIgnorado(string Palabra)
    {
        for(listaIgnorados->goToStart(); listaIgnorados->atEnd(); listaIgnorados->next()){
            if(Palabra == listaIgnorados->getElement())
            {
                return true;
            }
        }
        return false;
    }


    string quitarIndeseados(string Palabra)  //Función que toma una palabra y le quita cualquier caracter fuera del abecedario
    {
        string aux;
        int Switch = 0;
        const char CaracteresIndeseados[] =
        {
            '(', ')', ';', ',', '.', ':', '[', ']', '-', '<', '>', '_', '+', '#', '$', '%', '&', '/', '«', '"', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\''
        };
        for (unsigned int i = 0; i < Palabra.length(); i++)
        {
            for (unsigned int j = 0; j < strlen(CaracteresIndeseados); j++)
                if (Palabra[i] == CaracteresIndeseados[j])
                    Switch = 1;

            if (Switch == 0)
                aux += Palabra[i];
            Switch = 0;
        }
        return aux;
    }

    void llenarTrie()
    {
        List<string> *lineas = dict.getValues();
        List<int> *numeros = dict.getKeys();
        numeros->goToStart();

        int aux = 0;

        for (lineas->goToStart(); !lineas->atEnd(); lineas->next())
        {
            string line = lineas->getElement();
            int num = numeros->getElement();
            //cout << num++ << " " << line << endl; //Hasta acá funciona bien
            istringstream isstream(line);

            while(isstream >> line)   //Separa la linea cada vez que encuentra un espacio
            {
                line = minusculas(line);
                line = quitarIndeseados(line);
                //cout << num << " " << line << endl;
                if(!comprobarIgnorado(line))  //Si no está en la lista de ignorados
                {
                    if(line != "")
                    {
                        arbolPalabras.insert(num,line);
                        //cout << num << "insertando " << line << endl;
                    }
                }
                //arbolPalabras.insert(num,line);
            }
            //cout << num << endl;
            numeros->next();
            aux++;
        }
    }

    /*void lineasPalabra(){
        cout << "Ingrese la palabra a buscar"<<endl;
        string word; cin >> word;
        word = minusculas(word);
        //List<string> *lineas = dict.getValues();
        List<string> *lista = arbolPalabras.getMatches(word);
        List<int> *lineas = arbolPalabras.getLines(word);

        if (lista->getSize() != 0) {
            if (arbolPalabras.getLinesSize(lista->getElement()) == 1) {
                cout << word<< " se utiliza: "<< arbolPalabras.getLinesSize(lista->getElement())<< " vez" << endl;
            } else {
                cout << word<< " se utiliza: "<< arbolPalabras.getLinesSize(lista->getElement())<< " veces" << endl;

            }
        } else {
            cout<< "\nLa palabra " <<  word  << " no se encuentra en el texto " << endl;
        }
        cout << endl << endl;
        cout << "Lineas: ";
        for(lineas->goToStart(); !lineas->atEnd(); lineas->next()){
            cout << dict.getValue(lineas->getElement()) << endl;
        }

        delete lista;
        system("pause");
        system("cls");
    }*/


};

#endif // WORDS_H
