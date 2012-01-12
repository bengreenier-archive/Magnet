#ifndef MAGNET_H
#define MAGNET_H

#include <SFML/Graphics.hpp>

#include "Console/Console.h"

#include "Game/Handlers/EventHandler.h"

#include "Game/State.h"
#include "Game/Hook.h"


#include "Game/Renderer.h"
#include "Game/Resource.h"
#include "Game/MouseTrail.h"

#include "World/World.h"

#include "World/World.h"

#include "FileActions/FileAction.h"

class Magnet
{
    public:

    sf::Sprite spr;
        //Garbage collection
        virtual ~Magnet();

        static Magnet* Object(std::string from);    ///< DEBUG
        static Magnet* Object();
        static void Init(sf::Thread& renderThread, sf::Thread& loadThread);
        static bool Initialized(); //Check to see if we have initialized yet
        static void Hook_Initialize();

        static void Frame();
        static void Hook_Setup();
        static void CreateSprite();

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
        static Hook::Registry* Hooks(std::string from); ///< DEBUG
        static Hook::Registry* Hooks();



        static State GetState(){ return Object("GetState")->gameState; }

        //////////////////////////////////////////
        /// Change the current state of the game
        //////////////////////////////////////////
        void ChangeState(State::_type newState);


        MouseTrail m_mouseTrail;
        sf::Sprite m_sprite;

    protected:
        //Magnet initialization stuff
        Magnet(sf::Thread& renderThread, sf::Thread& loadThread, State::_type defaultState);
    private:
        static Magnet* magnet_ptr;
        State gameState;
        sf::Thread* m_renderThread_ptr;
        sf::Thread* m_loadThread_ptr;

        sf::Mutex m_globalMutex;
        Hook::Registry m_hooks;

        bool m_loadingStarted; //Checks to see if the loading has started yet


};

#endif // MAGNET_H
