#ifndef PARAMETER_H
#define PARAMETER_H


class Parameter
{
    public:
        struct EventParam {
            sf::Event data;
        };

        union{
            EventParam  Event;
        };

};

#endif // PARAMETER_H
