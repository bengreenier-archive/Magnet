#include "Graphics.h"

Vector::Vector(point_t _x, point_t _y, point_t _z, Point origin) //Default, Construct from three point_t x, y, and z
{
    m_x = _x;
    m_y = _y;
    m_z = _z;
    m_origin = origin;
}
Vector::Vector(const Point& pt, Point origin)                          //Construct from a point
{
    m_x = pt.x;
    m_y = pt.y;
    m_z = pt.z;
    m_origin = origin;
}

Vector::Vector(const Vector& oldvect){
    m_x = oldvect.x();
    m_y = oldvect.y();
    m_z = oldvect.z();
}

point_t Vector::x() const{ return m_x; }
point_t Vector::y() const{ return m_y; }
point_t Vector::z() const{ return m_z; }

float   Vector::length() const {
    float x = pow((m_x - m_origin.x), 2);
    float y = pow((m_y - m_origin.y), 2);
    float z = pow((m_z - m_origin.z), 2);
    float sum = x+y+z;

    if(sum < 0 ){
        std::cout << "Sum is negative\n";
        sum *= -1;
    }

    float r = sqrt(sum);

    return r;
}

void    Vector::normalize(){
    while(length() != 1.0f){
        m_x = m_x/length();
        m_y = m_y/length();
        m_z = m_z/length();
    }
}
