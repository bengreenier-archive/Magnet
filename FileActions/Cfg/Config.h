#ifndef CONFIG_H
#define CONFIG_H

#include <vector>

#include "CfgGlobals.h"
#include "CfgObject.h"
#include <iostream>

class Config
{
    public:
        typedef std::vector<CfgObject*>             config_vect_type;
        typedef std::vector<CfgObject*>::iterator   config_vect_it_type;

        Config();
        virtual ~Config();

        bool CategoryExists(std::string category_name);
        config_vect_type GetCategory(std::string category_name);

        bool            KeyExists(std::string category_name, std::string key);
        bool            KeyExists(std::string key);
        CfgObject*   GetKeyObject(std::string category_name, std::string key);
        CfgObject*   GetKeyObject(std::string key);
        const std::string&           GetKeyValue(std::string category_name, std::string key);
        const std::string&           GetKeyValue(std::string key);

        void AddKeyObject(CfgObject* cfg_ob);
        void RemoveKeyObject(std::string category_name, std::string key);

        //////////// DEGUB ///////////////////
        //Output all config data
        void Output();

    protected:
    private:
        config_vect_type m_cfg_vect;

        void makeNullGlobal(std::string& null_string);
};

#endif // CONFIG_H
