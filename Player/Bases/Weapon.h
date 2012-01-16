#ifndef WEAPON_H
#define WEAPON_H

#include "ItemBase.h"
//might need to include <string>

class Weapon : ItemBase
{
    public:
        Weapon(std::string Name);
        ~Weapon();
    protected:
    private:
};

#endif // WEAPON_H
