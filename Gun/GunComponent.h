#ifndef GUNCOMPONENT_H
#define GUNCOMPONENT_H
#include <SFML/Graphics.hpp>
#include "../Handler/Renderer/LinkableSprite.h"
#include <string>
class GunComponent : public LinkableSprite
{
    public:
        GunComponent(int Damage,std::string Name,std::string ImagePath);          // Default Constructor, take the parts needed to make a component


        //sf::Sprite* GetSprite();
        int         GetDamage();                        // Return the components damge value
        std::string GetName();                          // Return the components name
        std::string GetImagePath();                     // Return the components image path
        int         Length;                             // Store the components length here
        int         Width;                              // Store the components width here

        std::string GetType();                          // Return the components gun type

    protected:
    private:

        int         Damage;                             // Store The damage value for the component here
        std::string Name;                               // Store The name value for the component here
        std::string ImagePath;                          // Store ImagePath here
        std::string Type;                               //Store the guntype here
        //sf::Sprite  Sprite;                             // Store Sprite here

        std::string TypeFinder();

};

#endif // GUNCOMPONENT_H
