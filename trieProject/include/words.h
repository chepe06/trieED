#ifndef WORDS_H
#define WORDS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "unsortedArrayDictionary.h"
#include "trie.h"
#include <limits>
#include "arrayList.h"

using namespace std;
class words
{
private:
    string archivo;
    UnsortedArrayDictionary<int, string> dict;
    Trie arbolPalabras;
    Trie listaIgnorados;
    ArrayList<string> nuevasIgnoradas;

public:
    words()
    {
        verificarArchivo();
        llenarIgnorados();
        llenarDiccionario();
        llenarTrie();
    }
    //Jafet, Álvaro
    void verificarArchivo() //Verifica que el archivo digitado se pueda leer y muestra error hasta que el usuario lo corrija
    {
        bool abierto = false;
        while(!abierto)
        {
            cout << "Bienvenido al proyecto programado de Estructuras de Datos.\nEste proyecto cuenta con el propósito de realizar un programa de consola en modo texto.\n\nSe va a procesar el documento de texto que indique a continuación.\nEl documento .txt debe estar codificado en el formato ANSI.\n\n";
            cout << "Ingrese el nombre del archivo junto con su extensión. Por ejemplo \'C:/Users/PC/Desktop/Prueba.txt\'\nNombre: ";
            cin >> archivo;

            fstream myFile(archivo);
            if(!myFile.is_open())
            {
                cout << "\nError en la apertura del archivo " << archivo << endl << endl;
                system("pause");
                system("cls");
            }
            else
            {
                cout << "\nEl archivo " <<  archivo << " se abrió de manera correcta\n\n";
                abierto = true;
            }
        }
    }

    //Jafet y Priscilla
    void llenarDiccionario() //Llena el diccionario con las lineas del documento
    {
        system("pause");
        string linea;
        fstream myFile(archivo); //string linea;
        int aux = 0;
        while (getline(myFile, linea))  //Mientras encuentre líneas
        {
            dict.insert(aux++, linea); //Se almacenan en el diccionario todas las líneas

        }
        myFile.close();
    }

    //Jafet
    void llenarIgnorados() //Llena el Trie con las palabras del archivo ignorar.txt
    {
        fstream myFile("ignorar.txt");
        string linea;

        if(!myFile.is_open())
        {
            throw runtime_error("Error en la apertura del archivo");
        }
        else
        {
            listaIgnorados.clear();
            while (getline(myFile, linea))  //Mientras encuentre líneas
            {
                listaIgnorados.insert(0,linea,false);
            }
            myFile.close();
        }
    }

    //Priscilla
    string minusculas(string str) //Cambia las letras mayúsculas por minúsculas en una palabra
    {
        for(int i = 0; i < str.length(); i++)
        {
            str[i] = tolower(str[i]);
        }
        return str;
    }

    //Jafet
    string quitarIndeseados(string str) //Función que toma una palabra y le quita ciertos carácteres
    {
        string aux;
        int Switch = 0;
        const char CaracteresIndeseados[] =
        {
            '(', ')', ';', ',', '.', ':', '[', ']', '-', '<', '>', '_', '+', '#', '$', '%', '&', '/', '«', '"',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\'', '¿', '?', '!', '¡', '»', '{', '}', '^',
        };
        for (unsigned int i = 0; i < str.length(); i++)
        {
            for (unsigned int j = 0; j < strlen(CaracteresIndeseados); j++)
                if (str[i] == CaracteresIndeseados[j])
                    Switch = 1;

            if (Switch == 0)
                aux += str[i];
            Switch = 0;
        }
        return aux;
    }

    //Jafet
    void llenarTrie() //Llena el Trie con las palabras de las líneas del diccionario
    {
        List<string> *lineas = dict.getValues();
        List<int> *numeros = dict.getKeys();
        numeros->goToStart();

        int aux = 0;

        for (lineas->goToStart(); !lineas->atEnd(); lineas->next())
        {
            string line = lineas->getElement();
            int num = numeros->getElement();

            istringstream isstream(line);
            while(isstream >> line)   //Separa la linea cada vez que encuentra un espacio
            {
                line = minusculas(line);
                line = quitarIndeseados(line);
                if(!listaIgnorados.containsWord(line))
                {
                    if(line != "")
                    {
                        arbolPalabras.insert(num,line,true);
                    }
                }
            }
            numeros->next();
            aux++;
        }
    }

