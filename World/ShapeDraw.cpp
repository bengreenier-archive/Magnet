#include "ShapeDraw.h"


ShapeDraw::ShapeDraw(sf::Drawable* shape)
{
    //ctor
    m_shape = shape;
    showing = false;
}

ShapeDraw::~ShapeDraw()
{
    //dtor
}

void ShapeDraw::Show()
{
    m_link=Renderer::CreateLink(m_shape);
    showing = true;
}

void ShapeDraw::Hide()
{
    if (showing)
    Renderer::RemoveLink(m_link);
}
