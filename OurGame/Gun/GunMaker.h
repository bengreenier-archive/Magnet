#ifndef GUNMAKER_H
#define GUNMAKER_H
#include <SFML/Graphics.hpp>
class GunMaker
{
    public:
        GunMaker();
        void ConsoleAGun();
        void DrawTo(sf::RenderWindow& Window,int x,int y);
    protected:
    private:
        int fRand;
        int mRand;
        int rRand;

};

#endif // GUNMAKER_H
