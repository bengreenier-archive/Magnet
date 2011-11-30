#include "GunMaker.h"
#include "GunLocker.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

GunMaker::GunMaker()
{
        srand ( time(NULL) );
        //Generate random number for each part of the gun.
     fRand = rand() % GunLocker::Get()->FrontSize();
     mRand = rand() % GunLocker::Get()->MiddleSize();
     rRand = rand() % GunLocker::Get()->RearSize();
}

void GunMaker::ConsoleAGun()
{


    //Get the components we will be using to craft the gun.
    std::string fName   =   GunLocker::Get()->GetFrontComponent(fRand)->GetName();
    std::string mName   =   GunLocker::Get()->GetMiddleComponent(mRand)->GetName();
    std::string rName   =   GunLocker::Get()->GetRearComponent(rRand)->GetName();
    int         fDamage =   GunLocker::Get()->GetFrontComponent(fRand)->GetDamage();
    int         mDamage =   GunLocker::Get()->GetMiddleComponent(mRand)->GetDamage();
    int         rDamage =   GunLocker::Get()->GetRearComponent(rRand)->GetDamage();

    //Output the gun stats.
    std::cout<<fName<<" does "<<fDamage<<" damage.\n";
    std::cout<<mName<<" does "<<mDamage<<" damage.\n";
    std::cout<<rName<<" does "<<rDamage<<" damage.\n";
    std::cout<<"So the gun "<<fName<<" "<<mName<<" "<<rName<<" does "<<fDamage+mDamage+rDamage<<".\n";

}


void GunMaker::DrawTo(sf::RenderWindow& Window)
{
    //can't draw like this for some reason.
    Window.Draw(GunLocker::Get()->GetFrontComponent(fRand)->GetSprite("Front",0,0));
    Window.Draw(GunLocker::Get()->GetMiddleComponent(mRand)->GetSprite("Middle",0,0));
    Window.Draw(GunLocker::Get()->GetRearComponent(rRand)->GetSprite("Rear",0,0));
}
