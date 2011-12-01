#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#include <SFML/Graphics.hpp>
#include "Renderer/RenderHandler.h"

class RenderData {
    public:
    RenderHandler::Layer    layer;
    int                     depth;
    sf::Drawable*           object;

    RenderData(){
        layer = RenderHandler::Layer;
        depth = 0;
    }
}

#endif //RenderData
