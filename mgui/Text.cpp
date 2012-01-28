#include "Text.h"
#include "../Game/Resource.h"

using namespace mgui;

Text::Text() : Component("default_text_name")
{
    init("Default text", Text::AlignLeft);
}

Text::Text(const char* name) : Component(name)
{
    init("Default text", Text::AlignLeft);
}
Text::Text(const char* name, const char* string) : Component(name)
{
    init(string, Text::AlignLeft);
}

Text::Text(const char* name, const char* string, AlignType align) : Component(name)
{
    init(string, align);
}

Text::~Text(){
    //remove link
}

void Text::init(const char* string, AlignType align){
    m_string.SetText(string);
    m_string.SetFont(Resource::GetFont("font/tahoma.ttf"));
    m_align =   align;

    Component::EnableFill(false);
    Component::EnableOutline(false);
    Component::SetOutlineWidth(0);

    SetFontSize(12);

    m_text_link = new Renderer::Link();
    m_text_link->object = &m_string;
    m_text_link->layer  = Renderer::MenuLayer;
    m_text_link->depth  = GetDepth()+1;
    SetRendererLink(m_text_link);
}
void Text::SetText(const char* text){
    m_string.SetText(text);
    Update();
}

void Text::SetFontSize(int size){
    m_string.SetSize(size);
    Update();
}

void Text::SetPosition(sf::Vector2f pos){
    Component::SetPosition(pos);
    m_string.SetPosition(pos);
}

void Text::Update(){
    SetSize(sf::Vector2f(m_string.GetRect().GetWidth(), m_string.GetRect().GetHeight()));

    if(IsChild()){
        sf::Vector2f newPos;
        newPos.x = GetParent()->GetPosition().x + GetParent()->GetOutlineWidth();
        newPos.y = GetParent()->GetPosition().y + GetParent()->GetOutlineWidth();

        SetPosition(newPos);
    }

    Format();
}

