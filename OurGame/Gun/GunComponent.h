#ifndef GUNCOMPONENT_H
#define GUNCOMPONENT_H
#include <SFML/Graphics.hpp>
#include <string>
class GunComponent : sf::Sprite
{
    public:
        GunComponent(int Damage,std::string Name,std::string ImagePath);          // Default Constructor, take the parts needed to make a component


        int         GetDamage();                                                        // Return the components damge value
        std::string GetName();                                                          // Return the components name
        sf::Sprite  GetSprite(std::string Position,int x,int y);                        // Return a drawable sprite made from Image
        std::string GetImagePath();                                                     // Return the components image path


    protected:
    private:

        float       ScaleFactor;                        // the amount to scale the sprite by
        int         Length;                             // Store the components length here
        int         Width;                              // Store the components width here
        int         Damage;                             // Store The damage value for the component here
        std::string Name;                               // Store The name value for the component here
        std::string ImagePath;                          // Store ImagePath here
        sf::Sprite  Sprite;                             // Store Sprite here
        sf::Image   Image;                              // Store image here
};

#endif // GUNCOMPONENT_H
