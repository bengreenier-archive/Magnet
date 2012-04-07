#include "Hook.h"

void Hook::begin() throw()
{
    try{
        //std::cout << "Executing '" << name() << "'\n";
        m_callback.execute();
    }catch(util::Exception& error){
        error.log();
    }
}

const std::string& Hook::name()
{
    return m_name;
}
