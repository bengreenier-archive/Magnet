#include "EventListener.h"

EventListener::EventListener(sf::Event::EventType evtType, callback_func_type cb)
{
    callback = cb;
    eventType = evtType;
    //object = NULL;
}

EventListener::EventListener(sf::Event::EventType evtType, callback_func_type cb, void* callob)
{
    callback    =   cb;
    eventType   =   evtType;
    //object      =   callob;

}

EventListener::~EventListener()
{
    //dtor
}

bool EventListener::onEvent(sf::Event evt){
    //if(object == NULL){
        return callback(evt);
    /*}else{
        return ob->callback(evt);
    }*/
}
