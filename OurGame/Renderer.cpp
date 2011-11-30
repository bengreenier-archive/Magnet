#include "Renderer.h"

void Renderer::Link(sf::Drawable* linkedObj, const int& layer, int depth){
    RenderHandler::GetObject()->Map(linkedObj, layer, depth);
}

/*
template<typename _T>
static void Renderer::Link(RenderObject<_T> &linkedObj){
    RenderHandler::GetObject()->Add(linkedObj);
}
*/
sf::RenderWindow* Window(){
    return RenderHandler::GetObject()->Window();
}

void draw(){
    RenderHandler::GetObject()->Render();
}
