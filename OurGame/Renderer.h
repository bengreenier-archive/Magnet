#ifndef RENDERER_H
#define RENDERER_H

#include "Renderer/RenderHandler.h"
#include "Renderer/RenderData.h"
#include "Renderer/Layer.cpp"

/*************************************
    Renderer is a static class allows
        an easy API with RenderHandler
**************************************/

class Renderer
{
    public:
        //Link the Renderer to a drawable with a predefined RenderObject
       // template<typename T>
       // static void Link(RenderObject<T> linkedObj);

        //Link the Renderer to a drawable with no RenderObject
        //  A new RenderObject is created with default Layer (GAME) and depth(0)
        //template <typename T>
        static void Link(sf::Drawable* linkedObj);

        static void RemapDepth(sf::Drawable* linkedObj, int depth);

        static sf::RenderWindow* Window();
        static void draw();

    protected:
    private:
};

#endif // RENDERER_H
