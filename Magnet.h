#ifndef MAGNET_H
#define MAGNET_H

#include <SFML/Graphics.hpp>

#include "Console/Console.h"

#include "Game/EventListener.h"
#include "Game/Handlers/EventHandler.h"

#include "Game/State.h"
#include "Game/Hook.h"

#include "Achievements/Achievements.h"
#include "Game/Renderer.h"
#include "Game/Resource.h"
#include "Game/MouseTrail.h"

#include "World/World.h"

//#include "mgui/mgui.h"

#include "FileActions/FileAction.h"
#include "FileActions/Cfg/CfgInclude.h"

#include "Network/HttpReq.h"
//#include "FileActions/Xml/xml_include.h"

#include "World/WorldManager.h"

#include "FileActions/Cfg/CfgInclude.h"

class Magnet
{
    public:
        virtual ~Magnet();

        static Magnet* Object(std::string from);    ///< DEBUG
        static Magnet* Object();
        static void Init(sf::RenderWindow& window, sf::Thread& renderThread, sf::Thread& loadThread)  throw(Exception);
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
        //static mgui::Registry* Menus();
        //////////////////////////////////////////
        /// Retrieve the global config object
        //////////////////////////////////////////
        static Config* GlobalConfig();

        static void ben_testing_space();//!< space for shit ben needs to test

        static State::_type GetState(){ return Object("GetState")->gameState.get(); }

        //////////////////////////////////////////////
        /// Retrieve the global achievement registry
        //////////////////////////////////////////////
        static Achievements::Registry* Achieves();

        //////////////////////////////////////////
        /// Change the current state of the engine
        //////////////////////////////////////////
        void ChangeState(State::_type newState);

        //////////////////////////////////////////
        /// Returns true if setup hooks are
        /// registered to m_hooks;
        ///
        /// always returns true for now until
        /// hook is updated
        /////////////////////////////////////////
        bool LoadNeeded();

        void Debug_CreateMenu();


        MouseTrail m_mouseTrail;
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
        //mgui::Registry m_menus;
        Achievements::Registry m_acheivs;

        Config m_config;

        bool m_load_started;  //True when a load has been started
        bool m_initialized;     //True when Engine critical classes are initialized

        //////////////////////////////////////////
        /// Called on initialize
        //////////////////////////////////////////
        void State_Initialize();
        //////////////////////////////////////////
        /// Called on setup
        //////////////////////////////////////////
        void State_Setup();
        //////////////////////////////////////////
        /// Called on load
        //////////////////////////////////////////
        void State_Load();
        //////////////////////////////////////////
        /// Called on ready
        //////////////////////////////////////////
        void State_Ready();


};

#endif // MAGNET_H
