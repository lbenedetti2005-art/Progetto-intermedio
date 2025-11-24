#ifndef INERTIAL_DRIVER_H
#define INERTIAL_DRIVER_H

#include <iostream>
#include <array>
#include "MyVector.h"
using namespace std;

const int NUM_SENS=17;    //Numero di sensori
const int NUM_VAL=6;    //Numero di valori per sensore
const int BUFFER_DIM=5;  //Dimensione del buffer circolare

using lettura=array<double, NUM_VAL>;
using misura=array<lettura, NUM_SENS>;

class InertialDriver {
    private:
        MyVector<misura> elem; //Buffer circolare di letture
        int head;                                               //indice della testa del buffer (elemento più vecchio)
        int sz;                                                 //Numero di elementi nel buffer

    public:
        
        class Invalid{}; //Eccezione per operazioni non valide

        InertialDriver();//Costruttore

        void push_back(misura a); //Aggiunge una nuova misura al buffer

        misura pop_front(); //Elimina la misura più vecchia e la restituisce

        void clear_buffer();   //Svuota il buffer

        lettura get_reading(int sensor_index); //Ritorna la corrispondente lettura della misura più recente, senza cancellarla dal buffer
         
        friend ostream& operator<<(std::ostream& os, const InertialDriver& i);                  //stampa a schermo l’ultima misura salvata
        
        void print() const;

};

#endif