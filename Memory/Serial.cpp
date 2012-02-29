#include "Serial.h"

/*
SerialRegistry32::SerialRegistry32(size_t reserved)
{
    m_reg_reserve_size = reserved;
    m_serial_reserve_size = sizeof(Serial);
    std::cout << "[SerialRegistry32] Creating new serial registry.\n";
    std::cout << "[SerialRegistry32] Serial size is: " << sizeof(Serial) << std::endl;
    std::cout << "[SerialRegistry32] Registry size is: " << m_reg_reserve_size << std::endl;
    std::cout << "[SerialRegistry32] Registry can contain  " << m_reg_reserve_size/m_serial_reserve_size << " serials\n";

    if((Serial::GetMaxIndex() * m_serial_reserve_size) < m_reg_reserve_size){
        throw(Exception(Exception::SerialUnderflow, "serial registry underflow", "too much memory was reserved for registry. (Indices will not be unique)"));
    }
    m_registry.insert(new Serial(0));
    m_registry.insert(new Serial(1));
    m_registry.insert(new Serial(3));
    //m_registry.insert(new Serial(\));
    NewSerial();
}

SerialRegistry32::~SerialRegistry32()
{
    //dtor
}


Serial* SerialRegistry32::NewSerial() throw(Exception){
    if((m_registry.size()*m_serial_reserve_size) >= m_reg_reserve_size || (m_registry.size()*m_serial_reserve_size)+m_serial_reserve_size > m_reg_reserve_size){
        throw(Exception(Exception::SerialOverflow, "serial registry overflow", "the registry is full"));
    }

    //Serial* newserial = new Serial(0);
    unsigned int* index;
    std::cout << "Next empty index: " << createIndex(index)->GetIndex() << std::endl;
    return 0;
}

//Returns pointer to a temporary Serial. Fills index with the expected value. Before actually inserting this index into the registry, a CAS should be performed
Serial* SerialRegistry32::createIndex(unsigned int* index){
    if(m_registry.empty()){
        *index = 0;
        return new Serial(0);
    }

    unsigned int                chk_index = 0;
    Serial::_Serial_t*      check = 0;
    bool checkSet       = false;

    for(registry_type_iterator it = m_registry.begin(); it != m_registry.end(); it++){
        std::cout << (*it)->_Serial.index << "==" << chk_index;
        if((*it)->_Serial.index == chk_index){
            std::cout << " continue\n";
            chk_index = (*(it++))->_Serial.index;
            continue;
        }

        std::cout << " break\n";
        chk_index = (*it)->_Serial.index;
        checkSet = true;
        break;
    }

    if(checkSet){
        *index = chk_index;
    }else{
        *index = -1;
    }

    return new Serial(*index);
}

*/
///////////////////////////////////////////////////////////////////
///CLASS:             Serial
///////////////////////////////////////////////////////////////////
Serial::Serial(){
    key.serial  = 0;
    key.flags   = 0;
}
Serial::Serial(const unsigned char& flags){
    key.serial = 0;
    key.flags  = flags;
}

void Serial::SetSerial(const unsigned char& _serial){
    key.serial = _serial;
}

bool Serial::IsFlagged(const unsigned char& flag) const{
    return key.flags & flag;
}

void Serial::Flag(const unsigned char& _flags){
    key.flags = key.flags | _flags;
}

void Serial::Unflag(const unsigned char& _flags){
    key.flags = key.flags & ~_flags;
}

const unsigned char Serial::GetFlagsCopy() const{
    unsigned char copy = key.flags;
    return copy;
}

const unsigned char Serial::GetSerialCopy() const{
    unsigned char copy = key.serial;
    return copy;
}

const unsigned char Serial::GetKeyCopy() const{
    unsigned char copy = key.serial | key.flags;
    return copy;
}

bool Serial::operator==(const Serial& cmp) const{
    if(cmp.GetSerialCopy() == key.serial && cmp.GetFlagsCopy() == key.flags){
        return true;
    }

    return false;
}
