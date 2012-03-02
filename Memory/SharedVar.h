#ifndef SHAREDVAR_H
#define SHAREDVAR_H

#include "Serial.h"
#include <sstream>

/*

        IN THE FUTURE, THESE MUST BE REGISTERED TO A SERIALREGISTRY BEFORE THEY MAY BE USED
        also rename to SharedPointer

*/

template<class T>
class SharedVar
{
    public:
        SharedVar(const char& flag = 0){                        //Default
            m_value = new T();
        }
        SharedVar(T val, const char& flag = 0){
            m_value = new T(val);
        }                  //Create with a value
        SharedVar(const SharedVar& cpy){
            *m_value = *cpy.m_value;
            m_serial = cpy.m_serial;
        }    //Copy constructor
        virtual ~SharedVar(){
            delete m_value;
        }

        //A read that will fail if a write interrupts
        bool WeakRead(T& store_var) throw(Exception){
            if(SerialCompare(m_serial.Copy())){
                store_var = *m_value;

                return true;
            }else{
                return false;
            }
        }

        void StrongRead(T& store_var) throw(Exception){

            std::cout << "Serial compare ";
            while(!SerialCompare(m_serial.Copy())){}
            std::cout << "success\n";

            store_var = *m_value;
        }

        //Strong write ensures that a write will take place, unless an exception has occured
        void StrongWrite(const T& val) throw(Exception){

            while(!SerialCAS(m_value, *m_value, m_serial.Copy(), val)){}
        }
        //Weak write makes no guarentee that a write will be made and returns true if it succeeded and false if it did not
        bool WeakWrite(const T& val) throw(Exception){
            return SerialCAS(m_value, *m_value, m_serial.Copy(), val);
        }

        bool operator==(SharedVar<T> var) const throw(){
            T extval;
            T myval;

            try{
                extval = var.StrongRead();
                myval  = StrongRead();
            }

            catch(Exception e){
                //Should only output for debug purposes
                e.output();
                return false;
            }

            if(extval == myval && SerialCompare(m_serial.Copy())){
                return true;
            }

            return false;
        }


        SharedVar& operator=(const SharedVar& cpy){
            SharedVar newvar(cpy);
            return newvar;
        }

        const char GetSerialCopy(){
            return  m_serial.Copy();;
        }
    protected:
    private:
        Serial      m_serial;
        T*          m_value;

        void initialize(T val);

        bool SerialCAS(T* store, T expected, const unsigned char serial, T newval){
            T curval = *store;

            if(expected == curval && m_serial.Copy() == serial){
                m_serial++;
                *store = newval;
                return true;
            }else{
                return false;
            }
        }
        bool SerialCompare(const unsigned char expected_serial) const{
            //std::cout << "Serial compare: cpy " << (int)m_serial.GetKeyCopy() << " ==  ex " << (int)expected_serial << std::endl;
            if(m_serial.Copy() == expected_serial){
                return true;
            }else{
                return false;
            }
        }
};

#endif // SHAREDVAR_H
