#ifndef SELECTED_H
#define SELECTED_H
#include "Bases/ItemBase.h"

#include <iostream>
#include <vector>
#include <string>


/*********************************
        ITS IMPORTANT TO KNOW:
        Selected doesn't create Base(s),
   it only stores them and accesses them.
and it should only store the ones in use.
*********************************/
class Selected
{
    public:
        Selected();
        ~Selected();
        //function to add new Bases to Selected Layout (Takes a base)
        void Add(ItemBase In);

        //function to get Bases from Selected Layout, by name (Std::string)
        ItemBase* Equipped(std::string In);

    protected:
    private:
        std::vector <ItemBase> Objects;
};

#endif // SELECTED_H
