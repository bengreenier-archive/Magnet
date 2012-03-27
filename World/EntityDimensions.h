#ifndef ENTITYDIMENSIONS_H
#define ENTITYDIMENSIONS_H

#include <string>

class EntityDimensions
{
    public:
        /** Default constructor */
        EntityDimensions(std::string rect,float i_width,float i_height,float i_posx,float i_posy,float i_angle = 0);
        EntityDimensions(float i_radius,float i_posx,float i_posy,float i_angle = 0);
        EntityDimensions(std::string rect,int i_width,int i_height,int i_posx,int i_posy,int i_angle=0);
        EntityDimensions(int i_radius,int i_posx,int i_posy,int i_angle=0);
        /** Default destructor */
        ~EntityDimensions();

        float width,height,radius,posx,posy,angle;
    protected:
    private:
};

#endif // ENTITYDIMENSIONS_H
