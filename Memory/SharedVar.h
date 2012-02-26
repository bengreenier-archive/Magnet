#ifndef SHAREDVAR_H
#define SHAREDVAR_H

#include "../Game/Serial.h"

template<class T>
class SharedVar
{
    public:
        SharedVar();                        //Default
        SharedVar(T val);                   //Create with a value
        SharedVar(const SharedVar& cpy);    //Copy constructor
        virtual ~SharedVar();

        const T& GetValue() throw(Exception);
        //Strong write ensures that a write will take place, unless an exception has occured
        void StrongWrite(T& val) throw(Exception);
        //Weak write makes no guarentee that a write will be made and returns true if it succeeded and false if it did not
        bool WeakWrite(T& val) throw(Exception);

        bool operator==(SharedVar<T> var) const throw(){
            T extval;
            T myval;

            try{
                extval = var.GetValue();
                myval  = GetValue();
            }

            catch(Exception e){
                //Should only output for debug purposes
                e.output();
                return false;
            }

            if(extval == myval && SerialCompare(m_serial.GetKeyCopy())){
                return true;
            }

            return false;
        }


        SharedVar& operator=(const SharedVar& cpy){
            SharedVar newvar(cpy);
            return newvar;
        }
        T operator=(const T& val){
            while(!SerialCAS(m_value, *m_value, m_serial.GetKeyCopy(), val)){}
            return *m_value;
        }

    protected:
    private:
        Serial    m_serial;
        T*          m_value;

        void initialize(T val);

        bool SerialCAS(T* store, T expected, const unsigned char serial, T newval);
        bool SerialCompare(const unsigned char expected_serial);
};

#endif // SHAREDVAR_H
