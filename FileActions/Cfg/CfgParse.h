#ifndef CFGPARSE_H
#define CFGPARSE_H


#include <fstream>
#include <iostream>

#include "CfgGlobals.h"
#include "CfgObject.h"
#include "Config.h"

class CfgParse
{
    public:
        CfgParse(const char* path);
        virtual ~CfgParse();

        //////////////////////////////////////
        /// Loads the config file
        //////////////////////////////////////
        bool Load(const char* path);
        bool Load();

        //////////////////////////////////////
        /// This converts the loaded file
        /// into a CfgObject tree
        //////////////////////////////////////
        Config& Parse(Config& data);

        ///Returns true when ready for a parse
        bool IsReady();

        void TrimString(std::string& to_trim, bool left=true, bool right=true);
        void ToLower(std::string& str);
        bool StringIsInt(std::string str);
    protected:
    private:
        const char* m_path;
        std::ifstream m_config_file;
};

#endif // CFGPARSE_H
