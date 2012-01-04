#ifndef MOUSETRAIL_H
#define MOUSETRAIL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class TrailCircle;
class MouseTrail
{
    public:
        MouseTrail();
        virtual ~MouseTrail();

        void MouseMove(sf::Vector2i mouse);

        void Frame();

        bool on;
    protected:
    private:
        typedef std::vector<TrailCircle*>            trail_t;
        typedef std::vector<TrailCircle*>::iterator  trail_it_t;
        trail_t     trail;
        trail_it_t  trail_it;
};

#endif // MOUSETRAIL_H
