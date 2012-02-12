#ifndef USERCONTROLLED_H
#define USERCONTROLLED_H

#include "MovementBase.h"


#include <SFML/Graphics.hpp>

class UserControlled : MovementBase
{
    public:
        UserControlled();
        UserControlled(int i);//used to set speed on construction
        ~UserControlled();
        void BindKey(sf::Keyboard::Key kCode,Movement::Type mType);
    protected:
    private:
};

#endif // USERCONTROLLED_H
