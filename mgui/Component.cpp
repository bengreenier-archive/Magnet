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
    m_debug = false;

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

    if(m_debug){
        _RemoveDebugLines();
        _CreateDebugLines();
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

void Component::DebugOn(){
    m_debug = true;

    _CreateDebugLines();
}

void Component::DebugOff(){
    m_debug = false;

    _RemoveDebugLines();
}

void Component::_CreateDebugLines(){
    std::cout << m_name << ": GETTING X POSITION\n";
    float xpos  =   this->GetPosition().x;
    std::cout << m_name << ": DONE GETTING X POSITION\t"<< xpos << "\n";
    debug_size_top      = sf::Shape::Line(GetPosition().x, GetPosition().y, GetPosition().x+GetSize().x, GetPosition().y, 10, sf::Color(255, 255, 255));
    /*debug_size_left     = sf::Shape::Line(GetPosition().x, GetPosition().y, GetPosition().x, GetPosition().y+GetSize().y, 1, sf::Color(255, 255, 255));
    debug_size_right    = sf::Shape::Line(GetPosition().x+GetSize().x, GetPosition().y, GetPosition().x, GetPosition().y+GetSize().y, 1, sf::Color(255, 255, 255));
    debug_size_bottom   = sf::Shape::Line(GetPosition().x, GetPosition().y+GetSize().y, GetPosition().x+GetSize().x, GetPosition().y+GetSize().y, 1, sf::Color(255, 255, 255));*/

    Renderer::CreateLink(&debug_size_top, Renderer::MenuLayer, 10);
    /*Renderer::CreateLink(&debug_size_left, Renderer::MenuLayer, 10);
    Renderer::CreateLink(&debug_size_right, Renderer::MenuLayer, 10);
    Renderer::CreateLink(&debug_size_bottom, Renderer::MenuLayer, 10);*/
}

void Component::_RemoveDebugLines(){
    Renderer::RemoveLink(&debug_size_top);
    /*Renderer::RemoveLink(&debug_size_left);
    Renderer::RemoveLink(&debug_size_right);
    Renderer::RemoveLink(&debug_size_bottom);*/

    debug_size_top.~Drawable();
    /*debug_size_left.~Drawable();
    debug_size_right.~Drawable();
    debug_size_bottom.~Drawable();*/
}
