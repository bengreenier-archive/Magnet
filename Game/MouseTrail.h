#ifndef MOUSETRAIL_H
#define MOUSETRAIL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

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
        typedef std::vector<std::auto_ptr<sf::Shape> >            trail_t;
        trail_t trail;
};

#endif // MOUSETRAIL_H
