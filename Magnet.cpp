#include "Magnet.h"
#include "Renderer.h"

//Static memebetrs
Magnet*         Magnet::magnet_ptr           =   NULL;

Magnet::Magnet(State::_type defaultState) : gameState(defaultState)
{

}

Magnet::~Magnet()
{
    //dtor
}

Magnet* Magnet::Object(){
    if(magnet_ptr == NULL)
        magnet_ptr = new Magnet(State::NullPointer);

    return magnet_ptr;
}

void Magnet::Frame(){
}

bool Magnet::IsRunning(){
    return false;
}

void Magnet::AddManagedThread(std::string accessName, sf::Thread& threadToManage, bool shouldRunAlways, bool lock, bool isGameThread, Hook::Type callHook){
    managed_thread newManagedThread;
    newManagedThread.name = accessName;
    newManagedThread.threadPtr = &threadToManage;
    newManagedThread.runAlways = shouldRunAlways;
    newManagedThread.gameThread = isGameThread;

    if(!newManagedThread.runAlways && lock){
        newManagedThread.lockOnRun = true;
    }else{
        newManagedThread.lockOnRun = false;
    }

    if(!newManagedThread.runAlways){
        newManagedThread.onHook = callHook;
    }

    std::cout << "Pushing " << newManagedThread.name << std::endl;
    Object()->threads.push_back(newManagedThread);
}
void Magnet::AddManagedThread(std::string accessName, sf::Thread& threadToManage){  Object()->AddManagedThread(accessName, threadToManage, false, false, false, Hook::OnCall); }
void Magnet::AddManagedThread(std::string accessName, sf::Thread& threadToManage, bool shouldRunAlways){  Object()->AddManagedThread(accessName, threadToManage, shouldRunAlways, false, false, Hook::OnCall); }
void Magnet::AddManagedThread(std::string accessName, sf::Thread& threadToManage, bool shouldRunAlways, bool lock){  Object()->AddManagedThread(accessName, threadToManage, shouldRunAlways, lock, false, Hook::OnCall); }
void Magnet::AddManagedThread(std::string accessName, sf::Thread& threadToManage, bool shouldRunAlways, bool lock, bool isGameThread){  Object()->AddManagedThread(accessName, threadToManage, shouldRunAlways, lock, isGameThread, Hook::OnCall); }

Magnet::managed_thread* Magnet::GetManagedThread(std::string find){
    threads_iterator_t it;
    for(it  =   Object()->threads.begin();
        it  !=  Object()->threads.end();
        it++)
    {
        if(it->name == find){
            return &*it;
        }
    }
}

void Magnet::Think(){
    threads_iterator_t it;
    for(it  =   Object()->threads.begin();
        it  !=  Object()->threads.end();
        it++)
    {
        if(!it->isRunning && it->runAlways){
            std::cout << "Starting thread " << it->name << std::endl;
            it->isRunning = true;
            it->threadPtr->Launch();
        }
    }
}
