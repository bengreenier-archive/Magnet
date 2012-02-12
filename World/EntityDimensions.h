#ifndef ENTITYDIMENSIONS_H
#define ENTITYDIMENSIONS_H


class EntityDimensions
{
    public:
        /** Default constructor */
        EntityDimensions(float i_width,float i_height,float i_posx,float i_posy,float i_angle = 0);
        EntityDimensions(float i_radius,float i_posx,float i_posy,float i_angle = 0);
        /** Default destructor */
        ~EntityDimensions();

        float width,height,radius,posx,posy,angle;
    protected:
    private:
};

#endif // ENTITYDIMENSIONS_H
