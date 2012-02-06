#include "CfgParse.h"

CfgParse::CfgParse(const char* path)
{
    m_path = path;

    if(CfgGlobals::DEBUG && CfgGlobals::VERBOSE)
        std::cout << "[CfgParse]Created new parse element from path \"" << path << "\"\n";

    Load();
}

CfgParse::~CfgParse()
{
    //dtor
}

bool CfgParse::Load(const char* path){
    if(CfgGlobals::DEBUG && CfgGlobals::VERBOSE)
        std::cout << "[CfgParse][Load] Setting path to \"" << path << "\"\n";
    m_path = path;
    return Load();
}
bool CfgParse::Load(){
    if(CfgGlobals::DEBUG && CfgGlobals::VERBOSE)
        std::cout << "[CfgParse][Load] Loading from \"" << m_path << "\"\n";

    if(m_config_file.is_open()){
        m_config_file.close();
    }

    m_config_file.open(m_path);
}

Config& CfgParse::Parse(Config& data){
    if(!IsReady()) return data;

    std::string line;

    std::string current_category = CfgGlobals::GLOBAL_CATEGORY;
    int line_n = 1;
    while(getline(m_config_file, line)){
        if(line.find(CfgGlobals::COMMENT_STRING) != std::string::npos){
            line = line.substr(0, line.find(CfgGlobals::COMMENT_STRING));
        }

        //Look for the start of a category
        if(line.find(CfgGlobals::CATEGORY_TAG_OPEN) != std::string::npos){
            //Get start and end position of the category definition
            size_t start = line.find(CfgGlobals::CATEGORY_TAG_OPEN);
            size_t end = line.find(CfgGlobals::CATEGORY_TAG_CLOSE);

            if(end == std::string::npos){
                if(CfgGlobals::DEBUG)
                    std::cout << "[CfgParse][Load] Syntax error in file \"" << m_path << "\" one line " << line_n << ". Category tag not closed.\n";
                continue;
            }
            current_category = line.substr(start+1, end-1);
            TrimString(current_category);
            ToLower(current_category);
        }else if(line.find(CfgGlobals::ASSIGNMENT_OPERATOR) != std::string::npos){
            size_t split_pos = line.find(CfgGlobals::ASSIGNMENT_OPERATOR);
            std::string name = line.substr(0, split_pos);
            std::string value= line.substr(split_pos+1, line.length());

            TrimString(name);
            TrimString(value);

            //std::cout << "Category: \"" << current_category << "\"" << std::endl;
            data.AddKeyObject(new CfgObject(current_category, name, value));
        }

        line_n++;
    }

    return data;
}

void CfgParse::ToLower(std::string& str){
    for(int i=0; i < str.length(); i++){
        str[i] = std::tolower(str[i]);
    }
}

void CfgParse::TrimString(std::string& to_trim, bool left, bool right){
    if(left){
        if(to_trim.find(" ") == 0){
            size_t pos = to_trim.find_first_not_of(" ");
            to_trim = to_trim.substr(pos);
        }
    }

    if(right){
        if(to_trim.find(" ", to_trim.length()-1) != std::string::npos){
            to_trim = to_trim.substr(0, to_trim.length()-1);

            TrimString(to_trim, false, true);
        }
    }
}

bool CfgParse::StringIsInt(std::string str){
    for(int i = 0; i < str.length(); i++){
        int ascii_code = (int)str[i];
        if((ascii_code < 48 || ascii_code > 57) && ascii_code != 45){ // 48 = 0, 57 = 9, 45 = -
            return false;
        }
    }

    return true;
}

bool CfgParse::IsReady(){
   if(m_config_file.is_open() && m_config_file.good()){
        if(CfgGlobals::DEBUG && CfgGlobals::VERBOSE)
            std::cout << "[CfgParse][IsReady] Parser is ready\n";

        return true;
    }

    if(CfgGlobals::DEBUG && CfgGlobals::VERBOSE)
            std::cout << "[CfgParse][IsReady] Parser is not ready\n";

    return false;
}
