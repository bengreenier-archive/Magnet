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
    typedef std::set<Config*>   registry_type;
    registry_type                          m_registry;

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
        static const Config* GetConfig(std::string name); //Needs to be properly defined
        static bool ConfigExists(std::string name) { return false; }; //Needs to be properly defined

        ///Attempt to find a config file in the search tree by
        // its name
        static file_node* GetConfigFileFromTree(std::string name);

        static file_node* GetConfigFile(std::string name);



};

class ConfigVar;
class Config
{
    public:
        typedef std::vector<const ConfigVar*>             config_vect_type;
        typedef std::vector<const  ConfigVar*>::iterator   config_vect_it_type;

        Config();
        virtual ~Config();


        config_vect_type GetCategory(std::string category_name) const;

        bool            CategoryExists(std::string category_name) const;
        bool            KeyExists(std::string category_name, std::string key) const;
        bool            KeyExists(std::string key) const;

        const ConfigVar*                   GetVar(std::string category_name, std::string key) const;
        const ConfigVar*                   GetVar(std::string key) const;
        //const std::string&           GetKeyValue(std::string category_name, std::string key);
        //const std::string&           GetKeyValue(std::string key);

        void AddVar(ConfigVar* cvar);
        void RemoveVar(std::string category_name, std::string key);

        //////////// DEGUB ///////////////////
        //Output all config data
        void Output();

        const file_node* GetFile() const;
        void SetFile(const file_node* file);
    private:
        friend class ConfigGlobals;

        config_vect_type m_cfg_vect;
        const file_node*       m_file;

        void makeNullGlobal(std::string& null_string) const;
};

//ConfigVar Flags
enum CVAR_FLAG{
    CVAR_F_CONSTANT =   1,//Makes a config var unwriteable
    CVAR_F_ARCHIVE  =   2 //Stores the config var in the cache
};

class ConfigVar
{
    public:
        ConfigVar(std::string cat, std::string name, const char* value, uint8_t flags=0);
        virtual ~ConfigVar();

        const int          GetInt() const;
        const float        GetFloat() const;
        const bool         GetBool() const;
        const std::string  GetString() const;

        void            SetValue(void* value);
        void            SetName(std::string str);
        void            SetCategory(std::string str);

        std::string GetCategory() const { return m_category; };
        std::string GetName() const { return m_name; };
    protected:
    private:
        typedef std::pair<std::string, std::string>    kv_pair_type;

        Config*                     m_config;
        std::string                 m_category;
        std::string                 m_name;
        SharedVar<std::string>            m_value;
};


#endif // CFGGLOBALS_H
