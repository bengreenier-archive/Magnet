#include "ShapeDraw.h"


ShapeDraw::ShapeDraw(sf::Drawable* shape)
{
    //ctor
    Instance = shape;
    showing = false;
}

ShapeDraw::~ShapeDraw()
{
    //dtor
}

void ShapeDraw::Show()
{
    m_link=Renderer::CreateLink(Instance);
    showing = true;
}

void ShapeDraw::Hide()
{
    if (showing)
    Renderer::RemoveLink(m_link);
}
