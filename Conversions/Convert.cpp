#include "Convert.h"
#include <sstream>

Convert* Convert::ConvertPtr=NULL;

Convert::Convert()
{
    //ctor
}

Convert* Convert::Get()
{

     if(ConvertPtr==NULL)
        ConvertPtr=new Convert();

    return ConvertPtr;
}

std::string ToString(int i)
{
    std::stringstream ss;
    ss<<i;
    return ss.str();
}
