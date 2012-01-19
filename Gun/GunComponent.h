#ifndef GUNCOMPONENT_H
#define GUNCOMPONENT_H
#include <SFML/Graphics.hpp>
#include "../Magnet.h"
#include <string>
#include "GunEnum.h"


class GunComponent //! Defines a piece of a gun, so that it can be used to create a whole gun
{
    public:
        // Default Constructor, take the parts needed to make a component
        GunComponent();//!< Default Constructor


        ~GunComponent(); //!< Default Destructor


        sf::Sprite* GetSpritePtr(); //!< Get the Sprite for this component
        std::string GetImagePath();                     //!< Return the components image path
        int GetWidth(); //!< Get the width for this components sprite
        int GetHeight(); //!< Get the height for this components sprite
        void SetImagePath(std::string path); //!< Set the current image to an image, based on a sprite (Depreciated, should use Resource)

        std::string GetType();                          //!< Return the components gun type
        GunEnum::Type type;     //!< The type of the component

    protected:
    private:
        std::string         m_imagepath;
        sf::Sprite          m_sprite;

        int         m_width;
        int         m_height;

        std::string TypeFinder();

};

#endif // GUNCOMPONENT_H
