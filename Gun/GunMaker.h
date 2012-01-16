#ifndef GUNMAKER_H
#define GUNMAKER_H
#include <SFML/Graphics.hpp>
#include "GunComponent.h"

class GunMaker
{
    public:
        GunMaker(float Scale);
        void ConsoleAGun();
        void SetPosition(int x,int y);
        std::string name;
        int damage;
    protected:
    private:
        void        FormatDrawable(int x,int y);
        void        RenderGunInfo(int x,int y );
        std::string RenderGunInfo_Helper(int i);

        float ScaleFactor;

        sf::String m_nameCmp;//GunName
        sf::String m_damageCmp;

        GunComponent   FrontComponent;       // Points to the Front GunComponents Sprite
        GunComponent   MiddleComponent;      // Points to the Middle GunComponents Sprite
        GunComponent   RearComponent;        // Points to the Rear GunComponents Sprite




};

#endif // GUNMAKER_H
