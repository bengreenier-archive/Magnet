#include "GunMaker.h"
#include "GunLocker.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

GunMaker::GunMaker(float Scale)
{
     ScaleFactor=Scale;//For Now, until this constructor takes a scale
        //Generate random number for each part of the gun.
     fRand = rand() % GunLocker::Get()->FrontSize();
     mRand = rand() % GunLocker::Get()->MiddleSize();
     rRand = rand() % GunLocker::Get()->RearSize();

     //Get the components we will be using to craft the gun.
     fName   =   GunLocker::Get()->GetFrontComponent(fRand)->GetName();
     mName   =   GunLocker::Get()->GetMiddleComponent(mRand)->GetName();
     rName   =   GunLocker::Get()->GetRearComponent(rRand)->GetName();
     fDamage =   GunLocker::Get()->GetFrontComponent(fRand)->GetDamage();
     mDamage =   GunLocker::Get()->GetMiddleComponent(mRand)->GetDamage();
     rDamage =   GunLocker::Get()->GetRearComponent(rRand)->GetDamage();

     //set the sprite pointers to GunComponents
     FrontComponent = GunLocker::Get()->GetFrontComponent(fRand);
     MiddleComponent = GunLocker::Get()->GetMiddleComponent(mRand);
     RearComponent = GunLocker::Get()->GetRearComponent(rRand);

}

void GunMaker::ConsoleAGun()
{
    //Output the gun stats.
    std::cout<<fName<<" does "<<fDamage<<" damage.\n";
    std::cout<<mName<<" does "<<mDamage<<" damage.\n";
    std::cout<<rName<<" does "<<rDamage<<" damage.\n";
    std::cout<<"So the gun "<<fName<<" "<<mName<<" "<<rName<<" does "<<fDamage+mDamage+rDamage<<".\n";

}


void GunMaker::DrawTo(sf::RenderWindow& Window,int x,int y)
{
    FormatDrawable(x,y);

    Window.Draw(RearComponent->Sprite);
    Window.Draw(MiddleComponent->Sprite);
    Window.Draw(FrontComponent->Sprite);
}

void GunMaker::FormatDrawable(int x,int y)
{
    int fLength =FrontComponent->Length;
    int mLength =MiddleComponent->Length;
    int rLength =RearComponent->Length;

    int fWidth  =FrontComponent->Width;
    int mWidth  =MiddleComponent->Width;
    int rWidth  =RearComponent->Width;

    //Scale the Sprites
    RearComponent->Sprite.SetScale(ScaleFactor,ScaleFactor);
    MiddleComponent->Sprite.SetScale(ScaleFactor,ScaleFactor);
    FrontComponent->Sprite.SetScale(ScaleFactor,ScaleFactor);

    //Set Sprite Draw Positions
    RearComponent->Sprite.SetPosition(x,y);
    MiddleComponent->Sprite.SetPosition(x+(ScaleFactor*rWidth),y);
    FrontComponent->Sprite.SetPosition(x+(ScaleFactor*rWidth)+(ScaleFactor*mWidth),y);
}
