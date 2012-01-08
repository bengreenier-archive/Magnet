#include "FontHandler.h"
#include "../../Magnet.h"

FontHandler* FontHandler::FontHandlerPtr = NULL;

FontHandler::FontHandler()
{
    //ctor
    Console::AddCommand("FontHandler::PrintAvailableFonts()",&FontHandler::PrintAvailableFonts);
}

FontHandler::~FontHandler()
{
    //dtor
}

sf::Font& FontHandler::GetFont(std::string in)
{
    if (GetObject()->object_map.count(in) <= 0)
    {
        //make new
        //error
    }else{

        //return reference to Font
        return GetObject()->object_map[in];
    }



}

bool FontHandler::AddFont(std::string in)
{
    sf::Font Font;

    GetObject()->object_map[in] = Font;

    if (!GetObject()->object_map[in].LoadFromFile(in))
    {
        std::cout<<"Font could not be loaded from "<<in<<"\n";
        return false;
    }

    return true;

}

FontHandler* FontHandler::GetObject(){
    if(FontHandlerPtr == NULL){
        FontHandlerPtr = new FontHandler();
    }

    return FontHandlerPtr;
}


void FontHandler::PrintAvailableFonts()
{
    for ( GetObject()->Oit=GetObject()->object_map.begin() ; GetObject()->Oit != GetObject()->object_map.end(); GetObject()->Oit++ )
        std::cout<<GetObject()->Oit->first<<"\n";

}



sf::String* FontHandler::MakeStringWithFont(std::string in,std::string font,int size)
{
    return new sf::String(in,GetFont(font),size);
}
