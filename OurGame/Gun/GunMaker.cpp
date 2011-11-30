#include "GunMaker.h"
#include "GunLocker.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

GunMaker::GunMaker()
{

}

void GunMaker::ConsoleAGun()
{
    srand ( time(NULL) );

    int fRand = rand() % GunLocker::Get()->FrontSize();
    int mRand = rand() % GunLocker::Get()->MiddleSize();
    int rRand = rand() % GunLocker::Get()->RearSize();

    std::string fName   =   GunLocker::Get()->GetFrontComponent(fRand).GetName();
    std::string mName   =   GunLocker::Get()->GetMiddleComponent(mRand).GetName();
    std::string rName   =   GunLocker::Get()->GetRearComponent(rRand).GetName();
    int         fDamage =   GunLocker::Get()->GetFrontComponent(fRand).GetDamage();
    int         mDamage =   GunLocker::Get()->GetMiddleComponent(mRand).GetDamage();
    int         rDamage =   GunLocker::Get()->GetRearComponent(rRand).GetDamage();

    std::cout<<fName<<" does "<<fDamage<<" damage.\n";
    std::cout<<mName<<" does "<<mDamage<<" damage.\n";
    std::cout<<rName<<" does "<<rDamage<<" damage.\n";
    std::cout<<"So the gun "<<fName<<" "<<mName<<" "<<rName<<" does "<<fDamage+mDamage+rDamage<<".\n";

}
