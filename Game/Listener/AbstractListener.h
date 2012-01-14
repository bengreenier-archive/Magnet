#ifndef ABASTRACTLISTENER_H
#define ABASTRACTLISTENER_H

#include "../Callback.h"

class AbstractListener {
    public:
        typedef bool (*callback_func_type)(sf::Event);

        virtual ~AbstractListener() {}
        virtual bool onEvent(sf::Event evt) = 0;

        sf::Event::EventType     eventType;
        callback_func_type      callback;
};

#endif //ABASTRACTLISTENER_H
