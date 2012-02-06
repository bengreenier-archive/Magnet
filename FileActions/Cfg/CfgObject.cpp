#include "CfgObject.h"

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
float GetFloat();
bool GetBool();
const std::string& CfgObject::GetString(){ return m_kvpair.second; }
