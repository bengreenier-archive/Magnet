/*
#ifndef TRAILCIRCLE_H
#define TRAILCIRCLE_H

#include "../Magnet.h"

class TrailCircle
{
    public:
        sf::Shape m_circle; //Move to private .. ?

        TrailCircle(float x, float y, float radius, const sf::Color color);
        virtual ~TrailCircle();

        ///////////////////////
        /// Called every frame
        ///////////////////////
        void Update();

        ///////////////////////
        /// Link the circle to
        /// THe renderer
        ///////////////////////
        void Link();
        ///////////////////////
        /// Remove the circle from
        /// The renderer
        ///////////////////////
        void RemoveLink();


        ///////////////////////
        /// True when circle a
        /// Animation is done
        ///////////////////////
        bool ShouldRemove(){ return m_remove; }

    protected:
    private:
        float m_shake;  ///< How much to modify the initial x and
        int m_initalX;  ///< The starting X position
        int m_initialY; ///< THe starting Y position
        float m_scale;  ///< Current scale
        bool m_remove;  ///< Default false, true when the circle should be remved from the trail

        bool _m_removed;
};

#endif // TRAILCIRCLE_H

*/
