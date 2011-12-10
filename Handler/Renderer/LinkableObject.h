#ifndef LINKABLEOBJECT_H
#define LINKABLEOBJECT_H

#include <SFML/Graphics.hpp>
#include "../../Renderer.h"

//class Renderer;

class LinkableObject : public sf::Sprite
{
    public:
        LinkableObject();
        virtual ~LinkableObject();

        int                 depth;
        Renderer::layer_t   layer;
    protected:
    private:

};

#endif // LINKEDOBJECT_H
