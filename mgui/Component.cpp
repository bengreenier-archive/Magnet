#include "Component.h"
#include "../Game/Renderer.h"
using namespace mgui;

Component::Component(const char* name)
{
    m_name = name;
    init(0, 0, 100, 100);
}

Component::Component(const char* name, sf::Vector2f pos, sf::Vector2f size){
    m_name = name;
    init(pos.x, pos.y, size.x, size.y);
}

Component::~Component()
{
    Renderer::RemoveLink(this);
}

void Component::init(float x, float y, float width, float height){
    SetPosition(x, y);
    SetSize(width, height);
    EnableOutline(true);
    SetVisible(false);
    SetOutlineWidth(2);
    SetOutlineColor(sf::Color(255, 0, 0, 255));
}

void Component::SetSize(float width, float height){
    SetSize(sf::Vector2f(width, height));
}
void Component::SetSize(sf::Vector2f size){
    m_size = size;
    format();
}

void Component::format(){
    if(GetNbPoints() == 0){
        AddPoint(0, 0, GetColor(), GetOutlineColor());
        AddPoint(m_size.x, 0, GetColor(), GetOutlineColor() );
        AddPoint(m_size.x, m_size.y, GetColor(), GetOutlineColor() );
        AddPoint(0, m_size.y, GetColor(), GetOutlineColor() );
    }else{
        SetPointPosition(1, sf::Vector2f(m_size.x, 0));
        SetPointPosition(2, sf::Vector2f(m_size.x, m_size.y));
        SetPointPosition(3, sf::Vector2f(0, m_size.y));

        SetPointOutlineColor(0, GetOutlineColor());
        SetPointOutlineColor(1, GetOutlineColor());
        SetPointOutlineColor(2, GetOutlineColor());
        SetPointOutlineColor(3, GetOutlineColor());

        SetPointColor(0, GetColor());
        SetPointColor(1, GetColor());
        SetPointColor(2, GetColor());
        SetPointColor(3, GetColor());
    }
}

void Component::SetOutlineColor(sf::Color outlineCol){
    m_outlineColor = outlineCol;
    format();
}

sf::Color Component::GetOutlineColor(){
    return m_outlineColor;
}


void Component::SetColor(sf::Color color){
    m_color = color;
    format();
}
sf::Color Component::GetColor(){ return m_color; }

void Component::SetVisible(bool toggle){
    if(m_outline){
        EnableOutline(toggle);
    }

    EnableFill(toggle);
}

void Component::EnableOutline(bool enable){
    m_outline = enable;
    sf::Shape::EnableOutline(enable);
}

void Component::Create(){
    Renderer::CreateLink(this, Renderer::HudLayer);
}
