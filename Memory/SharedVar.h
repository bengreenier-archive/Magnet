#ifndef SHAREDVAR_H
#define SHAREDVAR_H

#include "Serial.h"
#include <sstream>

/*

        IN THE FUTURE, THESE MUST BE REGISTERED TO A SERIALREGISTRY BEFORE THEY MAY BE USED
        also rename to SharedPointer

*/


/*
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
            while(!SerialCompare(m_serial.Copy())){}
            delete m_value;
        }

        //A read that will fail if a write interrupts
        bool WeakRead(T& store_var) const throw(Exception){
            if(SerialCompare(m_serial.Copy())){
                store_var = *m_value;

                return true;
            }else{
                return false;
            }
        }

        const T& StrongRead() const throw(Exception){
            T&          exp           = *m_value;
            Serial::serial_t    exp_serial    = m_serial.Copy();

            while(!SerialCompare(exp_serial) && exp != *m_value){
                exp = *m_value;
                //if(GlobalConfig::GetConfig("memory")->GetVar("debug")->GetBool())
                std::cout << "StrongRead failed, getting new val. Serial " << m_serial.Copy() << " != " << exp_serial << std::endl;
                exp_serial = m_serial.Copy();
            }


            return exp;
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

        const uint8_t GetSerialCopy(){
            return  m_serial.Copy();;
        }
    protected:
    private:
        Serial               m_serial;
        volatile T*          m_value;

        void initialize(T val);

        bool SerialCAS(T* store, T expected, const uint8_t serial, T newval){
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
*/
#endif // SHAREDVAR_H

