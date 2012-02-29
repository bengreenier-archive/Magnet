#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "BaseListener.h"

class EventListener : public BaseListener
{
    public:
        typedef bool(*callback_type)(sf::Event evt);

        EventListener(sf::Event::EventType event, callback_type callback);
        virtual ~EventListener();

        virtual bool onHear(sf::Event& evt);


        sf::Event::EventType eventType;
    protected:
        virtual bool executeCallback(param_list_t params);
    private:
        callback_type m_callback;
};

#endif // EVENTLISTENER_H
