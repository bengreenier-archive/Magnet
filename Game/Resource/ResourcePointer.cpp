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

sf::Image&  ResourcePointer::getImage() throw(Exception){
    std::cout << "Get image\n";
    if(!isValid()){
        std::cout << "IMage is inbalid, throw...\n";
        Exception e(Exception::NullPointer, "Invalid image", m_file + " is not a valid image");
        throw e;
    }

    return ImageHandler::GetImage(m_fullPath);
}

sf::Font&   ResourcePointer::getFont(){
    return FontHandler::GetFont(m_fullPath);
}

void ResourcePointer::set(std::string fnode){
/*    std::cout << "Creating resource pointer from file: " << fnode->path << std::endl;
    m_file = file;


    m_type = Invalid;*/
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
