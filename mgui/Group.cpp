#include "Group.h"

using namespace mgui;

Group::Group(const char* name) : Component(name)
{
    EnableFill(false);
    EnableOutline(false);
    SetOutlineWidth(0);

    DebugOn();
}

Group::~Group()
{
}


void Group::SetPosition(sf::Vector2f newPosition){
    component_map_iterator_type cmp_iterator;


    for(cmp_iterator = m_component_map.begin(); cmp_iterator != m_component_map.end(); cmp_iterator++){
        cmp_iterator->second->SetPosition(sf::Vector2f(cmp_iterator->second->GetPosition().x+newPosition.x, cmp_iterator->second->GetPosition().y+newPosition.y));
    }

    sf::Shape::SetPosition(newPosition);
}

void Group::AddComponent(Component* newCmp){
    if(ComponentExists(newCmp)) return;

    newCmp->SetParent(this);
    m_component_map.insert(std::pair<const char*, Component*>(newCmp->GetName(), newCmp));
}

bool Group::ComponentExists(Component* checkcmp){
    return (bool)m_component_map.count(checkcmp->GetName());
}



bool Group::onMouseRelease(sf::Vector2f mouse_pos){
    if(m_component_map.empty()) return true;

    component_map_iterator_type     cmp_map_it;

    cmp_map_it = m_component_map.begin();
    while(cmp_map_it != m_component_map.end()){
        if(cmp_map_it->second->CheckBounds(mouse_pos)){
            if(!cmp_map_it->second->onMouseRelease(mouse_pos)){
                return false;
            }
        }

        cmp_map_it++;
    }

    return true;
}

const char* Group::GetName(){ return m_name; }

