#include "LinkableSprite.h"


LinkableSprite::LinkableSprite()
{
    //sprite = sprite_ptr;
    depth = 0;
    layer = Renderer::GameLayer;

}

LinkableSprite::LinkableSprite(int depth, Renderer::layer_t layer)
{
    LinkableSprite::depth = depth;
    LinkableSprite::layer = layer;
}

