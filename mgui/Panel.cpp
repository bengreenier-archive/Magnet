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

bool Panel::onMouseRelease(sf::Event evt){
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

bool Panel::onMousePress(sf::Event evt){
    if(evt.MouseButton.Button == sf::Mouse::Left){
        m_mouse_down = true;
        m_mouse_dist = sf::Vector2f(evt.MouseButton.X - GetPosition().x, evt.MouseButton.Y-GetPosition().y);
    }else if(evt.MouseButton.Button == sf::Mouse::Right){
        Remove();
    }
    return false;
}
