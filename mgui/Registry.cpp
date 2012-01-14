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
        return new Group();
    }
}

bool Registry::GroupExists(Group* checkgrp){
    return (bool)m_group_map.count(checkgrp->GetName());
}

bool Registry::GroupExists(const char* grpname){
    return (bool)m_group_map.count(grpname);
}
