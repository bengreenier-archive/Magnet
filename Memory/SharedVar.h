#ifndef SHAREDVAR_H
#define SHAREDVAR_H

#include "Serial.h"
#include <sstream>

template<class T>
class SharedVar
{
    public:
        SharedVar(const char& flag = 0){                        //Default
            m_value = new T();
            m_serial.Flag(flag);
        }
        SharedVar(T val, const char& flag = 0){
            m_value = new T(val);
            m_serial.Flag(flag);
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
            CheckReadFlags();

            if(SerialCompare(m_serial.GetSerialCopy())){
                if(m_serial.IsFlagged(SERIAL_MODIFIED)){
                    m_serial.Unflag(SERIAL_MODIFIED);
                }

                store_var = *m_value;

                return true;
            }else{
                return false;
            }
        }

        void StrongRead(T& store_var) throw(Exception){
            std::cout << "Checking flags";
            CheckReadFlags();
            std::cout << " success\n";

            std::cout << "Serial compare ";
            while(!SerialCompare(m_serial.GetSerialCopy())){}
            std::cout << "success\n";

            if(m_serial.IsFlagged(SERIAL_MODIFIED)){
                m_serial.Unflag(SERIAL_MODIFIED);
            }

            store_var = *m_value;
        }

        //Strong write ensures that a write will take place, unless an exception has occured
        void StrongWrite(const T& val) throw(Exception){
            CheckWriteFlags();

            while(!SerialCAS(m_value, *m_value, m_serial.GetSerialCopy(), val)){}
        }
        //Weak write makes no guarentee that a write will be made and returns true if it succeeded and false if it did not
        bool WeakWrite(const T& val) throw(Exception){
            CheckWriteFlags();
            return SerialCAS(m_value, *m_value, m_serial.GetSerialCopy(), val);
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

            if(extval == myval && SerialCompare(m_serial.GetSerialCopy())){
                return true;
            }

            return false;
        }


        SharedVar& operator=(const SharedVar& cpy){
            SharedVar newvar(cpy);
            return newvar;
        }

        const char GetSerialCopy(){
            return  m_serial.GetSerialCopy();;
        }
    protected:
    private:
        Serial      m_serial;
        T*          m_value;

        void initialize(T val);

        void CheckWriteFlags() const throw(Exception){
            if(m_serial.IsFlagged(SERIAL_MODIFIED)){
                if(m_serial.IsFlagged(SERIAL_WRITE_ONCE)){
                    std::stringstream ss;
                    ss << (int)m_serial.GetFlagsCopy();
                    throw Exception(Exception::SharedWriteDenied, "write denied", "this shared varaible doesn't have permission to write (FLAGS: " + ss.str() + ")");
                }
            }
        }
        void CheckReadFlags() const throw(Exception){
            if(!m_serial.IsFlagged(SERIAL_MODIFIED)){
                if(m_serial.IsFlagged(SERIAL_READ_ONCE)){
                    std::stringstream ss;
                    ss << (int)m_serial.GetFlagsCopy();
                    throw Exception(Exception::SharedReadDenied, "read denied", "this shared varaible doesn't have permission to read (FLAGS: " + ss.str() + ")");
                }
            }
        }

        bool SerialCAS(T* store, T expected, const unsigned char serial, T newval){
            T curval = *store;

            if(expected == curval && m_serial.GetSerialCopy() == serial){
                m_serial.SetSerial(m_serial.GetSerialCopy()+1);
                m_serial.Flag(SERIAL_MODIFIED);
                *store = newval;
                return true;
            }else{
                return false;
            }
        }
        bool SerialCompare(const unsigned char expected_serial) const{
            //std::cout << "Serial compare: cpy " << (int)m_serial.GetKeyCopy() << " ==  ex " << (int)expected_serial << std::endl;
            if(m_serial.GetSerialCopy() == expected_serial){
                return true;
            }else{
                return false;
            }
        }
};

#endif // SHAREDVAR_H
