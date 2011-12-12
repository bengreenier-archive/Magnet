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
     name   = GunLocker::Get()->GetRandomName();
     damage = GunLocker::Get()->Random(9)+1;
     ScaleFactor=Scale;//For Now, until this constructor takes a scale

     /*//this mess supossibly rerandomizes until types match.


     //set the sprite pointers to GunComponents
     //FrontComponent = *GunLocker::Get()->GetFrontComponent(fRand);
     //MiddleComponent = *GunLocker::Get()->GetMiddleComponent(mRand);
     //RearComponent = *GunLocker::Get()->GetRearComponent(rRand);
     */

     FrontComponent = GunLocker::Get()->GetRandomComponent(GunEnum::Front, GunEnum::Light);
     MiddleComponent = GunLocker::Get()->GetRandomComponent(GunEnum::Middle, GunEnum::Light);
     RearComponent = GunLocker::Get()->GetRandomComponent(GunEnum::Rear, GunEnum::Light);


     Renderer::CreateLink(FrontComponent.GetSpritePtr());
     Renderer::CreateLink(MiddleComponent.GetSpritePtr());
     Renderer::CreateLink(RearComponent.GetSpritePtr());
     Renderer::CreateLink(&m_nameCmp);
     Renderer::CreateLink(&m_damageCmp);

}

void GunMaker::ConsoleAGun()
{
    std::cout<<"The gun "<< name <<" does "<< damage <<".\n";

}


void GunMaker::SetPosition(int x,int y)
{
    FormatDrawable(x,y);
    RenderGunInfo(x,y);

}

void GunMaker::FormatDrawable(int x,int y)
{
    /*
    int fLength =FrontComponent->Length;
    int mLength =MiddleComponent->Length;
    int rLength =RearComponent->Length;
    */

    std::cout << "Making changes!\n";

    int fWidth  =FrontComponent.GetWidth();
    int mWidth  =MiddleComponent.GetWidth();
    int rWidth  =RearComponent.GetWidth();

    //Scale the Sprites
    RearComponent.GetSpritePtr()->SetScale(ScaleFactor,ScaleFactor);
    MiddleComponent.GetSpritePtr()->SetScale(ScaleFactor,ScaleFactor);
    FrontComponent.GetSpritePtr()->SetScale(ScaleFactor,ScaleFactor);

    //Set Sprite Draw Positions
    RearComponent.GetSpritePtr()->SetPosition(x,y);
    MiddleComponent.GetSpritePtr()->SetPosition(x+(ScaleFactor*rWidth),y);
    FrontComponent.GetSpritePtr()->SetPosition(x+(ScaleFactor*rWidth)+(ScaleFactor*mWidth),y);

    Renderer::invalidate(NULL);
}

void GunMaker::RenderGunInfo(int x,int y)
{

int mLength = MiddleComponent.GetHeight();

m_nameCmp.SetText(name);
m_nameCmp.SetSize(24);
m_nameCmp.SetColor(sf::Color(140,240,240));
m_nameCmp.SetPosition(x,y+(ScaleFactor*mLength));




m_damageCmp.SetText("Damage: "+RenderGunInfo_Helper(damage));
m_damageCmp.SetSize(18);
m_damageCmp.SetColor(sf::Color(140,240,240));
m_damageCmp.SetPosition(x,y+(ScaleFactor*mLength)+26);

}

std::string GunMaker::RenderGunInfo_Helper(int i)//this should be in conversions
{
    std::stringstream ss;
    ss<<i;
    return ss.str();
}
