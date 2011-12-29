#include "ManagedThread.h"


ManagedThread::ManagedThread(FuncType func, void* data)
    :   m_func(func),
        m_data(data)
{
}

void ManagedThread::Wait(){
    sf::Thread::Wait();

    m_isRunning = false;
}
void ManagedThread::Terminate(){
    sf::Thread::Terminate();

    m_isRunning = false;
}
void ManagedThread::Launch(){
    m_isRunning = true;
    sf::Thread::Launch();
}

void ManagedThread::Run(){
    std::cout << "Calling threaded function\n";
    m_func(m_data);

    m_isRunning = false;
}

