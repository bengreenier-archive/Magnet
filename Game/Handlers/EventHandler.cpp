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
    event_queue_t& queue = Object()->m_event_queue;
    listener_map_pair_t ptr_range;
    sf::Event nextEvent;

    while (Renderer::GetRenderWindow()->GetEvent(nextEvent))
    {
        queue.push(nextEvent);
    }

    while(!queue.empty()){
        Object()->doCallEvent(queue.front(), Object()->m_listener_map.equal_range(queue.front().Type));
        queue.pop();
    }
}

void EventHandler::AddListener(AbstractListener* listener_ptr){
    EventHandler* EventHandler = Object();

    EventHandler->m_listener_map.insert(std::pair<sf::Event::EventType, AbstractListener*>(listener_ptr->eventType, listener_ptr));
}

void EventHandler::doCallEvent(sf::Event& evt, listener_map_pair_t lrange){
    listener_map_it itr;

    for(itr = lrange.first; itr != lrange.second; itr++ )
        itr->second->onEvent(evt);

}
EventHandler* EventHandler::Object(){
    if(EventObject == NULL)
        EventObject = new EventHandler();

    return EventObject;
}
