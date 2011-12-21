#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SFML/Graphics.hpp>
#include <map>

using std::multimap;
using std::pair;

class EventHandler
{
    public:

        typedef void (*FuncType)(sf::Event);

        //Should be called every frame
        static void Listen();

        /***************
            Add(Type)Listener maps a FuncType to an EventType

            AddListener - Should be used for things like Event::Closed, Event::KeyPressed, etc.
            AddKeyListener - Should be used for key specific keypresses
            AddMouseListener - should be used for specific mouse events
        ******************/
        static void AddEventListener(sf::Event::EventType type, FuncType funcPtr);
        static void AddMouseListener(sf::Mouse::Button type, EventHandler::FuncType funcPtr);
        static void AddKeyListener(sf::Key::Code type, EventHandler::FuncType funcPtr);

        /**************************************
                "Calls all stored evnts of
                    event type `type` "

            \param  type The Event type to be called
        *******************************************/
        void CallEvent(sf::Event::EventType type);
        void CallKeyEvent(sf::Key::Code type);
        void CallMouseEvent(sf::Mouse::Button type);


        static EventHandler* GetObject();

        virtual ~EventHandler();
    protected:
        EventHandler();
    private:
        static EventHandler* EventObject;

        sf::Event Event;
        multimap<sf::Event::EventType, FuncType>            event_listeners;
        multimap<sf::Event::EventType, FuncType>::iterator  event_listeners_iterator;
        multimap<sf::Key::Code, FuncType>                   key_listeners;
        multimap<sf::Key::Code, FuncType>::iterator         key_listeners_iterator;
        multimap<sf::Mouse::Button, FuncType>               mouse_listeners;
        multimap<sf::Mouse::Button, FuncType>::iterator     mouse_listeners_iterator;

};

#endif // EVENTHANDLER_H
