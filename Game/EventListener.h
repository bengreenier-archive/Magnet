#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Listener/AbstractListener.h"

class EventListener : public AbstractListener
{
    public:
        EventListener(sf::Event::EventType event, callback_type callback);
        virtual ~EventListener();
        virtual bool onEvent(sf::Event evt);
};

#endif // EVENTLISTENER_H
