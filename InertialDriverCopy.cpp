#include <iostream>
#include "MyVector.h"
using namespace std;

const int NUM_SENS=17;    //Numero di sensori
const int NUM_VAL=6;    //Numero di valori per sensore
const int BUFFER_DIM=5;  //Dimensione del buffer circolare

class InertialDriver {
    private:
        MyVector<array<array<double, NUM_VAL>, NUM_SENS>> elem; //Buffer circolare di letture
        int head;                                               //indice della testa del buffer (elemento più vecchio)
        int sz;                                                 //Numero di elementi nel buffer

    public:
        
        class Invalid{}; //Eccezione per operazioni non valide

        InertialDriver() : sz{0}, head{0} //Costruttore
        {
            elem.reserve(BUFFER_DIM);
        }

        ~InertialDriver() //Distruttore
        {
            clear_buffer();
        }
    
        void push_back(array<array<double, NUM_VAL>, NUM_SENS> a) //Aggiunge una nuova misura al buffer
        {
            int tail=(head+sz)%BUFFER_DIM; //tail è l'indice dove inserire il nuovo elemento
            if(tail<sz) {
                 elem.push_back(a);
            } else {
                 elem[tail] = a;
            }
            if (sz==BUFFER_DIM)         //Se il buffer è pieno, sovrascrivo l'elemento più vecchio
                 head=(head+1)%BUFFER_DIM;
            else
            ++sz;
        }

        array<array<double, NUM_VAL>, NUM_SENS> pop_front() //Elimina la misura più vecchia e la restituisce
        {
            if(sz==0) throw Invalid();

            array<array<double, NUM_VAL>, NUM_SENS> r=elem[head];
            head=(head+1)%BUFFER_DIM;
            --sz;
            return r;
        }

        void clear_buffer()   //Svuota il buffer
        {
            elem.clear();
            sz=0;
            head=0;
        }

        array<double, NUM_VAL> get_reading(int sensor_index) //Ritorna la corrispondente lettura della misura più recente, senza cancellarla dal buffer
        {
            if(sz==0) throw Invalid();

            if(sensor_index<0 || sensor_index>=NUM_SENS) throw Invalid();

            int latest_index=(head+sz-1)%BUFFER_DIM;
            return elem[latest_index][sensor_index];
        }

        std::ostream& operator<<(std::ostream& os, const InertialDriver& i)                  //stampa a schermo l’ultima misura salvata
        {
            if(i.sz==0) throw Invalid();

            int latest_index=(i.head+i.sz-1)%BUFFER_DIM;
            for(int s=0; s<NUM_SENS; ++s)
            {
                cout<<"Sensor"<<s<<":";
                for(int v=0; v<NUM_VAL; ++v)
                {
                    cout<<i.elem[latest_index][s][v]<<" ";
                }
                cout<<endl;
            }
            return cout;
        }

        void print() const
        {
            if(sz==0) throw Invalid();

            int index=head;
            for(int i=0; i<sz; ++i)
            {
                for(int s=0; s<NUM_SENS; ++s)
                {
                 cout<<"Sensor"<<s<<":";
                 for(int v=0; v<NUM_VAL; ++v)
                    {
                        cout<<elem[index][s][v]<<" ";
                    }
                    cout<<endl;
                }
                index=(index+1)%BUFFER_DIM;
            }   
        }   

};