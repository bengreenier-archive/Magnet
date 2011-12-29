#ifndef MAGNET_H
#define MAGNET_H

#include <SFML/Graphics.hpp>

#include "Game/State.h"
#include "Game/Hook.h"
#include "Game/ManagedThread.h"

class Magnet
{
    public:

        //Garbage collection
        virtual ~Magnet();

        static Magnet* Object();

        static void Frame();

        //////////////////////////////////////////
        /// Retrieve the global mutex
        //////////////////////////////////////////
        static sf::Mutex* GlobalMutex();

        //////////////////////////////////////////
        /// Retrieve the global hook registry
        //////////////////////////////////////////
        static Hook::Registry* Hooks();
    protected:
        //Magnet initialization stuff
        Magnet(State::_type defaultState);
    private:
//        typedef std::vector<managed_thread>            threads_t;
//        typedef std::vector<managed_thread>::iterator  threads_iterator_t;

        static Magnet* magnet_ptr;
        State gameState;
//        threads_t threads;

        sf::Mutex m_globalMutex;
        Hook::Registry m_hooks;

};

#endif // MAGNET_H
