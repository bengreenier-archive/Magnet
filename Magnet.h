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

#include "Renderer.h"

#include "Console/Console.h"
#include "Achievements/Achievements.h"
#include "World/World.h"

//Should change Game to Engine...
#include "Game/EventListener.h"
#include "Game/EventHandler.h"
#include "Game/Resource.h"
#include "Game/Exception.h"

//#include "mgui/mgui.h"

#include "FileActions/FileAction.h"
#include "Config/ConfigInclude.h"
#include "Utility/Functor.h"
#include "Network/HttpReq.h"

//#include "Sandbox.h"

//Memory management
#include "Memory/Serial.h"

#define mENGINE_REGISTER_SHOOK(hook_name, hook_enum, func_pointer)      Magnet::Hooks()->registerHook(new Hook(hook_name, hook_enum, func_pointer));    //Static hook (a hook that points to a static/free function)
#define mENGINE_REGISTER_IHOOK(hook_name, hook_enum, func_pointer, ob)  Magnet::Hooks()->registerHook(new Hook(hook_name, hook_enum, func_pointer, ob));      //Instance hook (a hook that points to a member function)

////////////////////////////////////////////////////////////
    //This class manages the state of the enginge, and the
    // initialization of singleton classes.
////////////////////////////////////////////////////////////
class Magnet
{
    public:
        virtual ~Magnet();

        static Magnet* Object();
        static void Init(size_t& _serial_entity_size, sf::Window& window, sf::Thread& loadThread)  throw(util::Exception);
        static bool IsInitialized(); //Check to see if we have initialized yet

        static void Hook_Initialize();
        static void Hook_Setup();

        static bool event_keyPressed(sf::Event evt);

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
        static HookRegistry* Hooks(std::string from); ///< DEBUG
        static HookRegistry* Hooks() { return &Object()->m_hooks; }
        //////////////////////////////////////////
        /// Retrieve the global menu registry
        //////////////////////////////////////////
        //static mgui::Registry* Menus();
        //////////////////////////////////////////
        /// Retrieve the global config object
        //////////////////////////////////////////
        //static Config* GlobalConfig();

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
        Magnet(size_t _serial_entity_size, sf::Window& window, sf::Thread& loadThread, State::_type defaultState);
    private:
        typedef std::vector<EventListener*>     eventlistener_vector_t;

        eventlistener_vector_t m_eventlistener_vect;

        static Magnet* magnet_ptr;
        State gameState;

        sf::Thread* m_renderThread_ptr;
        sf::Thread* m_loadThread_ptr;
        sf::Window* m_renderWindow;
        Renderer*   m_renderer;

        sf::Mutex m_globalMutex;

        sf::Clock* dbg_timer;

        //Registries
        HookRegistry m_hooks;
        //mgui::Registry m_menus;
        //Achievements::Registry m_acheivs;

      //  Config m_config;
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
        void State_Entry();

        void dbg_deleteTimer();
        void dbg_resetTimer(std::string msg);


};

#endif // MAGNET_H
