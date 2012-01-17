#include "Component.h"
#include "../Game/Renderer.h"


#include "Group.h"
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
    SetSize(sf::Vector2f(width, height));
    EnableOutline(true);
    SetVisible(false);
    SetOutlineWidth(2);
    SetOutlineColor(sf::Color(255, 0, 0, 255));
}

bool Component::CheckBounds(sf::Vector2f coord){
    //Check x bounds
    if(coord.x > GetPosition().x && coord.x < (GetPosition().x+GetSize().x)){
        //Check y bounds
        if(coord.y > GetPosition().y && coord.y < (GetPosition().y+GetSize().y)){
            return true;
        }
    }

    return false;
}

sf::Vector2f Component::GetSize(){
    return sf::Vector2f(Sizeable::GetSize().x + GetOutlineWidth()*2, Sizeable::GetSize().y + GetOutlineWidth()*2);
}

void Component::SetSize(sf::Vector2f size){
    Sizeable::SetSize(size);
    format();
}

sf::Vector2f Component::GetPosition(){
    return sf::Vector2f(sf::Shape::GetPosition().x - GetOutlineWidth(), sf::Shape::GetPosition().y - GetOutlineWidth());
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

    m_visible = toggle;
}

void Component::EnableOutline(bool enable){
    m_outline = enable;
    sf::Shape::EnableOutline(enable);
}

void Component::Create(){
    Renderer::CreateLink(static_cast<sf::Shape*>(this), Renderer::HudLayer);
}

void Component::SetParent(Component* parent){
    m_parent = parent;
    m_isChild = true;
}
