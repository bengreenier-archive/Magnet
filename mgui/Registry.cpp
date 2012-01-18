#include "Registry.h"

using namespace mgui;

Registry::Registry()
{
    //ctor
}

Registry::~Registry()
{
    //dtor
}

void Registry::Register(Group* newGroup){
    if(GroupExists(newGroup)) return;

    m_group_map.insert(std::pair<const char*, Group*>(newGroup->GetName(), newGroup));
}

Group* Registry::GetByName(const char* groupName){
    if(GroupExists(groupName)){
        return m_group_map[groupName];
    }else{
        return new Group("GROUP_NOT_FOUND");
    }
}

bool Registry::GroupExists(Group* checkgrp){
    return (bool)m_group_map.count(checkgrp->GetName());
}

bool Registry::GroupExists(const char* grpname){
    return (bool)m_group_map.count(grpname);
}

void Registry::group_iterator_start(){
    m_group_map_it = m_group_map.begin();
}

bool Registry::do_iterate(){
    m_group_map_it++;

    if(m_group_map_it == m_group_map.end()){
        return false;
    }

    return true;
}

void Registry::onEvent(sf::Event evt){
    group_iterator_start();

    do{
        get_iterator()->second->onEvent(evt);
    }while(do_iterate());
}


Registry::group_map_iterator_type Registry::get_iterator(){ return m_group_map_it; }
