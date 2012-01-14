#include "Group.h"

using namespace mgui;

Group::Group()
{
    m_name = "";
}

Group::Group(const char* name)
{
    m_name = name;
}

Group::~Group()
{
}


void Group::SetPosition(sf::Vector2f newPosition){
    component_map_iterator_type cmp_iterator;


    for(cmp_iterator = m_component_map.begin(); cmp_iterator != m_component_map.end(); cmp_iterator++){
        cmp_iterator->second->SetPosition(cmp_iterator->second->GetPosition()+newPosition);
    }
}

void Group::AddComponent(Component* newCmp){
    if(ComponentExists(newCmp)) return;

    m_component_map.insert(std::pair<const char*, Component*>(newCmp->GetName(), newCmp));
}

bool Group::ComponentExists(Component* checkcmp){
    return (bool)m_component_map.count(checkcmp->GetName());
}
const char* Group::GetName(){ return m_name; }

