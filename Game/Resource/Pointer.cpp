#include "Pointer.h"
#include "../Resource.h"

Resource::Pointer::Pointer(std::string file)
{
    set(file);
}

Resource::Pointer::~Pointer()
{
    //dtor
}

void Resource::Pointer::set(std::string file){
    std::vector<std::string> fileType;

    parse(file, ".", &fileType);

    std::cout << "Setting type... ";
    if(fileType.size() == 2){
        std::cout << fileType[1] << std::endl;
        std::cout << "File path is properly formatted\n";
        if(fileType[1] == "png"){
            std::cout << "File is an image\n";
            //try{
                ImageHandler::AddImage(file);
                m_type = Image;
            //}

            /*catch(Resource::Exception e){
                std::cout << "Resource exception occured!\n";
                //e.error();
                m_type = Invalid;
            }*/
        }else{
            m_type = Invalid;
        }
    }else{
        m_type = Invalid;
    }
}

void Resource::Pointer::parse(std::string str, std::string separator, std::vector<std::string>* results){
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
