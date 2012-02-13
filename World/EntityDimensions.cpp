#include "EntityDimensions.h"

EntityDimensions::EntityDimensions(float i_width,float i_height,float i_posx,float i_posy,float i_angle)
{
    radius = -1;
    width = i_width;
    height = i_height;
    posx = i_posx;
    posy = i_posy;
    angle = i_angle;
}

EntityDimensions::EntityDimensions(int i_width,int i_height,int i_posx,int i_posy,int i_angle)
{
    radius = -1;
    width = i_width;
    height = i_height;
    posx = i_posx;
    posy = i_posy;
    angle = i_angle;
}

EntityDimensions::EntityDimensions(float i_radius,float i_posx,float i_posy,float i_angle)
{
    width = -1;
    height = -1;
    radius = i_radius;
    posx = i_posx;
    posy = i_posy;
    angle = i_angle;
}

EntityDimensions::EntityDimensions(int i_radius,int i_posx,int i_posy,int i_angle)
{
    width = -1;
    height = -1;
    radius = i_radius;
    posx = i_posx;
    posy = i_posy;
    angle = i_angle;
}

EntityDimensions::~EntityDimensions()
{
    //dtor
}
