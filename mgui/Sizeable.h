#ifndef SIZEABLE_H_INCLUDED
#define SIZEABLE_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace mgui{
    struct Sizeable{
        Sizeable(sf::Vector2f size) : m_size(size){}
        Sizeable() : m_size(sf::Vector2f(0, 0)){}

        virtual void SetSize(sf::Vector2f newSize){ m_size = newSize; }
        virtual sf::Vector2f GetSize(){ return m_size; }

        sf::Vector2f m_size;
    };
}

#endif // SIZEABLE_H_INCLUDED
