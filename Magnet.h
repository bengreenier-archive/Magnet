#ifndef MAGNET_H
#define MAGNET_H

#include <iostream> //For testing purposes

#ifndef __cplusplus
    #error C++ is required!
#endif

//Set up operating system support
#ifdef __WIN32__
    #define WINDOWS 1
#elif __unix
    //#define UNIX 1
    #error Operating system not supported!
#else
    #error Operating system not supported!
#endif

//Define our api
#ifdef WINDOWS
    #ifdef BUILDING_MAGNET_DLL
        #define MAGNET_API __declspec(dllexport)
    #else
        //#define MAGNET_API __declspec(dllimport)
    #endif
#else
    #error This operating system is not yet supported
#endif

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

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

//#include "FileActions/Xml/xml_include.h" **DELETE THIS

#include "Sandbox.h"

#include "FileActions/Cfg/CfgInclude.h"

//Memory management
#include "Memory/Serial.h"

////////////////////////////////////////////////////////////
    //This class manages the state of the enginge, and the
    // initialization of singleton classes.
////////////////////////////////////////////////////////////
class Magnet
{
    public:
        virtual ~Magnet();

        static Magnet* Object();
        static void Init(size_t _serial_entity_size, sf::RenderWindow& window, sf::Thread& renderThread, sf::Thread& loadThread)  throw(Exception);
        static bool IsInitialized(); //Check to see if we have initialized yet

        static void Hook_Initialize();
        static void Hook_Setup();

        static void Think();

        //////////////////////////////////////////
        /// Called on space press
        //////////////////////////////////////////
        /*
        static bool Event_SpacePressed(sf::Event evt);
        static bool Event_MouseButtonReleased(sf::Event evt);
        static bool Event_MouseMove(sf::Event evt);
        static bool Event_MouseButtonPressed(sf::Event evt);
        */

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

        static State::_type GetState(){ return Object()->gameState.get(); }

        //////////////////////////////////////////////
        /// Retrieve the global achievement registry
        //////////////////////////////////////////////
        //static Achievements::Registry* Achieves();

        //////////////////////////////////////////
        /// Change the current state of the engine
        //////////////////////////////////////////
        void ChangeState(State::_type newState);

    protected:
        Magnet(size_t _serial_entity_size, sf::RenderWindow& window, sf::Thread& renderThread, sf::Thread& loadThread, State::_type defaultState);
    private:
        typedef std::vector<EventListener*>     eventlistener_vector_t;

        eventlistener_vector_t m_eventlistener_vect;

        static Magnet* magnet_ptr;
        State gameState;
        sf::Thread* m_renderThread_ptr;
        sf::Thread* m_loadThread_ptr;
        sf::RenderWindow* m_renderWindow;

        sf::Mutex m_globalMutex;

        sf::Clock* dbg_timer;

        //Registries
        Hook::Registry m_hooks;
        //mgui::Registry m_menus;
        //Achievements::Registry m_acheivs;

        Config m_config;
        bool m_services_initialized;     //True when Engine critical classes are initialized

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

        void dbg_deleteTimer();
        void dbg_resetTimer(std::string msg);


};

#endif // MAGNET_H
