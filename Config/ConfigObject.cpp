#include "ConfigObject.h"
#include <iostream>
CfgObject::CfgObject(std::string cat, std::string name, std::string value)
{
    m_category  =   cat;
    m_kvpair.first  = name;
    m_kvpair.second = value;
}

CfgObject::~CfgObject()
{
    //delete m_kvpair.second;
}

const int& CfgObject::GetInt(){
    return atoi(m_kvpair.second.c_str());
}
const float& CfgObject::GetFloat(){
    return atof(m_kvpair.second.c_str());
}
const bool& CfgObject::GetBool(){
    if(m_kvpair.second == CfgGlobals::BOOL_ID){
        return true;
    }

    return false;
}
const std::string& CfgObject::GetString(){ return m_kvpair.second; }
