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

        void ShowAll();
        void HideAll();

        void ShowFps();
        void HideFps();

        void ShowWorldCount();
        void HideWorldCount();
        void UpdateWorldCount();

    protected:
    private:
        b2World* m_managedWorldPtr;
        sf::String* m_wc;
};

#endif // WORLDSTATS_H
