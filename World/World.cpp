#include "World.h"

World::World()
{
    //ctor

    m_world1 = new b2World(b2Vec2(0.0f,10.0f));

}

b2World* World::Access()
{
    return this->m_world1;
}

 sf::RenderWindow* World::RenderAccess()
 {
     return Renderer::GetRenderWindow();
 }

sf::Color World::B2SFColor(const b2Color &color, int alpha)
{
	sf::Color result((sf::Uint8)(color.r*255), (sf::Uint8)(color.g*255), (sf::Uint8)(color.b*255), (sf::Uint8) alpha);
	return result;
}
