#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <SFML/Graphics.hpp>
#include <string>

class ItemBase
{
    public:
        ItemBase();
        ~ItemBase();
        std::string ElementName;//the name of a Base. IE ("Green Shirt") or ("Incinerator Sniper")
        std::string ElementType;//the type of Base. IE ("Weapon") or ("Apparel")
    protected:
        sf::Sprite Sprite;//a drawable sprite (what IT looks like)
        sf::String String;//a drawable string (what ITS name is)
    private:

};

#endif // ITEMBASE_H
