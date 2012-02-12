#ifndef SHAPEDRAW_H
#define SHAPEDRAW_H

#include <SFML/Graphics.hpp>

//because we need to renderer stuff in here.
#include "../Game/Renderer.h"

class ShapeDraw
{
    public:
        /** Default constructor */
        ShapeDraw(sf::Drawable* shape);
        /** Default destructor */
        ~ShapeDraw();

        void Show();
		void Hide();

    protected:
    private:
        sf::Drawable* m_shape;
        bool showing;
        Renderer::Link* m_link;
};

#endif // SHAPEDRAW_H
