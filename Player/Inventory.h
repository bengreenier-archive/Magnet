#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include "Bases/ItemBase.h"

class Inventory
{
    public:
        Inventory();
        ~Inventory();

        void Add(ItemBase in);
        void Remove(ItemBase in);

        Inventory* GetObject();//pointer to this class

        void Print();//cout<<inventory items

    protected:
    private:
        std::map< int , ItemBase > Objects;



        int AddCounter;
};

#endif // INVENTORY_H
