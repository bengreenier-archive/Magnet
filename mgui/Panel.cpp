/*#include "Panel.h"
#include "../Game/Resource.h"

using namespace mgui;

Panel::Panel(const char* name) : Component(name)
{
    m_mouse_down = false;
    m_text.SetText("Default panel text");
    m_text.SetFontSize(14);
    m_text.SetParent(this);
    //m_label.SetFont(Resource::GetFont("font/tahomabd.ttf"));
}

Panel::Panel(const char* name, const char* label) : Component(name)
{
    m_mouse_down = false;
    m_text.SetText(label);
}

Panel::~Panel()
{
    //dtor
}

void Panel::DebugOn(){
    m_text.DebugOn();
    Component::DebugOn();
}

void Panel::DebugOff(){
    m_text.DebugOff();
    Component::DebugOff();
}

void Panel::Format(){
    m_text.Update();
    Component::Format();
}

void Panel::Create(){
    Component::Create();
    m_text.Create();
}

void Panel::Remove(){
    if(m_text.IsCreated()){
        m_text.Remove();
    }
    Component::Remove();
}

void Panel::SetDepth(int depth){
    m_text.SetDepth(depth+1);
    Component::SetDepth(depth);
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
    m_mouse_down = true;
    return false;
}*/
