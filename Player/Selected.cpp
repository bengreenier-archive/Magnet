#include "Selected.h"

Selected::Selected()
{
    //ctor
}

Selected::~Selected()
{
    //dtor
}

void Selected::Add(ItemBase In)
{
    Objects.push_back(In);
}

ItemBase* Selected::Equipped(std::string In)
{
    std::vector <ItemBase>::iterator it;

    for ( it=Objects.begin() ; it < Objects.end(); it++ )
        if (it->ElementName.compare(In) == 0)
            return &*it;

    for ( it=Objects.begin() ; it < Objects.end(); it++ )
        if (it->ElementType.compare(In) == 0)
            return &*it;

std::cout<<"Selected Equipped("<<In<<") did not work. No return success.\n";
}
