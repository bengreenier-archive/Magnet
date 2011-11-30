#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <SFML/Graphics.hpp>
#include "Layer.h"

template<typename T>
class RenderObject
{
    public:
        RenderObject();

        Layer           layer;
        int             depth;
        T&      object;

        bool isValid();
    protected:
    private:
        bool _valid;

};

#endif // RENDEROBJECT_H
