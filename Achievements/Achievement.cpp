#include "Achievement.h"

Achievement::Achievement(std::string name, std::string desc)
{
    //ctor
    SetName(name);
    SetDesc(desc);
}

Achievement::~Achievement()
{
    //dtor
}

std::string Achievement::GetName()
{
    return m_name;
}

std::string Achievement::GetDesc()
{
    return m_desc;
}

void Achievement::SetName(std::string name)
{
    m_name = name;
}

void Achievement::SetDesc(std::string desc)
{
    m_desc = desc;
}
