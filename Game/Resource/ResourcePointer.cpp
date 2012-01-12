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

sf::Image&  ResourcePointer::getImage(){
    return ImageHandler::GetImage(m_fullPath);
}

void ResourcePointer::set(std::string file){
    m_file = file;

    std::vector<std::string> fileType;

    parse(file, ".", &fileType);

    if(fileType.size() == 2){
        if(fileType[1] == "png"){
            m_fullPath = Resource::Object()->ImageDir + file;
            if(ImageHandler::AddImage(m_fullPath)){
                m_type = Image;
            }else{
                m_type = Invalid;
            }
        }else if(fileType[1] == "ttf"){
            m_fullPath = Resource::Object()->FontDir + file;
            if(FontHandler::AddFont(m_fullPath)){
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
