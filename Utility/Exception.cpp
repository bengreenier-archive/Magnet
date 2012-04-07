#include "Exception.h"
#include "../Pipeline.h"

using namespace util;

Exception::Exception( std::string name, std::string msg )
:   m_name(name),
    m_msg(msg)
{}

Exception::~Exception()
{
    //dtor
}

void Exception::log()
{
    Pipeline::SetScope(Pipeline::SCREEN);

    pipe << "'Exception " << m_name << " has occured!' " << m_msg << std::endl;
}
