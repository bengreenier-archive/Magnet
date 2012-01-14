#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SFML/Graphics.hpp>
#include <map>
#include "../EventListener.h"

#include <iostream>

//This class should call only static events
//  Non-statics event callbacks should be
//  excecuted by a static event call back
class EventHandler
{
    public:

        //Should be called every frame
        static void Listen();
        ////////////////////////////////////////////////////////////////////////////////////////////
        ///    Function:        static void AddListener()
        ///    \param name            c string name to map the
        ///    \param listenerptr     a pointer to the lisener
        ////////////////////////////////////////////////////////////////////////////////////////////
        static void AddListener(AbstractListener* listener);
        void CallEvent(sf::Event& newEvent);


        static EventHandler* Object();

        virtual ~EventHandler();
    protected:
        EventHandler();
    private:
        static EventHandler* EventObject;

        sf::Event Event;
        typedef std::multimap<sf::Event::EventType, AbstractListener*>              listener_map_t;
        typedef std::pair<sf::Event::EventType, AbstractListener*>                  listener_pair_t;
        typedef std::multimap<sf::Event::EventType, AbstractListener*>::iterator    listener_map_it;
        typedef std::pair<listener_map_it, listener_map_it>                         listener_map_pair_t;
        typedef std::queue<sf::Event>                                               event_queue_t;

        listener_map_t  m_listener_map;
        event_queue_t   m_event_queue;

        /**************************************
                "Calls all stored evnts of
                    event type `type` "

            \param  type The Event type to be called
        *******************************************/
        void doCallEvent(sf::Event& evt, listener_map_pair_t lrange);


        /*
        multimap<sf::Event::EventType, FuncType>            event_listeners;
        multimap<sf::Event::EventType, FuncType>::iterator  event_listeners_iterator;
        multimap<sf::Key::Code, FuncType>                   key_listeners;
        multimap<sf::Key::Code, FuncType>::iterator         key_listeners_iterator;
        multimap<sf::Mouse::Button, FuncType>               mouse_listeners;
        multimap<sf::Mouse::Button, FuncType>::iterator     mouse_listeners_iterator;
        */
};

#endif // EVENTHANDLER_H
