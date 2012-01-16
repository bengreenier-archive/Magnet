#ifndef WORLDSTATS_H
#define WORLDSTATS_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

//magnet included in .cpp

class WorldStats
{
    public:

        WorldStats(b2World* in);
        ~WorldStats();

        void ShowAll(int x,int y);
        void HideAll();

        void ShowFps(int x,int y);
        void HideFps();
        void UpdateFps(int x,int y);

        void ShowWorldCount(int x,int y);
        void HideWorldCount();
        void UpdateWorldCount(int x, int y);

    protected:
    private:
        b2World* m_managedWorldPtr;
        sf::String* m_wc;
        sf::String* m_fps;
};

#endif // WORLDSTATS_H
