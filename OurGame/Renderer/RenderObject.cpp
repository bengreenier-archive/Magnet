#include "RenderObject.h"
#include "Layer.h"

template <typename T>
RenderObject<T>::RenderObject()
{
    depth   =   0;
    layer   =   Layer::GAME;
}

template <typename T>
bool RenderObject<T>::isValid(){
    return _valid;
}
