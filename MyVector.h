#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <exception>
#include <string>

template<typename T>
class MyVector{
    
    private:
        int sz;             //Numero di elementi
        int space;          //Capacità del buffer
        T *elem;            //Puntatore agli elementi

    public:

        class Invalid{};                                                 //Eccezione per accesso non valido
        explicit MyVector(int s);                                        //Costruttore
        MyVector(std::initializer_list<T> lst);                          //Costruttore che prende in input una lista
       
        ~MyVector() { delete[] elem;}                                    //Distruttore

        MyVector(const MyVector& arg);                                   //Costruttore di copia
        MyVector& operator=(const MyVector& a);                          //Assegnamento di copia
        
        MyVector(MyVector&& a);                                          //Move constructor
        MyVector& operator=(MyVector&& a);                               //Move assignment

        T& operator[] (int n);               //Accesso al vettore tramite reference
        const T& operator[] (int n) const;   //Overloading su const
       
        void push_back(const T& d);      //Aggiunge un elemento

        void pop_back();                 //Elimina l'ultimo elemento

        T& at(int n);                    //Restituisce l'elemento in posizione n
        const T& at(int n) const;        //Overloading su const

        void reserve(int n);             //Riserva spazio in memoria

        int size() const { return sz;}

        int capacity() const {return space;}

        void print() const;


};

#include "MyVector.hpp"
#endif  // MYVECTOR_H
