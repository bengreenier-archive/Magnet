#include "GunMaker.h"
#include "GunLocker.h"
#include "../Renderer.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>

#include "../ImageHandler.h"

GunMaker::GunMaker(float Scale)
{


     ScaleFactor=Scale;//For Now, until this constructor takes a scale

     //this mess supossibly rerandomizes until types match.
     do{

               //Generate random number for each part of the gun.
     fRand = rand() % GunLocker::Get()->FrontSize();
     mRand = rand() % GunLocker::Get()->MiddleSize();
     rRand = rand() % GunLocker::Get()->RearSize();

            }while (
            (GunLocker::Get()->GetFrontComponent(fRand)->GetType().compare(GunLocker::Get()->GetMiddleComponent(mRand)->GetType()) !=0)
            &&(GunLocker::Get()->GetRearComponent(rRand)->GetType().compare(GunLocker::Get()->GetMiddleComponent(mRand)->GetType()) !=0)
            &&(GunLocker::Get()->GetFrontComponent(fRand)->GetType().compare(GunLocker::Get()->GetRearComponent(rRand)->GetType()) !=0)
            );

     //Get the components we will be using to craft the gun.
     fName   =   GunLocker::Get()->GetFrontComponent(fRand)->GetName();
     mName   =   GunLocker::Get()->GetMiddleComponent(mRand)->GetName();
     rName   =   GunLocker::Get()->GetRearComponent(rRand)->GetName();
     fDamage =   GunLocker::Get()->GetFrontComponent(fRand)->GetDamage();
     mDamage =   GunLocker::Get()->GetMiddleComponent(mRand)->GetDamage();
     rDamage =   GunLocker::Get()->GetRearComponent(rRand)->GetDamage();

    tDamage=fDamage+mDamage+rDamage;

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


//void GunMaker::SetPosition(int x,int y)
void GunMaker::DrawTo(int x,int y)
{
    FormatDrawable(x,y);
    RenderGunInfo(x,y);
    Renderer::Link(*RearComponent);
    Renderer::Link(*MiddleComponent);
    Renderer::Link(*FrontComponent);

}

void GunMaker::FormatDrawable(int x,int y)
{
    /*
    int fLength =FrontComponent->Length;
    int mLength =MiddleComponent->Length;
    int rLength =RearComponent->Length;
    */

    int fWidth  =FrontComponent->Width;
    int mWidth  =MiddleComponent->Width;
    int rWidth  =RearComponent->Width;

    //Scale the Sprites
    RearComponent->SetScale(ScaleFactor,ScaleFactor);
    MiddleComponent->SetScale(ScaleFactor,ScaleFactor);
    FrontComponent->SetScale(ScaleFactor,ScaleFactor);

    //Set Sprite Draw Positions
    RearComponent->SetPosition(x,y);
    MiddleComponent->SetPosition(x+(ScaleFactor*rWidth),y);
    FrontComponent->SetPosition(x+(ScaleFactor*rWidth)+(ScaleFactor*mWidth),y);
}

void GunMaker::RenderGunInfo(int x,int y)
{

int mLength = MiddleComponent->Length;

Name.SetText(fName+" "+mName+" "+rName);
Name.SetSize(24);
Name.SetColor(sf::Color(140,240,240));
Name.SetPosition(x,y+(ScaleFactor*mLength));




Damage.SetText("Damage: "+RenderGunInfo_Helper(fDamage+mDamage+rDamage));
Damage.SetSize(18);
Damage.SetColor(sf::Color(140,240,240));
Damage.SetPosition(x,y+(ScaleFactor*mLength)+26);

}

std::string GunMaker::RenderGunInfo_Helper(int i)//this should be in conversions
{
    std::stringstream ss;
    ss<<i;
    return ss.str();
}
