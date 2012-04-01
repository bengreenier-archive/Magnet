#include "Hook.h"

void Hook::begin() throw()
{
    try{
        m_callback.execute();
    }catch(util::Exception& error){
        error.log();
    }
}

const char* Hook::name()
{
    return m_name;
}
