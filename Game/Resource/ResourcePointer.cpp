#include "ResourcePointer.h"
#include "../Resource.h"
ResourcePointer::ResourcePointer(std::string file)
{
    set(file);
}

ResourcePointer::~ResourcePointer()
{
    //dtor
}

void ResourcePointer::set(std::string file){
    std::vector<std::string> fileType;

    parse(file, ".", &fileType);

    if(fileType.size() == 2){
        if(fileType[1] == "png"){
            std::string realPath = Resource::Object()->ImageDir + file;
            if(ImageHandler::AddImage(realPath)){
                m_type = Image;
            }else{
                m_type = Invalid;
            }
        }else if(fileType[1] == "ttf"){
            std::string realPath = Resource::Object()->FontDir + file;
            if(FontHandler::AddFont(realPath)){
                m_type = Font;
            }else{
                m_type = Invalid;
            }
        }else{
            m_type = Invalid;
        }
    }else{
        m_type = Invalid;
    }
}

void ResourcePointer::parse(std::string str, std::string separator, std::vector<std::string>* results){
    int found;
    found = str.find_first_of(separator);
    while(found != std::string::npos){
        if(found > 0){
            results->push_back(str.substr(0,found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(separator);
    }
    if(str.length() > 0){
        results->push_back(str);
    }
}
