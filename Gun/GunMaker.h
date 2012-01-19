#ifndef GUNMAKER_H
#define GUNMAKER_H
#include <SFML/Graphics.hpp>
#include "GunComponent.h"

class GunMaker //! The GunFactory class that creates and formats/etc a new gun.
{
    public:
        GunMaker(float Scale); //!< Default Constructor
        void ConsoleAGun(); //!< Print gun info to console
        void SetPosition(int x,int y); //!< Set gun screen position
        std::string name; //!< The gun name
        int damage; //!< The gun damage multiplier
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
