#ifndef MAGNET_H
#define MAGNET_H

#include <SFML/Graphics.hpp>

#include "Console/Console.h"

#include "Game/EventListener.h"
#include "Game/Handlers/EventHandler.h"

#include "Game/State.h"
#include "Game/Hook.h"


#include "Game/Renderer.h"
#include "Game/Resource.h"
#include "Game/MouseTrail.h"

#include "World/World.h"

#include "mgui/mgui.h"

#include "FileActions/FileAction.h"

#include "Network/HttpReq.h"

class Magnet
{
    public:
        //Garbage collection
        virtual ~Magnet();

        static Magnet* Object(std::string from);    ///< DEBUG
        static Magnet* Object();
        static void Init(sf::RenderWindow& window, sf::Thread& renderThread, sf::Thread& loadThread);
        static bool Initialized(); //Check to see if we have initialized yet
        static void Hook_Initialize();

        static void Think();
        static void Hook_Setup();
        static void CreateSprite();

        //////////////////////////////////////////
        /// Called on space press
        //////////////////////////////////////////
        static bool Event_SpacePressed(sf::Event evt);
        static bool Event_MouseButtonReleased(sf::Event evt);
        static bool Event_MouseMove(sf::Event evt);
        static bool Event_MouseButtonPressed(sf::Event evt);

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
        //////////////////////////////////////////
        /// Retrieve the global menu registry
        //////////////////////////////////////////
        static mgui::Registry* Menus();

        static void ben_testing_space();//!< space for shit ben needs to test

        static State GetState(){ return Object("GetState")->gameState; }


        //////////////////////////////////////////
        /// Change the current state of the game
        //////////////////////////////////////////
        void ChangeState(State::_type newState);

        void Debug_CreateMenu();


        MouseTrail m_mouseTrail;
        mgui::Panel* test;
        const char*  name;

    protected:
        //Magnet initialization stuff
        Magnet(sf::RenderWindow& window, sf::Thread& renderThread, sf::Thread& loadThread, State::_type defaultState);
    private:
        typedef std::vector<EventListener*>     eventlistener_vector_t;

        eventlistener_vector_t m_eventlistener_vect;

        static Magnet* magnet_ptr;
        State gameState;
        sf::Thread* m_renderThread_ptr;
        sf::Thread* m_loadThread_ptr;
        sf::RenderWindow* m_renderWindow;

        sf::Mutex m_globalMutex;

        //Registries
        Hook::Registry m_hooks;
        mgui::Registry m_menus;

        bool m_loadingStarted; //Checks to see if the loading has started yet
        bool m_initialized;


};

#endif // MAGNET_H
