#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include <SFML/Graphics.hpp>

namespace mgui{
    struct Positionable{
        Positionable(sf::Vector2f startPos) : m_pos(startPos) {}
        Positionable() : m_pos(sf::Vector2f(0, 0)) {}
        virtual ~Positionable(){};
        virtual void SetPosition(sf::Vector2f newPosition){ m_pos = newPosition; }
        virtual sf::Vector2f GetPosition(sf::Vector2f newPosition){  return m_pos; }
        sf::Vector2f m_pos;
    };
}

#endif // POSITIONABLE_H
