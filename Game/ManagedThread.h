#ifndef MANAGEDTHREAD_H
#define MANAGEDTHREAD_H

#include <SFML/System.hpp>
#include <iostream>

/**************
    Class: Managed Thread
**************/

class ManagedThread : public sf::Thread
{
    public:
        enum Length{
            Indefinite, //Type used if the length of the thread is unknown (I.E. runs a while loop)
            Definite    //Type used if the length of the thread is known (I.E. runs a for loop, or procedural code)
        };

        typedef void(* FuncType)(void*);

        ManagedThread(FuncType threadedFunc, void* data);

        void Wait();
        void Terminate();
        void Launch();

        bool IsRunning();
    protected:
    private:
        bool        m_isRunning;
        void*       m_data;
        FuncType    m_func;

        void Run();
};

#endif // MANAGEDTHREAD_H
