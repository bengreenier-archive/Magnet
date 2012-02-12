#ifndef SHAPETRANSFORM_H
#define SHAPETRANSFORM_H


class ShapeTransform
{
    public:
        /** Default constructor */
        ShapeTransform(sf::Vector2f position);
		ShapeTransform(sf::Vector2f position,sf::Vector2f origin);
		ShapeTransform(sf::Vector2f position,sf::Vector2f scale);
		ShapeTransform(sf::Vector2f position,sf::Vector2f origin,sf::Vector2f scale);
        /** Default destructor */
        ~ShapeTransform();

        sf::Transformable* Shape;
    protected:
    private:
};

#endif // SHAPETRANSFORM_H