    //Priscilla
    void lineasPalabra() //Busca una palabra y muestra la cantidad de veces que aparece en el texto junto con el texto de las líneas
    {
        cout << "Ingrese la palabra a buscar"<<endl;
        string word;
        cin >> word;
        word = minusculas(word);
        List<int> *numLineas = dict.getKeys();
        List<int> *lineas = arbolPalabras.getLines(word);

        if (arbolPalabras.containsWord(word))
        {
            if (arbolPalabras.getLinesSize(word) == 1)
            {
                cout << word<< " se utiliza: "<< arbolPalabras.getLinesSize(word)<< " vez" << endl;
            }
            else
            {
                cout << word<< " se utiliza: "<< arbolPalabras.getLinesSize(word)<< " veces" << endl;

            }
            cout << endl;
            numLineas->goToStart();
            for(lineas->goToStart(); !lineas->atEnd(); lineas->next())
            {
                cout << "Linea " << lineas->getElement() << ": " << dict.getValue(lineas->getElement()) << endl;
            }
        }
        else
        {
            cout<< "\nLa palabra " <<  word  << " no se encuentra en el texto " << endl;
        }
        system("pause");
        system("cls");
    }

    //Álvaro
    void prefijos() //Busca un prefijo e imprime todas la palabras con el mismo y dice la cantidad de veces que se repite en el texto
    {
        cout << "Escriba un prefijo \nPrefijo: ";
        string prefijo;
        cin >> prefijo;

        List<string> *lista = arbolPalabras.getMatches(prefijo);
        if(lista->getSize()!= 0)
        {
            cout << "\nPalabras que empiezan con: "<< prefijo << endl << endl;
            for (lista->goToStart(); !lista->atEnd(); lista->next())
            {
                if (arbolPalabras.getLinesSize(lista->getElement())==1)
                {
                    cout << lista->getElement() << " se repite: "<< arbolPalabras.getLinesSize(lista->getElement())<< " vez" << endl;
                }
                else
                {
                    cout << lista->getElement() << " se repite: "<< arbolPalabras.getLinesSize(lista->getElement())<< " veces" << endl;
                }
            }
        }
        else
        {
            cout<< "No existen palabras con ese prefijo"<< endl;
        }

        cout << " " << endl;
        delete lista;
        system("pause");
        system("cls");

    }

