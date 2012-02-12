#ifndef SHAPEDRAW_H
#define SHAPEDRAW_H


class ShapeDraw
{
    public:
        /** Default constructor */
        ShapeDraw(sf::Drawable shape);
        /** Default destructor */
        ~ShapeDraw();

        Show();
		Hide();

    protected:
    private:
        sf::Drawable* shape;
};

#endif // SHAPEDRAW_H
