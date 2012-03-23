/*
#ifndef SHAPEDRAW_H
#define SHAPEDRAW_H

#include <SFML/Graphics.hpp>
#include <iostream>

//because we need to renderer stuff in here.
#include "../Game/Renderer.h"
#include "WorldStandards.h"

class ShapeDraw
{
    public:
        /// Default constructor
        ShapeDraw(sf::Drawable* shape);
        /// Default destructor
        ~ShapeDraw();

        sf::Drawable* Instance;

        void Show();
		void Hide();

    protected:
    private:

        bool showing;
        Renderer::Link* m_link;
};

#endif // SHAPEDRAW_H
*/
