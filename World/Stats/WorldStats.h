#ifndef WORLDSTATS_H
#define WORLDSTATS_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

//magnet included in .cpp

class WorldStats //! Create stats for a world! info like FPS and total bodies are here.
{
    public:

        WorldStats(b2World* in); //!< Default constructor
        ~WorldStats();

        void ShowAll(int x,int y); //!< Show all available stats.
        void HideAll(); //!< Hide all available stats.

        void ShowFps(int x,int y); //!< Show fps
        void HideFps(); //!< Hide fps
        void UpdateFps(int x,int y); //!< Update fps

        void ShowWorldCount(int x,int y); //!< show total objects in world
        void HideWorldCount(); //!< hide total objects in world
        void UpdateWorldCount(int x, int y); //!< update total objects in world

    protected:
    private:
        b2World* m_managedWorldPtr;
        sf::String* m_wc;
        sf::String* m_fps;
};

#endif // WORLDSTATS_H
