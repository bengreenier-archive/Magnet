/*#include "ShapeDraw.h"


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
    if (WorldStandards::debug)
    std::cout<<"Draw showing..\n";

    m_link=Renderer::CreateLink(Instance);

    if (WorldStandards::debug)
    std::cout<<"Draw shown\n";

    showing = true;
}

void ShapeDraw::Hide()
{
    if (showing)
    Renderer::RemoveLink(m_link);
}
*/
