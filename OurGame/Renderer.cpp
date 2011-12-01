#include "Renderer.h"

//template <typename T>
void Renderer::Link(sf::Drawable* linkedObj){
    RenderHandler::GetObject()->Map(linkedObj, RenderHandler::GAME_LAYER, 0);
}

void Renderer::Link(sf::Drawable* linkedObj, RenderHandler::Layer layer){
    RenderHandler::GetObject()->Map(linkedObj, layer, 0);
}

void Renderer::Link(sf::Drawable* linkedObj, RenderHandler::Layer layer, int depth){
    RenderHandler::GetObject()->Map(linkedObj, layer, depth);
}

void Renderer::RemapDepth(sf::Drawable* linkedObj, int depth){
    RenderHandler::GetObject()->RemapDepth(linkedObj, depth);
}

/*
template<typename _T>
static void Renderer::Link(RenderObject<_T> &linkedObj){
    RenderHandler::GetObject()->Add(linkedObj);
}
*/
sf::RenderWindow* Renderer::Window(){
    return RenderHandler::GetObject()->Window();
}

void Renderer::draw(){
    RenderHandler::GetObject()->Render();
}
