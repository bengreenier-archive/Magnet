#include "Config.h"

Config::Config()
{
    //ctor
}

Config::~Config()
{
    //dtor
}

bool Config::CategoryExists(std::string category_name){
    makeNullGlobal(category_name);
    for(int i = 0; i < m_cfg_vect.size(); i++){
        if(m_cfg_vect[i]->GetCategory() == category_name){
            return true;
        }
    }

    return false;
}

Config::config_vect_type Config::GetCategory(std::string category_name){
    makeNullGlobal(category_name);
    config_vect_type category;
    for(int i = 0; i < m_cfg_vect.size(); i++){
        if(m_cfg_vect[i]->GetCategory() == category_name){
            category.push_back(m_cfg_vect[i]);
        }
    }

    return category;
}

bool Config::KeyExists(std::string key){
    return KeyExists(CfgGlobals::NULL_STRING, key);
}
bool Config::KeyExists(std::string category_name, std::string key){
    for(int i = 0; i < m_cfg_vect.size(); i++){
        if(m_cfg_vect[i]->GetCategory() == category_name){
            if(m_cfg_vect[i]->GetName() == key){
                return true;
            }
        }
    }

    return false;
}

void Config::makeNullGlobal(std::string& null_string){
    if(null_string == CfgGlobals::NULL_STRING){
        null_string = CfgGlobals::GLOBAL_CATEGORY;
    }
}

CfgObject* Config::GetKeyObject(std::string key){
    return GetKeyObject(CfgGlobals::NULL_STRING, key);
}

CfgObject* Config::GetKeyObject(std::string category_name, std::string key){
    makeNullGlobal(category_name);

    for(int i = 0; i < m_cfg_vect.size(); i++){
        if(m_cfg_vect[i]->GetCategory() == category_name){
            if(m_cfg_vect[i]->GetName() == key){
                return m_cfg_vect[i];
            }
        }
    }

    return NULL;
}

const std::string& Config::GetKeyValue(std::string key){
    return GetKeyValue(CfgGlobals::NULL_STRING, key);
}
const std::string& Config::GetKeyValue(std::string category_name, std::string key){
    makeNullGlobal(category_name);
    CfgObject* cfgob = GetKeyObject(category_name, key);

    if(cfgob == NULL){
        return "UNKNOWN";
    }

    return cfgob->GetString();
}

void Config::AddKeyObject(CfgObject* cfg_ob){
    bool should_push = true;

    if(KeyExists(cfg_ob->GetCategory(), cfg_ob->GetName())){
        should_push = false;
        if(CfgGlobals::DEBUG)
            std::cout << "[Config][AddKeyObject] Key '" << cfg_ob->GetCategory() << ", " << cfg_ob->GetName() << "'already exists!\n";
    }

    if(should_push)
        m_cfg_vect.push_back(cfg_ob);


}

void Config::RemoveKeyObject(std::string category_name, std::string key){
    makeNullGlobal(category_name);
    if(KeyExists(category_name, key)){
        for(config_vect_it_type it = m_cfg_vect.begin(); it != m_cfg_vect.end(); it++){
            if((*it)->GetCategory() == category_name && (*it)->GetName() == key){
                it = m_cfg_vect.erase(it);
            }
        }
    }
}


void Config::Output(){
    if(!CfgGlobals::DEBUG) return;

    std::cout << "[Config][Output] There are " << m_cfg_vect.size() << " config entries\n";
    std::cout << "Category\t\tName\t\tValue\n";
    for(int i = 0; i < m_cfg_vect.size(); i++){
        std::cout << m_cfg_vect[i]->GetCategory() << "\t\t" << m_cfg_vect[i]->GetName() <<  "\t\t" << m_cfg_vect[i]->GetString () << std::endl;
    }
}
