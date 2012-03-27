#include "ShapeTransform.h"
#include <iostream>

ShapeTransform::ShapeTransform(sf::Vector2f position)
{
    std::cout<<"[ShapeTransform][Constructor] Inactive Constructor.\n";
}
ShapeTransform::ShapeTransform(sf::Vector2f position,sf::Vector2f origin)
{
    std::cout<<"[ShapeTransform][Constructor] Inactive Constructor.\n";
}
ShapeTransform::ShapeTransform(sf::Vector2f position,sf::Vector2f origin,sf::Vector2f scale)
{
    std::cout<<"[ShapeTransform][Constructor] Inactive Constructor.\n";
}
ShapeTransform::ShapeTransform(sf::Transformable* shape)
{
    Instance = shape;
}
ShapeTransform::~ShapeTransform()
{
    //dtor
}
