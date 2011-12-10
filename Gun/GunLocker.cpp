#include "GunLocker.h"
#include "GunComponent.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

GunLocker* GunLocker::GunLockerPtr = NULL;

/*********************
    The constructor for
    the gun locker,
    creates all the
    available components.

*********************/
GunLocker::GunLocker()
{
    //create initial (core/main loaded/non manual/etc) components from raw data here.
    AddFrontComponent(new GunComponent(2,"Pain","Sprites/Guns/Assault/assault1-front.png"));
    AddMiddleComponent(new GunComponent(4,"In The","Sprites/Guns/Assault/assault1-middle.png"));
    AddRearComponent(new GunComponent(1,"Ass","Sprites/Guns/Assault/assault1-rear.png"));

    AddFrontComponent(new GunComponent(8,"Burn","Sprites/Guns/Assault/assault2-front.png"));
    AddMiddleComponent(new GunComponent(2,"Near Your","Sprites/Guns/Assault/assault2-middle.png"));
    AddRearComponent(new GunComponent(3,"Eyes","Sprites/Guns/Assault/assault2-rear.png"));

    AddFrontComponent(new GunComponent(5,"Sting","Sprites/Guns/Assault/assault3-front.png"));
    AddMiddleComponent(new GunComponent(11,"Up Your","Sprites/Guns/Assault/assault3-middle.png"));
    AddRearComponent(new GunComponent(7,"Toes","Sprites/Guns/Assault/assault3-rear.png"));

    //ctor
}

/**************************

    The Getter For GunLocker,
    as we only want to have one
     instance of this class,
      as near as i can tell.

**************************/
GunLocker* GunLocker::Get()
{
    if(GunLockerPtr==NULL)
    GunLockerPtr=new GunLocker();

    return GunLockerPtr;
}

/**************************************************

    A helper function for GunLocker() to
    return a sf::Image that consists of
    a file (image) from the given path.

**************************************************/
sf::Image GunLocker::ImageFromPath(std::string Path)
{
    sf::Image Image;

    if (!Image.LoadFromFile(Path))
    {
        std::cout<<"Failure To Load Image From: "<<Path<<"\n";
    }

    return Image;
}

/********************************************************

    Takes a GunComponent and adds it to the vector
    of front components, which is to signify it can be
    used at any point in the game.

********************************************************/
void GunLocker::AddFrontComponent(GunComponent* Component)
{
    Front.push_back(Component);
}

/********************************************************

    Takes a GunComponent and adds it to the vector
    of middle components, which is to signify it can be
    used at any point in the game.

********************************************************/
void GunLocker::AddMiddleComponent(GunComponent* Component)
{
    Middle.push_back(Component);
}


/********************************************************

    Takes a GunComponent and adds it to the vector
    of rear components, which is to signify it can be
    used at any point in the game.

********************************************************/
void GunLocker::AddRearComponent(GunComponent* Component)
{
    Rear.push_back(Component);
}

/************************
    return Front.size()
************************/
int GunLocker::FrontSize()
{
    return Front.size();
}

/************************
    return Middle.size()
************************/
int GunLocker::MiddleSize()
{
    return Middle.size();
}

/************************
    return Rear.size()
************************/
int GunLocker::RearSize()
{
    return Rear.size();
}

GunComponent* GunLocker::GetFrontComponent(int Index)
{
    return Front[Index];
}

GunComponent* GunLocker::GetMiddleComponent(int Index)
{
    return Middle[Index];
}

GunComponent* GunLocker::GetRearComponent(int Index)
{
    return Rear[Index];
}