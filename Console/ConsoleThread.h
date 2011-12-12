#ifndef CONSOLETHREAD_H
#define CONSOLETHREAD_H

#include <string>
#include <iostream>

class ConsoleThread
{
    public:
        ConsoleThread();
        ~ConsoleThread();
        void TellAJoke();//This is our demo function.
        std::string listenerToExecutor;
    protected:
    private:
};

#endif // CONSOLETHREAD_H