    //Álvaro y Priscilla
    void letras() //Busca palabras según su cantidad de letras y dice cuantas veces aparece esta palabra
    {
        List<string> *lista = arbolPalabras.getMatches("");

        cout << "Por favor digite un numero entero positivo"<< endl;
        int numero;
        while(!(cin >> numero)||numero<=0)
        {
            cout<< "por favor digite un numero: "<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        int contador;
        contador = 0;
        cout << "\nPalabras con " << numero << " de letras:" << endl << endl;
        for (lista->goToStart(); !lista->atEnd(); lista->next())
        {
            string word;
            word = lista->getElement();
            if (word.length()== numero)
            {
                contador++;
                if (arbolPalabras.getLinesSize(lista->getElement())==1)
                {
                    cout << lista->getElement() << " se utiliza: "<< arbolPalabras.getLinesSize(lista->getElement())<< " vez" << endl;
                }
                else
                {
                    cout << lista->getElement() << " se utiliza: "<< arbolPalabras.getLinesSize(lista->getElement())<< " veces" << endl;
                }

            }
        }
        if (numero==1)
        {
            if (contador == 0)
            {
                cout << "No existen palabras con " << numero << " letra."<< endl<< endl;
            }
        }
        else
        {
            if (contador == 0)
            {
                cout << "No existen palabras con " << numero << " letras."<< endl<< endl;
            }
        }
        cout << " " << endl;
        delete lista;
        system("pause");
        system("cls");
    }

    //Álvaro
    void top(bool mayorMenor) //Muestra el top de palabras más o menos utilizadas
    {
        List<string> *lista = arbolPalabras.getMatches("");
        ArrayList<int> apariciones;
        cout << "Que cantidad del top desea ver: "<< endl;
        int numero;
        while(!(cin >> numero)||numero<=0)
        {
            cout<< endl << "Debe ingresar un número"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("pause");
            system("cls");
            cout << "Que cantidad del top desea ver: "<< endl;
        }

        if(numero < lista->getSize())
        {
            cout << "\nTop " << numero << "de palabras:" << endl << endl;
            for (lista->goToStart(); !lista->atEnd(); lista->next())
            {
                if(!apariciones.contains(arbolPalabras.getLinesSize(lista->getElement())))
                {
                    apariciones.append(arbolPalabras.getLinesSize(lista->getElement()));
                }
            }
            if(mayorMenor)
            {
                apariciones.ordenarMayor();
            }
            else
            {
                apariciones.ordenarMenor();
            }
            apariciones.goToStart();
            for (int i = 0 ; i < numero; i++)
            {
                int contador = 0;
                for (lista->goToStart(); !lista->atEnd(); lista->next())
                {
                    if (contador==0)
                    {
                        if ( arbolPalabras.getLinesSize(lista->getElement()) == apariciones.getElement())
                        {
                            contador++;

                            if (arbolPalabras.getLinesSize(lista->getElement())==1)
                            {
                                cout << lista->getElement() << " se utiliza: "<< arbolPalabras.getLinesSize(lista->getElement())<< " vez" << endl;
                            }
                            else
                            {
                                cout << lista->getElement() << " se utiliza: "<< arbolPalabras.getLinesSize(lista->getElement())<< " veces" << endl;
                            }
                        }
                    }
                    else
                    {
                        if ( arbolPalabras.getLinesSize(lista->getElement()) == apariciones.getElement())
                        {
                            i++;
                            if(i == numero )
                            {
                                break;
                            }
                            contador++;

                            if (arbolPalabras.getLinesSize(lista->getElement())==1)
                            {
                                cout << lista->getElement() << " se utiliza: "<< arbolPalabras.getLinesSize(lista->getElement())<< " vez" << endl;
                            }
                            else
                            {
                                cout << lista->getElement() << " se utiliza: "<< arbolPalabras.getLinesSize(lista->getElement())<< " veces" << endl;
                            }
                        }
                    }
                }
                apariciones.next();
            }
        }
        else
        {
            cout << "Debe indicar un número menor a " << lista->getSize();
        }

        cout << endl << endl;
        delete lista;
        system("pause");
        system("cls");
    }

    //David
    void agregarIgnorados() //Función que le permite al usuario escribir en el texto
    {
        setlocale(LC_CTYPE, "Spanish");
        ofstream archivo_ignorado;
        string palabra;

        archivo_ignorado.open("ignorar.txt",ios::app); //Se abre en modo añadir, no lo sobre escribe

        if(archivo_ignorado.is_open())
        {
            cout << "Escriba una palabra: "<< endl;
            cin.ignore();
            getline(cin, palabra);
            cout << endl;
            istringstream isstream(palabra);

            while(isstream >> palabra)   //Separa la linea cada vez que encuentra un espacio
            {
                if(!listaIgnorados.containsWord(palabra))
                {
                    archivo_ignorado<<palabra<<endl;
                    listaIgnorados.insert(0,palabra,false);
                    nuevasIgnoradas.append(palabra);
                    arbolPalabras.remove(palabra);
                    cout << "Se agregó la palabra " << palabra << " al archivo de ignorados" << endl;
                }
                else
                {
                    cout << "La palabra " << palabra << " ya está en el archivo de ignorados" << endl;
                }
            }
        }
        else
        {
            throw runtime_error("Error Archivo no abierto");
        }
        archivo_ignorado.close();//Cerrando el archivo
        cout << endl;
        nuevasIgnoradas.print();
        system("pause");
        system("cls");
    }

    //David
    void borrarIgnorados()  //Borra las palabras ingresadas por el usuario
    {
        {
            ofstream file;
            file.open("copia.txt"); //Crea un nuevo txt
            List<string> *lista = listaIgnorados.getMatches("");
            lista->goToStart();
            for(int i = 0; i < lista->getSize(); i++)
            {
                if(!nuevasIgnoradas.contains(lista->getElement()))
                {
                    file << lista->getElement()<<endl; //Mete solo las palabras originales del ignorar.txt
                }
                lista->next();
            }
            file.close();

            remove("ignorar.txt"); //Borra el txt
            rename("copia.txt","ignorar.txt");
            remove("copia.txt");

            nuevasIgnoradas.goToStart();
            for(int i = 0; i < nuevasIgnoradas.getSize(); i++)
            {
                arbolPalabras.insert(0, nuevasIgnoradas.getElement(), false);
                nuevasIgnoradas.next();
            }
            cout << "Se limpió el archivo de ignorados" << endl;
            system("pause");
            system("cls");
        }
    }
};

#endif // WORDS_H
