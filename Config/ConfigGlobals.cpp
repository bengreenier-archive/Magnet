#include "ConfigGlobals.h"

ConfigGlobals* ConfigGlobals::m_object =   0;

ConfigGlobals* ConfigGlobals::Object(){
    if(m_object == 0)
        m_object = new ConfigGlobals();

    return m_object;
}

ConfigGlobals::ConfigGlobals(){
    m_config_tree = FileAction::CreateDirectoryTree(RESOURCE_PATH);

    Config config_defaults;
    config_defaults.AddVar(new ConfigVar(CONFIG_GLOBAL_CATEGORY, "debug", "true"));
    config_defaults.AddVar(new ConfigVar(CONFIG_GLOBAL_CATEGORY, "verbose", "true"));
    config_defaults.AddVar(new ConfigVar("parser", "override_keys", "2", CVAR_F_CONSTANT)); //0 = existing keys are replaces, 1 = existing keys are not added, 2 = existing keys are added (two keys of the same name may exist)
    config_defaults.AddVar(new ConfigVar("parser", "comment_string", "//", CVAR_F_CONSTANT));
    config_defaults.AddVar(new ConfigVar("parser", "debug", "true", CVAR_F_CONSTANT));
    config_defaults.AddVar(new ConfigVar("parser", "category_tag_open", "[", CVAR_F_CONSTANT));
    config_defaults.AddVar(new ConfigVar("parser", "category_tag_close", "]", CVAR_F_CONSTANT));
    config_defaults.AddVar(new ConfigVar("parser", "assignment_operator", "=", CVAR_F_CONSTANT));
    config_defaults.AddVar(new ConfigVar("parser", "bool_id", "true", CVAR_F_CONSTANT));
    RegisterDefaults("config", config_defaults);
}

ConfigGlobals::~ConfigGlobals(){
    delete m_object;
}

void ConfigGlobals::RegisterDefaults(std::string name, Config& new_default){
    if(ConfigExists(name)){
        if(ConfigExists("config")){
            if(GetConfig("config")->GetVar("debug")->GetBool()){
                std::cout << "[ConfigGlobals][RegisterDefaults] Could not register class '" << name << "'. It already exists.\n";
            }
        }
        return;
    }

    //Created a temporary config to edit and do error checking (will insert a copy into the registry later)
    Config tmpcfg(new_default); //Make a copy of the recieved config

    if((tmpcfg.m_file = GetConfigFileFromTree(name)) != 0){
        if(tmpcfg.GetFile()->loaded){
            /*if(!GetCachedValue(reg_config.config)){  //Override defaults
                reg_config.flags |= CONFIG_F_LOAD;  //This lets main logic know that it doesn't need to load a file on load
            }*/
        }
    }

    Object()->m_registry.insert(new Config(tmpcfg));
}


file_node* ConfigGlobals::GetConfigFileFromTree(std::string name){
    for(int i = 0; i < Object()->m_config_tree.size(); i++){
        if(!Object()->m_config_tree[i]->files.empty()){
            for(int j = 0; j < Object()->m_config_tree[i]->files.size(); i++){
                if(Object()->m_config_tree[i]->files[j]->file.find(name) != std::string::npos){
                    return Object()->m_config_tree[i]->files[j];
                }
            }
        }
    }

    return 0;
}

 //this function needs to be properly defined
const Config* ConfigGlobals::GetConfig(std::string name){
    return new Config();
}


