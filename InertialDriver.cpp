#include "InertialDriver.h"

using namespace std;

        InertialDriver::InertialDriver() : elem(0) ,sz{0}, head{0} //Costruttore
        {
            elem.reserve(BUFFER_DIM);
        }

        void InertialDriver::push_back(misura a) //Aggiunge una nuova misura al buffer
        {
                 int tail=(head+sz)%BUFFER_DIM;  //tail è l'indice dove inserire il nuovo elemento
                 elem[tail] = a;
                 head=(head+1)%BUFFER_DIM;
                    if(sz<BUFFER_DIM)
                        ++sz;
        }

        misura InertialDriver::pop_front() //Elimina la misura più vecchia e la restituisce
        {
            if(sz==0) throw Invalid();

            misura r=elem[head];
            head=(head+1)%BUFFER_DIM;
            --sz;
            return r;
        }

        void InertialDriver::clear_buffer()   //Svuota il buffer
        {
            elem = MyVector<misura>(0);
            elem.reserve(BUFFER_DIM);
            sz=0;
            head=0;
        }

        lettura InertialDriver::get_reading(int sensor_index) //Ritorna la corrispondente lettura della misura più recente, senza cancellarla dal buffer
        {
            if(sz==0) throw Invalid();

            if(sensor_index<0 || sensor_index>=NUM_SENS) throw Invalid();

            int latest_index=(head+sz-1)%BUFFER_DIM;
            return elem[latest_index][sensor_index];
        }

        std::ostream& operator<<(std::ostream& os, const InertialDriver& i)                  //stampa a schermo l’ultima misura salvata
        {
            if(i.sz==0) throw InertialDriver::Invalid();

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
            return os;
        }

        void InertialDriver::print() const
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