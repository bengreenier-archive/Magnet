#ifndef PARAMETER_H
#define PARAMETER_H

#include <SFML/Window.hpp>

class Parameter
{
    public:
        struct EventParam {
            sf::Event data;
        };

        struct HookParam{
            int     inum;
            float   fnum;
            bool    condition;
            void*   void_ptr;
        };

        union{
            EventParam  Event;
            HookParam   Hook;
        };

};

#endif // PARAMETER_H
