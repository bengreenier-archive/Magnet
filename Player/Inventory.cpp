#include "Inventory.h"



Inventory::Inventory()
{
    //ctor
    AddCounter=0;
}

Inventory::~Inventory()
{
    //dtor
}




void Inventory::Add(ItemBase in)
{

    Objects[AddCounter]=in;


    AddCounter++;
}

void Inventory::Print()
{
    std::map<int,ItemBase>::iterator it;

    std::cout<<"Inventory Total: "<<Objects.size()<<" | ElementName List: ";

    for (it=Objects.begin(); it != Objects.end(); it++)
        std::cout<<(*it).second.ElementName<<" ";

    std::cout<<"\n";


}

void Inventory::Remove(ItemBase in)
{
    std::map<int,ItemBase>::iterator it;
    for (it=Objects.begin(); it != Objects.end(); it++)
        if ((*it).second.ElementName.compare(in.ElementName)==0)
            if ((*it).second.ElementType.compare(in.ElementType)==0)
                    Objects.erase(it);

    //erase it if Name and Type Strings match.
}
