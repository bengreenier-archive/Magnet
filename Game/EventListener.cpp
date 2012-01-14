#include "EventListener.h"

EventListener::EventListener(sf::Event::EventType evtType, callback_type cb)
{
    callback = cb;
    eventType = evtType;
}

EventListener::~EventListener()
{
    //dtor
}

bool EventListener::onEvent(sf::Event evt){
    std::cout << "Event called\n";
    return callback(evt);

    return true;
}
