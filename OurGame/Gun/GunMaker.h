#ifndef GUNMAKER_H
#define GUNMAKER_H
#include <SFML/Graphics.hpp>
#include "GunComponent.h"

class GunMaker
{
    public:
        GunMaker(float Scale);
        void ConsoleAGun();
        void DrawTo(sf::RenderWindow& Window,int x,int y);
    protected:
    private:
        void FormatDrawable(int x,int y);

        float ScaleFactor;
        int fRand;
        int mRand;
        int rRand;
        int fDamage;
        int mDamage;
        int rDamage;
        std::string fName;
        std::string mName;
        std::string rName;

        GunComponent*   FrontComponent;       // Points to the Front GunComponents Sprite
        GunComponent*   MiddleComponent;      // Points to the Middle GunComponents Sprite
        GunComponent*   RearComponent;        // Points to the Rear GunComponents Sprite

};

#endif // GUNMAKER_H
