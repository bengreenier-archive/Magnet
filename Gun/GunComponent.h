#ifndef GUNCOMPONENT_H
#define GUNCOMPONENT_H
#include <SFML/Graphics.hpp>
#include "../Magnet.h"
#include <string>
#include "GunEnum.h"


class GunComponent
{
    public:
        // Default Constructor, take the parts needed to make a component
        GunComponent();


        ~GunComponent();          // Default Constructor, take the parts needed to make a component


        sf::Sprite* GetSpritePtr();
        std::string GetImagePath();                     // Return the components image path
        int GetWidth();
        int GetHeight();
        void SetImagePath(std::string path);

        std::string GetType();                          // Return the components gun type
        GunEnum::Type type;

    protected:
    private:
        std::string         m_imagepath;
        sf::Sprite          m_sprite;

        int         m_width;
        int         m_height;

        std::string TypeFinder();

};

#endif // GUNCOMPONENT_H
