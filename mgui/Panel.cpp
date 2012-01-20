#include "Panel.h"

using namespace mgui;

Panel::Panel(const char* name) : Component(name)
{
    m_mouse_down = false;
}

Panel::~Panel()
{
    //dtor
}

bool Panel::onMouseRelease(sf::Vector2f mouse_pos){
    std::cout << "Mouse release\n";
    m_mouse_down = false;
    return false;
}

bool Panel::onMouseMove(sf::Vector2f mouse_pos){
    if(m_mouse_down){
        SetPosition(mouse_pos - m_mouse_dist);
    }

    Format();
    return true;
}

bool Panel::onMousePress(sf::Vector2f mouse_pos){
    m_mouse_down = true;
    m_mouse_dist = mouse_pos - GetPosition();
    return false;
}
