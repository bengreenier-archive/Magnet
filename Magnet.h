#ifndef MAGNET_H
#define MAGNET_H

#include <SFML/Graphics.hpp>

#include "Game/State.h"
#include "Game/Hook.h"

#include <vector>
#include <string>

class Magnet
{
    public:
        struct managed_thread{
            sf::Thread*     threadPtr;
            std::string     name;
            bool            isRunning;
            bool            runAlways;
            bool            lockOnRun;      //When true, the mutex is locked when the thread runs, and is unlocked when the thread terminates.
                                            //      runAlways must be falst for this to be true
            Hook::Type      onHook;
            bool            gameThread;     //When true, this thread is required to be running for Magnet::isRunning to return true
        };

        //Garbage collection
        virtual ~Magnet();

        static Magnet* Object();

        // Threads
        static sf::Thread* renderThread_ptr;
        static sf::Thread* thinkThread_ptr;

        static void Think();

        /******************************
            These functions add a managed thread.

            Managed threads are threads that can be accessed
            anywhere through this class.

            They are also launched and terminated through this class
            so threads can be created and managed easily without much thought.

            \param  accessName:      A string used to access the thread later on
            \param  threadToManage:  The thread we want to manage
            \param  shouldRunAlways: Sets managed_thread.runAlways  (Default: false)
            \param  lock:            Sets managed_thread.lockOnRun  (Default: false)
            \param  isGameThread:    Sets managed_thread.gameThread (Default: false)
            
            uhm, dude...remind me to show you optional arguments. you will redo this with them, i beleive
        *******************************/
        static void AddManagedThread(std::string accessName, sf::Thread& threadToManage);
        static void AddManagedThread(std::string accessName, sf::Thread& threadToManage, bool shouldRunAlways);
        static void AddManagedThread(std::string accessName, sf::Thread& threadToManage, bool shouldRunAlways, bool lock);
        static void AddManagedThread(std::string accessName, sf::Thread& threadToManage, bool shouldRunAlways, bool lock, bool isGameThread);
        static void AddManagedThread(std::string accessName, sf::Thread& threadToManage, bool shouldRunAlways, bool lock, bool isGameThread, Hook::Type callHook);

        static managed_thread* GetManagedThread(std::string find);

        /**************
            Returns true if the Magnet has been initialized
        **************/
        static bool IsRunning();


        static void Frame();
    protected:
        //Magnet initialization stuff
        Magnet(State::_type defaultState);
    private:
        typedef std::vector<managed_thread>            threads_t;
        typedef std::vector<managed_thread>::iterator  threads_iterator_t;

        static Magnet* magnet_ptr;
        State gameState;

        sf::Mutex threadMutex;
        threads_t threads;


};

#endif // MAGNET_H
