#ifndef LINKABLESPRITE_H
#define LINKABLESPRITE_H

#include <SFML/Graphics.hpp>
#include "../../Renderer.h"

//class Renderer;

class LinkableSprite : public sf::Sprite
{
    public:
        LinkableSprite();
        LinkableSprite(int depth, Renderer::layer_t);

        //sf::Sprite*         sprite;
        int                 depth;
        Renderer::layer_t   layer;
    protected:
    private:

};

#endif // LINKABLESPRITE_H
