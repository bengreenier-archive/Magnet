#ifndef MAGNET_H
#define MAGNET_H

#include <SFML/Graphics.hpp>


#include "Renderer.h"

#include "Handlers/EventHandler.h"

#include "Game/State.h"
#include "Game/Hook.h"
#include "Game/ManagedThread.h"
#include "Game/MouseTrail.h"

class Magnet
{
    public:

        //Garbage collection
        virtual ~Magnet();

        static Magnet* Object();

        static void Frame();

        //////////////////////////////////////////
        /// Called on space press
        //////////////////////////////////////////
        static void Event_SpacePressed(sf::Event evt);
        static void Event_MouseMove(sf::Event evt);

        //////////////////////////////////////////
        /// Start the game
        ///
        ///     Changes state to InGame
        //////////////////////////////////////////
        static void StartGame();

        //////////////////////////////////////////
        /// Retrieve the global mutex
        //////////////////////////////////////////
        static sf::Mutex* GlobalMutex();

        //////////////////////////////////////////
        /// Retrieve the global hook registry
        //////////////////////////////////////////
        static Hook::Registry* Hooks();

        //////////////////////////////////////////
        /// Change the current state of the game
        //////////////////////////////////////////
        void ChangeState(State::_type newState);

    protected:
        //Magnet initialization stuff
        Magnet(State::_type defaultState);
    private:
        static Magnet* magnet_ptr;
        State gameState;

        sf::Mutex m_globalMutex;
        Hook::Registry m_hooks;

        MouseTrail m_mouseTrail;

};

#endif // MAGNET_H
