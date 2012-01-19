#ifndef CONSOLETHREAD_H
#define CONSOLETHREAD_H

#include <string>
#include <iostream>

class ConsoleThread //! passes data to the executor from the listener
{
    public:
        ConsoleThread();
        ~ConsoleThread();
        std::string listenerToExecutor;
    protected:
    private:
};

#endif // CONSOLETHREAD_H
