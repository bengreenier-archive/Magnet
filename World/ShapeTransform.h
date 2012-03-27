#ifndef SHAPETRANSFORM_H
#define SHAPETRANSFORM_H

#include <SFML/Graphics.hpp>

class ShapeTransform
{
    public:
        /** Default constructor */
        ShapeTransform(sf::Vector2f position);
		ShapeTransform(sf::Vector2f position,sf::Vector2f origin);
		ShapeTransform(sf::Vector2f position,sf::Vector2f origin,sf::Vector2f scale);
		ShapeTransform(sf::Transformable* shape);
        /** Default destructor */
        ~ShapeTransform();

        sf::Transformable* Instance;
    protected:
    private:
};

#endif // SHAPETRANSFORM_H
