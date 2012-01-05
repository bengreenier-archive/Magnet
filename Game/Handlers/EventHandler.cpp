#include "EventHandler.h"
#include "../../Magnet.h"

EventHandler*   EventHandler::EventObject   =   NULL;

EventHandler::EventHandler()
{
    //ctor
}

EventHandler::~EventHandler()
{
    //dtor
}

void EventHandler::Listen(){
    while (Renderer::GetRenderWindow()->GetEvent(GetObject()->Event))
    {
        GetObject()->CallEvent(GetObject()->Event.Type);


        if(GetObject()->Event.Type == sf::Event::KeyPressed){
            GetObject()->CallKeyEvent(GetObject()->Event.Key.Code);
        }

        if(GetObject()->Event.Type == sf::Event::MouseButtonPressed || GetObject()->Event.Type == sf::Event::MouseButtonReleased){
            GetObject()->CallMouseEvent(GetObject()->Event.MouseButton.Button);
        }
    }
}

void EventHandler::AddEventListener(sf::Event::EventType type, EventHandler::FuncType funcPtr){
    GetObject()->event_listeners.insert(pair<sf::Event::EventType, FuncType> (type, funcPtr));
}

void EventHandler::AddKeyListener(sf::Key::Code type, EventHandler::FuncType funcPtr){
    GetObject()->key_listeners.insert(pair<sf::Key::Code, FuncType> (type, funcPtr));
}

void EventHandler::AddMouseListener(sf::Mouse::Button type, EventHandler::FuncType funcPtr){
    GetObject()->mouse_listeners.insert(pair<sf::Mouse::Button, FuncType> (type, funcPtr));
}

void EventHandler::CallEvent(sf::Event::EventType type){
    pair<multimap<sf::Event::EventType, FuncType>::iterator, multimap<sf::Event::EventType, FuncType>::iterator > ptr_range;
    ptr_range = event_listeners.equal_range(type);

    for(event_listeners_iterator = ptr_range.first;
        event_listeners_iterator != ptr_range.second;
        event_listeners_iterator++ )
    {
        event_listeners_iterator->second(Event);
    }
}

void EventHandler::CallKeyEvent(sf::Key::Code type){
    pair<multimap<sf::Key::Code, FuncType>::iterator, multimap<sf::Key::Code, FuncType>::iterator > ptr_range;
    ptr_range = key_listeners.equal_range(type);

    for(key_listeners_iterator = ptr_range.first;
        key_listeners_iterator != ptr_range.second;
        key_listeners_iterator++ )
    {
        key_listeners_iterator->second(Event);
    }
}

void EventHandler::CallMouseEvent(sf::Mouse::Button type){
    pair<multimap<sf::Mouse::Button, FuncType>::iterator, multimap<sf::Mouse::Button, FuncType>::iterator > ptr_range;
    ptr_range = mouse_listeners.equal_range(type);

    for(mouse_listeners_iterator = ptr_range.first;
        mouse_listeners_iterator != ptr_range.second;
        mouse_listeners_iterator++ )
    {
        mouse_listeners_iterator->second(Event);
    }
}

EventHandler* EventHandler::GetObject(){
    if(EventObject == NULL)
        EventObject = new EventHandler();

    return EventObject;
}
