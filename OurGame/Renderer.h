#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>

#include "Renderer/RenderHandler.h"
#include "Renderer/RenderObject.h"
#include "Renderer/Layer.cpp"

/*************************************
    Renderer is a static class allows
        objects to be drawn to screen
**************************************/

class Renderer
{
    public:
        //Link the Renderer to a drawable with a predefined RenderObject
       // template<typename T>
       // static void Link(RenderObject<T> linkedObj);

        //Link the Renderer to a drawable with no RenderObject
        //  A new RenderObject is created with default Layer (GAME) and depth(0)
        static void Link(sf::Drawable* linkedObj, const int& layer, int depth);

        static sf::RenderWindow* Window();
        static void draw();

    protected:
    private:
};

#endif // RENDERER_H
