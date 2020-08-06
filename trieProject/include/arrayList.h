#ifndef ARRAYLIST_H_INCLUDED
#define ARRAYLIST_H_INCLUDED

#define MAX_SIZE 10000
#include <iostream>
#include "List.h"
#include <stdexcept>

using namespace std;

template<typename E>
class ArrayList:public List<E>
{
private:
    E *elements;
    E* NuevaLista;
    int max;
    int pos;
    int size;

    //Función que revisa si la lista está llena
    void full()
    {
        if(size==max)
            throw runtime_error("List is full");
    }

public:
    //constructor
    ArrayList(int max = MAX_SIZE)
    {
        if(max<=0)
            throw runtime_error("Invalid max size");
        elements = new E[max];
        this->max = max;
        pos = 0;
        size = 0;
    }
    //destructor
    ~ArrayList()
    {
        delete[] elements;
    }

    void insert(E element)
    {
        if (size==max)
        {
            duplicaLista();
        }
        for (int i=size; i>pos; i--)
        {
            elements[i]=elements[i-1];
        }
        for(int i = size-1; i >= pos; i--)
        {
            elements[i+1] = elements[i];
        }
        elements[pos] = element;
        size++;
    }

    void append(E element)
    {
        if (size == max)
        {
            duplicaLista();
        }
        elements[size]= element;
        size++;
    }

    void duplicaLista()
    {
        NuevaLista = new E[max*2];
        for( int i = 0 ; i < size ; i++)
        {
            NuevaLista [i] = elements[i];
        }
        delete [] elements;
        max = max*2;
        elements = NuevaLista;
    }

    E getElement()
    {
        if(pos < 0 || pos >= size)
        {
            throw runtime_error("Index out of bounds");
        }
        return elements[pos];
    }

    E remove()
    {
        if(size == 0)
            throw runtime_error("List is empty");
        if(pos == size)
            throw runtime_error("No current element");
        E res = elements[pos];
        for(int i=pos; i<size; i++)
            elements[i]=elements[i+1];
        size--;
        return res;
    }

    void clear()
    {
        size = 0;
        pos = 0;
        delete [] elements;
        elements = new E[max];
    }

    void goToStart()
    {
        pos = 0;
    }

    void goToEnd()
    {
        pos = size;
    }

    void goToPos(int Pos)
    {
        pos = Pos;
    }

    void next()
    {
        if(pos < size)
        {
            pos++;
        }
    }

    void previous()
    {
        if(pos > 0)
        {
            pos--;
        }
    }

    bool atEnd()
    {
        return pos == size;
    }

    bool atStart()
    {
        return pos == 0;
    }

    int getPos()
    {
        return pos;
    }

    int getSize()
    {
        return size;
    }

    int getMax()
    {
        return max;
    }

    bool contains(E element)
    {
        for(goToStart(); !atEnd(); next())
        {
            if(getElement() == element)
            {
                return true;
            }
        }
        return false;
    }

    int indexOf(E element)
    {
        if(contains(element))
        {
            return getPos();
        }
        return -1;
    }

    void print()
    {
        for(int i = 0; i < size; i++)
        {
            cout << elements[i] << " ";
        }
    }

    //Álvaro
    void ordenarMayor() //Realiza un ordenamiento de mayor a menor
    {
        int Temp;
        for(int i=0; i<size; i++)
            for(int j=0; j<size-1; j++)
                if(elements[j]<elements[j+1])
                {
                    Temp=elements[j];
                    elements[j]=elements[j+1];
                    elements[j+1]=Temp;
                }
    }

    //Álvaro
    void ordenarMenor() ////Realiza un ordenamiento de menor a mayor
    {
        int Temp;
        for(int i=0; i<size; i++)
            for(int j=0; j<size-1; j++)
                if(elements[j]>elements[j+1])
                {
                    Temp=elements[j];
                    elements[j]=elements[j+1];
                    elements[j+1]=Temp;
                }
    }
};


#endif // ARRAYLIST_H_INCLUDED
