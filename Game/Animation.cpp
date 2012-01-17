#include "Animation.h"

Animation::Animation(std::string imageDir,int eachVisibleFor)
{
    //ctor
    m_mainPath = imageDir;
    m_Fps = eachVisibleFor;
}

Animation::~Animation()
{
    //dtor
    delete Sprite;
}

void Animation::Cycle()
{
    //first,
}
