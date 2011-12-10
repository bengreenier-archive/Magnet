#ifndef PLAYER_H
#define PLAYER_H
#include "Inventory.h"
#include "Selected.h"

class Player
{
    public:
        Player();
        ~Player();
        Inventory Items;
        Selected Select;
    protected:
    private:
};

#endif // PLAYER_H
