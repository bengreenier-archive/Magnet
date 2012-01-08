#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <iostream>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

#include "../Exception.h"

class ImageHandler
{
    public:
        ImageHandler();
        ~ImageHandler();

        //////////////////////////////////////////////
        /// Load an image
        ///
        /// Throws a LoadFail exception if the file
        /// could not be loaded.
        //////////////////////////////////////////////
        static bool AddImage(std::string in) throw(Exception::ob);
        static sf::Image& GetImage(std::string in);
        static ImageHandler* GetObject();
        static void PrintAvailableImages();

    protected:
    private:
        std::map <std::string, sf::Image> object_map;
        std::map <std::string, sf::Image>::iterator Oit;
        static ImageHandler* ImageHandlerPtr;
};

#endif // IMAGEHANDLER_H
