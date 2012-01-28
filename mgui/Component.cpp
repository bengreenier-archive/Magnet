#include "Component.h"
#include "Registry.h"

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
    if(m_created){
        Remove();
    }

    if(m_link != m_default_link){
        delete m_default_link;
    }
}

void Component::init(float x, float y, float width, float height){
    m_debug     = false;
    m_created   = false;
    m_isChild   = false;
    m_canFocus  = true;
    m_registry  = NULL;
    m_link      = NULL;
    m_parent    = NULL;
    debug_color         = sf::Color(255, 0, 0, 255);
    debug_color_focus   = sf::Color(0, 255, 0, 255);

    SetPosition(x, y);
    SetSize(sf::Vector2f(width, height));
    EnableFill(true);
    EnableOutline(true);
    SetVisible(false);
    SetOutlineWidth(0);
    SetOutlineColor(sf::Color(255, 0, 0, 255));
    SetColor(sf::Color(255, 255, 255));

    //Set up default component link
    SetRendererLink(new Renderer::Link());
    Link()->object   = static_cast<sf::Shape*>(this);
    Link()->layer    = Renderer::MenuLayer;
    if(IsRegistered()){
        Link()->depth = GetRegistry()->GetNextDepth();
    }else{
        Link()->depth = 0;
    }
    m_default_link = Link();
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
    Format();
}

sf::Vector2f Component::GetPosition(){
    return sf::Vector2f(sf::Shape::GetPosition().x - GetOutlineWidth(), sf::Shape::GetPosition().y - GetOutlineWidth());
}
/*
void Component::SetPosition(sf::Vector2f pos){
    //sf::Shape::SetPosition(sf::Vector2f(pos.x))
}
*/

void Component::Format(){
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
        if(HasFocus()){
            _UpdateDebugLines(debug_color_focus);
        }else{
            _UpdateDebugLines(debug_color);
        }
    }
}

void Component::SetOutlineColor(sf::Color outlineCol){
    m_outlineColor = outlineCol;
    Format();
}

sf::Color Component::GetOutlineColor(){
    return m_outlineColor;
}


void Component::SetColor(sf::Color color){
    m_color = color;
    Format();
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

    if(!enable){
        SetOutlineWidth(0);
    }
}

int Component::GetDepth(){
    if(!IsLinked()) return 0;

    return Link()->depth;
}

void Component::SetDepth(int depth){
    if(!IsLinked()) return;

    Renderer::SetLinkDepth(Link(), depth);
}

void Component::Create(){
    if(Link() == NULL) return;
    if(Renderer::Object()->LinkExists(Link())) return;
    Renderer::CreateLink(Link());

    m_created = true;
}

bool Component::IsLinked(){
    if(Link() == NULL){
        return false;
    }

    return true;
}
void Component::Remove(){
    if(IsRegistered()){
        GetRegistry()->Remove(this);
    }else{
        Renderer::RemoveLink(Link());

        if(m_debug){
            DebugOff();
        }
        m_created = false;
    }

}

Renderer::Link* Component::Link(){
    if(m_link == NULL){
        std::cout << "[Component][Link]\tWARNING: " << GetName() << " link is null, returning NULL\n";
    }

    return m_link;
}

void Component::SetParent(Component* parent){
    m_parent = parent;
    m_isChild = true;
}

bool Component::onMouseEvent(sf::Event evt){
    sf::Vector2f mouse_pos;

    switch(evt.Type){
        case sf::Event::MouseButtonReleased:
            mouse_pos = sf::Vector2f(evt.MouseButton.X, evt.MouseButton.Y);
            return onMouseRelease(evt);
            break;
        case sf::Event::MouseMoved:
            mouse_pos = sf::Vector2f(evt.MouseMove.X, evt.MouseMove.Y);

            return onMouseMove(mouse_pos);
            break;
        case sf::Event::MouseButtonPressed:
            mouse_pos = sf::Vector2f(evt.MouseButton.X, evt.MouseButton.Y);
            return onMousePress(evt);
            break;
    }

    return true;
}

void Component::SetRegistry(Registry* reg){
    m_registry = reg;
}

Registry* Component::GetRegistry(){
    return m_registry;
}

bool Component::IsRegistered(){
    if(m_registry == NULL){
        return false;
    }

    return true;
}

bool Component::HasFocus(){
    if(GetRegistry() == NULL) return false;
    if(GetRegistry()->GetFocus() == NULL) return false;

    return (bool)(GetRegistry()->GetFocus() == this);
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
    //int depth = m_link->depth+1;
    int depth = 1;
    Renderer::CreateLink(&debug_size_top, Renderer::MenuLayer, depth);
    Renderer::CreateLink(&debug_size_left, Renderer::MenuLayer, depth);
    Renderer::CreateLink(&debug_size_right, Renderer::MenuLayer, depth);
    Renderer::CreateLink(&debug_size_bottom, Renderer::MenuLayer, depth);
}

void Component::_UpdateDebugLines(sf::Color drawColor){
    float x             =   GetPosition().x;
    float y             =   GetPosition().y;
    float width         =   GetSize().x;
    float height        =   GetSize().y;
    float line_width    =   1;

    //
    debug_size_top      = sf::Shape::Line(x-line_width, y-line_width, x+width+line_width, y-line_width, line_width, drawColor);
    debug_size_left     = sf::Shape::Line(x, y, x, y+height+line_width, line_width, drawColor);
    debug_size_right    = sf::Shape::Line(x+width+line_width, y-line_width, x+width+line_width, y+height, line_width, drawColor);
    debug_size_bottom   = sf::Shape::Line(x-line_width, y+height, x+width+line_width, y+height, line_width, drawColor);
}

void Component::_RemoveDebugLines(){
    Renderer::RemoveLink(&debug_size_top);
    Renderer::RemoveLink(&debug_size_left);
    Renderer::RemoveLink(&debug_size_right);
    Renderer::RemoveLink(&debug_size_bottom);
}
