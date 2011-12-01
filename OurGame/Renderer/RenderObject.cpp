#include "RenderObject.h"
#include "Layer.h"

RenderObject::RenderObject()
{
    depth   =   0;
    layer   =   Layer::GAME;
    object  =   NULL;
}

bool RenderObject::isValid(){
    if(object ==  NULL) return false;

    return true;
}
