#ifndef FONTHANDLER_H
#define FONTHANDLER_H


#include <iostream>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>


class FontHandler
{
    public:
        FontHandler();
        ~FontHandler();

        static bool AddFont(std::string in);
        static sf::Font& GetFont(std::string in);
        static FontHandler* GetObject();
        static void PrintAvailableFonts();

        static sf::String* MakeStringWithFont(std::string in,std::string font,int size);

    protected:
    private:
        std::map <std::string, sf::Font> object_map;
        std::map <std::string, sf::Font>::iterator Oit;
        static FontHandler* FontHandlerPtr;
};

#endif // FONTHANDLER_H
