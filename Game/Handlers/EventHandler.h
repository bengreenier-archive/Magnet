#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SFML/Window.hpp>
#include <map>
#include <queue>
#include "../EventListener.h"

#include <iostream>
class EventHandler
{
    public:

        //Should be called every frame
        static void Listen(sf::Window& Window);

////////////////////////////////////////////////////////////////////////////////////////////
        ///    Function:        static void AddListener()

////////////////////////////////////////////////////////////////////////////////////////////
        static void AddListener(EventListener* listener);

        void CallEvent(sf::Event::EventType event_type, ...);


        static EventHandler* Object();

        virtual ~EventHandler();
    protected:
        EventHandler();
    private:
        static EventHandler* EventObject;

        sf::Event Event;
        typedef std::multimap<sf::Event::EventType, EventListener*>
listener_map_t;
        typedef std::pair<sf::Event::EventType, EventListener*>
listener_pair_t;
        typedef std::multimap<sf::Event::EventType,
EventListener*>::iterator    listener_map_it;
        typedef std::pair<listener_map_it, listener_map_it>
listener_map_pair_t;
        typedef std::queue<sf::Event>
event_queue_t;

        listener_map_t  m_listener_map;
        event_queue_t   m_event_queue;


////////////////////////////////////////////////////////////////////////////////////////////
        ///   Call all events within a range of listeners

////////////////////////////////////////////////////////////////////////////////////////////
        void doCallEvent(sf::Event& evt, listener_map_pair_t lrange);


        /*
        multimap<sf::Event::EventType, FuncType>
event_listeners;
        multimap<sf::Event::EventType, FuncType>::iterator
event_listeners_iterator;
        multimap<sf::Key::Code, FuncType>
key_listeners;
        multimap<sf::Key::Code, FuncType>::iterator
key_listeners_iterator;
        multimap<sf::Mouse::Button, FuncType>
mouse_listeners;
        multimap<sf::Mouse::Button, FuncType>::iterator
mouse_listeners_iterator;
        */
};

#endif // EVENTHANDLER_H
