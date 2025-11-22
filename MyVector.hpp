#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP
#include "MyVector.h"
#include <initializer_list>
#include <algorithm>
#include <iostream>

        template <typename T>
        MyVector<T>::MyVector(int s): sz {s}, space{s}, elem {new T[s]} //Costruttore
        {
            if(s==0) elem = nullptr;
            for(int i=0; i<s; ++i)
                elem[i]=0;
        }

        template <typename T>
        MyVector<T>::MyVector(std::initializer_list<T> lst) : sz{lst.size()}, space{lst.size()}, elem {new T[space]} //Costruttore che prende in input una lista
        {
            std:: copy(lst.begin(), lst.end(), elem);
        }

        template <typename T>
        MyVector<T>::MyVector(const MyVector& arg) : sz{arg.size()}, space{arg.capacity()}, elem{new T[space]} //Costruttore di copia
        {
            std::copy(arg.elem, arg.elem+sz, elem);
        }

        template <typename T>
        MyVector<T>::~MyVector() //Distruttore
        { 
            delete[] elem; 
        }

        template <typename T>
       MyVector<T>&  MyVector<T>::operator=(const MyVector& a) //Assegnamento di copia
        {
            if(this==&a) return *this;
            
            T *p=new T[a.sz];
            copy(a.elem, a.elem+a.sz, p);
            delete[] elem;
            sz=a.sz;
            space=a.space;
            elem=p;
            return *this;
        }
        
        template <typename T>
        MyVector<T>::MyVector(MyVector&& a) : sz{a.sz}, space{a.space}, elem{a.elem} //Move constructor
        {
            a.sz=0;
            a.space=0;
            a.elem=nullptr;
        }

        template <typename T>
        MyVector<T>&  MyVector<T>::operator=(MyVector&& a) //Move assignment
        {
            if(this==&a) return *this;

            delete[] elem;
            elem=a.elem;
            sz=a.sz;
            space=a.space;
            a.elem=nullptr;
            a.sz=0;
            a.space=0;
            return *this;
        }

        template <typename T>
        T&  MyVector<T>::operator[] (int n) //Accesso al vettore tramite reference
        {
            if(n>=sz || n<0) throw Invalid();
            return elem[n];
        }

        template <typename T>
        const T& MyVector<T>::operator[] (int n) const //Overloading su const
        {
            if(n>=sz || n<0) throw Invalid();
            return elem[n];
        }

        template <typename T>
        void MyVector<T>::push_back(const T& d) //Aggiunge un elemento
        {
            reserve(sz+1);      //if(sz == space) reserve(space > 0 ? 2*space : 1);
            elem[sz++]=d;
        }

        template <typename T>
        void MyVector<T>::pop_back()          //Elimina l'ultimo elemento
        {
            if(sz==0) throw Invalid();
            --sz;
        }

        template <typename T>
        T& MyVector<T>::at(int n)        //Restituisce l'elemento in posizione n
        {
            if(n>=sz || n<0) throw Invalid();
            return elem[n];
        }

        template <typename T>
        const T& MyVector<T>::at(int n) const   //Overloading su const
        {
            if(n>=sz || n<0) throw Invalid();
            return elem[n];
        }

        template <typename T>
        void  MyVector<T>::reserve(int n)     //Riserva spazio in memoria
        {
            if(space>=n) return;

            T *p=new T[n];
            for(int i=0; i<sz; ++i)
                p[i]=elem[i];
            delete[] elem;
            elem=p;
            space=n;
        }

        template <typename T>
        void MyVector<T>::print() const  //Stampa gli elementi del vettore
        {
            for (int i = 0; i < sz; ++i) 
            {
                cout<<elem[i];
                if (i + 1 < sz)cout<<' ';
            }
            cout<<'\n';
        }

        #endif  // MYVECTOR_HPP