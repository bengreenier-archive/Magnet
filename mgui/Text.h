#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>

class Text : virtual public sf::String
{
    public:
        Text(const char* content);
        Text();
        virtual ~Text();
    protected:
    private:
};

#endif // TEXT_H
