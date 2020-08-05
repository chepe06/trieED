#ifndef WORDS_H
#define WORDS_H

#include <fstream>
#include <sstream>
#include <string.h>
#include "unsortedArrayDictionary.h"
#include "trie.h"
#include <limits>

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
                dict.insert(aux++, linea); //Se almacenan en el diccionario todas las líneas

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
        for(int i = 0; i < str.length(); i++){
            str[i] = tolower(str[i]);
        }
        return str;
    }

    bool comprobarIgnorado(string Palabra)
    {
        //cout << listaIgnorados->getSize();
        listaIgnorados->goToStart();
        for(int i = 0; i < listaIgnorados->getSize(); i++){
            if(Palabra == listaIgnorados->getElement())
            {
                return true;
            }
            listaIgnorados->next();
        }
        return false;
    }


    string quitarIndeseados(string Palabra)  //Función que toma una palabra y le quita cualquier caracter fuera del abecedario
    {
        string aux;
        int Switch = 0;
        const char CaracteresIndeseados[] =
        {
            '(', ')', ';', ',', '.', ':', '[', ']', '-', '<', '>', '_', '+', '#', '$', '%', '&', '/', '«', '"',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\'', '¿', '?', '!', '¡', '»'
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

    void lineasPalabra()
    {
        cout << "Ingrese la palabra a buscar"<<endl;
        string word; cin >> word;
        word = minusculas(word);
        List<int> *numLineas = dict.getKeys();
        List<string> *lista = arbolPalabras.getMatches(word);
        List<int> *lineas = arbolPalabras.getLines(word);

        if (lista->getSize() != 0)
        {
            if (arbolPalabras.getLinesSize(lista->getElement()) == 1)
            {
                cout << word<< " se utiliza: "<< arbolPalabras.getLinesSize(lista->getElement())<< " vez" << endl;
            }
            else
            {
                cout << word<< " se utiliza: "<< arbolPalabras.getLinesSize(lista->getElement())<< " veces" << endl;

            }
        }
        else
        {
            cout<< "\nLa palabra " <<  word  << " no se encuentra en el texto " << endl;
        }
        cout << endl;
        numLineas->goToStart();
        for(lineas->goToStart(); !lineas->atEnd(); lineas->next()){
            cout << "Linea " << lineas->getElement() << ": " << dict.getValue(lineas->getElement()) << endl;
        }

        delete lista;
        system("pause");
        system("cls");
    }

    void prefijos()  // busca un prefijo e imprime todas la palabras con el mismo y dice la cantidad de veces que se repite en el texto.
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
            cout<< "no existen palabras con ese prefijo"<< endl;
        }

        cout << " " << endl;
        delete lista;
        system("pause");
        system("cls");

    }

    void letras()   // busca palabras por su cantidad de letras espesificas y dice cuantas veces de utiliza esa palabra en el texto
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

    void masUsadas()
    {

        List<string> *lista = arbolPalabras.getMatches("");
        ArrayList<int> apariciones;

        cout << "Que cantidad del top palabras mas utilizada desea ver: "<< endl;
        int numero;
        while(!(cin >> numero)||numero<=0)
        {
            cout<< "por favor digite un numero: "<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }



        cout << "\nTop " << numero << " palabras mas usadas:" << endl << endl;
        for (lista->goToStart(); !lista->atEnd(); lista->next())
        {
            if(!apariciones.contains(arbolPalabras.getLinesSize(lista->getElement())))
            {
                apariciones.append(arbolPalabras.getLinesSize(lista->getElement()));
            }
        }

        apariciones.ordenarMayor();
        apariciones.goToStart();

        for (int i =0 ; i< numero; i++)
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

        cout << endl;
        delete lista;
        system("pause");
        system("cls");
    }

    void menosUsadas() // se puede conbinar coma mas usadas por medio de un parametro booleano!!
    {

        List<string> *lista = arbolPalabras.getMatches("");
        ArrayList<int> apariciones;

        cout << "Que cantidad del top palabras menos utilizada desea ver: "<< endl;
        int numero;
        while(!(cin >> numero)||numero<=0)
        {
            cout<< "por favor digite un numero: "<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }



        cout << "\nTop " << numero << " palabras menos usadas:" << endl << endl;
        for (lista->goToStart(); !lista->atEnd(); lista->next())
        {
            if(!apariciones.contains(arbolPalabras.getLinesSize(lista->getElement())))
            {
                apariciones.append(arbolPalabras.getLinesSize(lista->getElement()));
            }
        }

        apariciones.ordenarMenor();
        apariciones.goToStart();

        for (int i =0 ; i< numero; i++)
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
        cout << endl;

        delete lista;
        system("pause");
        system("cls");
    }

};

#endif // WORDS_H
