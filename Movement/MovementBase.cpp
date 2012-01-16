#include "MovementBase.h"

MovementBase::MovementBase()
{
    //ctor
    MovementSpeed=1;//Default movement speed
}

MovementBase::~MovementBase()
{
    //dtor
}

void MovementBase::SetSpeed(int i)
{
    MovementSpeed=i;
}
