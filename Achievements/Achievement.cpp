#include "Achievement.h"

Achievement::Achievement(std::string name, std::string desc,CompletionFunction complete)
{
    //ctor
    SetName(name);
    SetDesc(desc);
    SetCompleteFunction(complete);
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
/*
void Achievement::SetFunction(AchievementFunction fn)
{
    m_fn_cond = fn;
}
*/
void Achievement::SetCompleteFunction(CompletionFunction fn)
{
    m_fn_comp = fn;
}

/*
bool Achievement::CheckFunction()
{
    if (m_fn_cond==NULL)
        return false;

    if (m_fn_cond){return true;}else{return false;}
}
*/
void Achievement::Completed()
{
    m_fn_comp;
}
