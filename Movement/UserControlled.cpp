#include "UserControlled.h"

UserControlled::UserControlled()
{
    //ctor
}

UserControlled::UserControlled(int i)
{
    //ovrld ctor
    SetSpeed(i);
}


UserControlled::~UserControlled()
{
    //dtor
}

void BindKey(sf::Keyboard::Key kCode,Movement::Type mType)
{
// call KeyBindings::AddBinding();

}
