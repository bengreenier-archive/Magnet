#include "ConfigGlobals.h"

Config::Config()
{
    //ctor
}

Config::~Config()
{
    //dtor
}

file_node* Config::GetFile(){
    return m_file;
}

void Config::SetFile(file_node* file){
    m_file = file;
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
    return KeyExists(CONFIG_GLOBAL_CATEGORY, key);
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
    if(null_string == ""){
        null_string = CONFIG_GLOBAL_CATEGORY;
    }
}

ConfigVar* Config::GetVar(std::string key){
    return GetVar("", key);
}

ConfigVar* Config::GetVar(std::string category_name, std::string key){
    makeNullGlobal(category_name);

    for(int i = 0; i < m_cfg_vect.size(); i++){
        if(m_cfg_vect[i]->GetCategory() == category_name){
            if(m_cfg_vect[i]->GetName() == key){
                return m_cfg_vect[i];
            }
        }
    }

    return new ConfigVar("", "", "");
}

void Config::AddVar(ConfigVar* cfg_ob){
    bool should_push    = true;
    bool rewrite        = false;

    int override_keys;
    bool debug;
    bool verbose;

    if(ConfigGlobals::ConfigExists("config")){
        override_keys   = ConfigGlobals::GetConfig("config")->GetVar("parser", "override_keys")->GetInt();
        debug           = ConfigGlobals::GetConfig("config")->GetVar("parser", "debug")->GetBool();
        verbose         = ConfigGlobals::GetConfig("config")->GetVar("parser", "verbose")->GetBool();
    }else{
       override_keys = 2;
       debug = true;
       verbose = true;

    }

    if(KeyExists(cfg_ob->GetCategory(), cfg_ob->GetName())){
        switch(override_keys){
            case 0: //Override
                should_push = true;
                rewrite = true;

                if(debug && verbose)
                    std::cout << "[Config][AddKeyObject] Key '" << cfg_ob->GetCategory() << ", " << cfg_ob->GetName() << "' already exists. The key will be rewritten.\n";
                break;
            case 1: //Ignore
                should_push = false;
                rewrite = false;

                if(debug && verbose)
                    std::cout << "[Config][AddKeyObject] Key '" << cfg_ob->GetCategory() << ", " << cfg_ob->GetName() << "' already exists. The key will be ignored.\n";

                break;
            case 2: //Add
                should_push = true;
                rewrite = false;

                if(debug && verbose)
                    std::cout << "[Config][AddKeyObject] Key '" << cfg_ob->GetCategory() << ", " << cfg_ob->GetName() << "' already exists. A duplicate key will be added.\n";
                break;
        }


    }

    if(should_push && !rewrite){
        m_cfg_vect.push_back(cfg_ob);
    }else if(should_push && rewrite){
        RemoveVar(cfg_ob->GetCategory(), cfg_ob->GetName());
        m_cfg_vect.push_back(cfg_ob);
    }
}

void Config::RemoveVar(std::string category_name, std::string key){
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
    if(!((ConfigGlobals::ConfigExists("config")) ? ConfigGlobals::GetConfig("config")->GetVar("parser", "debug")->GetBool() : true)) return;

    std::cout << "[Config][Output] There are " << m_cfg_vect.size() << " config entries\n";
    std::cout << "Category\t\tName\t\tValue\n";
    for(int i = 0; i < m_cfg_vect.size(); i++){
        std::cout << m_cfg_vect[i]->GetCategory() << "\t\t" << m_cfg_vect[i]->GetName() <<  "\t\t" << m_cfg_vect[i]->GetString () << std::endl;
    }
}
