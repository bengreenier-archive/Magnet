#include "Magnet.h"
#include "Renderer.h"

//Static memebetrs
Magnet*         Magnet::magnet_ptr           =   NULL;

Magnet::Magnet(State::_type defaultState) : gameState(defaultState)
{
    Hooks()->Register(Hook::Frame, &Magnet::Frame);
}

Magnet::~Magnet()
{
    //dtor
}

sf::Mutex* Magnet::GlobalMutex(){
    return &Object()->m_globalMutex;
}

Hook::Registry* Magnet::Hooks(){
    return &Object()->m_hooks;
}

Magnet* Magnet::Object(){
    if(magnet_ptr == NULL)
        magnet_ptr = new Magnet(State::NullPointer);

    return magnet_ptr;
}

void Magnet::Frame(){
    //Should be called every frame
}
