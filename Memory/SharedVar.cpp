#include "SharedVar.h"
#include <sstream>

template<class T>
SharedVar<T>::SharedVar()
{
    m_value = new T();
}

template<class T>
SharedVar<T>::SharedVar(T val)
{
    m_value = new T(val);
}

template<class T>
SharedVar<T>::SharedVar(const SharedVar& cpy){
    *m_value = *cpy.m_value;
    m_serial = cpy.m_serial;
}

template<class T>
SharedVar<T>::~SharedVar()
{
    delete m_value;
}

template<class T>
const T& SharedVar<T>::GetValue() throw(Exception){
    if(m_serial.IsFlagged(SERIAL_MODIFIED)){
        m_serial.Unflag(SERIAL_MODIFIED);
    }else{
        if(m_serial.IsFlagged(SERIAL_READ_ONCE)){
            std::stringstream ss;
            ss << (int)m_serial.GetFlagsCopy();
            throw Exception(Exception::SharedReadDenied, "read denied", "this shared varaible doesn't have permission to read (FLAGS: " + ss.str() + ")");
        }
    }

    return *m_value;
}

template<class T>
void SharedVar<T>::StrongWrite(T& val) throw(Exception){
    if(m_serial.IsFlagged(SERIAL_MODIFIED)){
        if(m_serial.IsFlagged(SERIAL_WRITE_ONCE)){
            std::stringstream ss;
            ss << (int)m_serial.GetFlagsCopy();
            throw Exception(Exception::SharedWriteDenied, "write denied", "this shared varaible doesn't have permission to write (FLAGS: " + ss.str() + ")");
        }
    }

    while(!SerialCAS(m_value, *m_value, m_serial.GetSerialCopy(), val)){}
}

template<class T>
bool SharedVar<T>::WeakWrite(T& val) throw(Exception){
    if(m_serial.IsFlagged(SERIAL_MODIFIED)){
        if(m_serial.IsFlagged(SERIAL_WRITE_ONCE)){
            std::stringstream ss;
            ss << (int)m_serial.GetFlagsCopy();
            throw Exception(Exception::SharedWriteDenied, "write denied", "this shared varaible doesn't have permission to write (FLAGS: " + ss.str() + ")");
        }
    }

    return SerialCAS(m_value, *m_value, m_serial.GetSerialCopy(), val);
}

template<class T>
bool SharedVar<T>::SerialCAS(T* store, T expected, const unsigned char serial, T newval){
    T curval = *store;

    if(expected == curval && m_serial.GetKeyCopy() == serial){
        *store = newval;
        m_serial.SetSerial(m_serial.GetSerialCopy()+1);
        m_serial.Flag(SERIAL_MODIFIED);
        return true;
    }else{
        return false;
    }
}

template<class T>
bool SharedVar<T>::SerialCompare(const unsigned char expected_serial){
    if(m_serial.GetKeyCopy() == expected_serial){
        return true;
    }else{
        return false;
    }
}
