#include "ConfigGlobals.h"
#include <iostream>

ConfigVar::ConfigVar(std::string cat, std::string name, const void* value, uint8_t flags)
{
    m_category  =   cat;
    m_name  = name;
    m_value.StrongWrite(&value);
}

ConfigVar::~ConfigVar()
{
    //delete m_kvpair.second;
}

const int ConfigVar::GetInt() const{
    //void* stored_val =  m_value.StrongRead();
    return 0;//;*static_cast<int*>(stored_val);
}
const float ConfigVar::GetFloat()const{
    //void* stored_val = m_value.StrongRead();
    return 0.f;//*static_cast<float*>(stored_val);
}
const bool ConfigVar::GetBool()const{
    /*void* stored_val = m_value.StrongRead();
    std::string val = *static_cast<std::string*>(stored_val);

    if(ConfigGlobals::ConfigExists("config")){
        if(ConfigGlobals::GetConfig("config")->GetVar("parser", "bool_id")->GetString() == val){
            return true;
        }
    }else{
        return (val == "true") ? true : false;
    }
    */
    return false;
}
const std::string ConfigVar::GetString()const{
    //void* stored_val = m_value.StrongRead();
    return "";//*static_cast<std::string*>(stored_val);
}
