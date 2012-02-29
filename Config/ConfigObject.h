#ifndef CFGOBJECT_H
#define CFGOBJECT_H

//#include <pair>
#include <string>
#include <stdlib.h>
#include "ConfigGlobals.h"

class CfgObject
{
    public:
        CfgObject(std::string cat, std::string name, std::string value);
        virtual ~CfgObject();

        const int&          GetInt();
        const float&        GetFloat();
        const bool&         GetBool();
        const std::string&  GetString();

        void            SetValue(void* value);
        void            SetName(std::string str);
        void            SetCategory(std::string str);

        std::string GetCategory(){ return m_category; }
        std::string GetName(){ return m_kvpair.first; }
    protected:
    private:
        typedef std::pair<std::string, std::string>    key_value_pair_t;

        std::string         m_category;
        std::string         m_name;
        key_value_pair_t    m_kvpair;
};

#endif // CFGOBJECT_H
