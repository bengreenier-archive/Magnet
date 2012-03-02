#ifndef CFGGLOBALS_H
#define CFGGLOBALS_H


#include <string>
#include "../FileActions/FileAction.h"
#include "../Game/ResourceDirectories.h"

#include "../Memory/ConcurrentQueue.h"

#include "ConfigVar.h"

#define CONFIG_GLOBAL_CATEGORY  "__CATGBL__"

enum CONFIG_FLAG{
    CONFIG_F_FILE       =   1,  //Flag is set when a the config has an associated file
    CONFIG_F_LOAD       =   2,  //Flag is set when the config has been loaded successfully
};

using namespace FileAction;


//////////////////////////////////////////////////////////////
//  A singleton class that handles  all configuration files
class Config;
class ConfigGlobals {

    struct registered_config_t{
        registered_config_t(){
            config = 0;
            file = 0;
            flags = 0;
        }
        Config*                      config; //A pointer to the configuration
        FileAction::file_node*       file;   //A pointer to the configuration file in the file tree
        uint8_t                     flags;
    };

    SerialRegistry   m_registry;

    static ConfigGlobals*                  m_object;
    directory_tree_t                       m_config_tree;

    ConfigGlobals();
    ~ConfigGlobals();



    public:
        static ConfigGlobals* Object();
        ///////////////////////////////////////////////////
        ///     RegisterDefaultClass
        //      Add a default configuration set. A .mcf will
        //      generated if it does not already exit.
        //      if the file does exist, file values will
        //      be used instead of defaults.
        static void RegisterDefaults(std::string name, Config& new_default);


        ///////////////////////////////////////////////////
        ///     GetConfig
        //      Gets a pointer to stored configuration data
        static Config* GetConfig(std::string name);
        static bool ConfigExists(std::string name);

        ///Attempt to find a config file in the search tree by
        // its name
        static bool ConfigFileExists(std::string name);

        static file_node* GetConfigFile(std::string name);



};

class ConfigVar;
class Config
{
    public:
        typedef std::vector<ConfigVar*>             config_vect_type;
        typedef std::vector<ConfigVar*>::iterator   config_vect_it_type;

        Config();
        virtual ~Config();


        config_vect_type GetCategory(std::string category_name);

        bool            CategoryExists(std::string category_name);
        bool            KeyExists(std::string category_name, std::string key);
        bool            KeyExists(std::string key);

        ConfigVar*                   GetVar(std::string category_name, std::string key);
        ConfigVar*                   GetVar(std::string key);
        //const std::string&           GetKeyValue(std::string category_name, std::string key);
        //const std::string&           GetKeyValue(std::string key);

        void AddVar(ConfigVar* cvar);
        void RemoveVar(std::string category_name, std::string key);

        //////////// DEGUB ///////////////////
        //Output all config data
        void Output();

        file_node* GetFile();
        void SetFile(file_node* file);
    private:
        sf::Mutex*  m_mutex;

        config_vect_type m_cfg_vect;
        file_node*       m_file;

        void makeNullGlobal(std::string& null_string);
};

//ConfigVar Flags
enum CVAR_FLAG{
    CVAR_F_CONSTANT =   1//Makes a config var unwriteable
};

class ConfigVar
{
    public:
        ConfigVar(std::string cat, std::string name, std::string value, uint8_t flags=0);
        virtual ~ConfigVar();

        const int&          GetInt();
        const float&        GetFloat();
        const bool&         GetBool();
        const std::string&  GetString();

        void            SetValue(uint8_t* value);
        void            SetName(std::string str);
        void            SetCategory(std::string str);

        std::string GetCategory();
        std::string GetName();
    protected:
    private:
        typedef std::pair<std::string, std::string>    kv_pair_type;

        Config*                     m_config;
        Serial                      m_serial;
        SharedVar<uint8_t*>         m_value;
};


#endif // CFGGLOBALS_H
