#include "EventListener.h"

EventListener::EventListener(sf::Event::EventType evtType, callback_type cb) : BaseListener()
{
    m_callback = cb;
    eventType = evtType;
}

EventListener::~EventListener()
{
    //dtor
}

bool EventListener::onHear(sf::Event& evt){
    Parameter newParam;
    newParam.Event.data = evt;

    return BaseListener::onHear(1, newParam);
}

bool EventListener::executeCallback(param_list_t params){
    m_callback(params[0].Event.data);
}
