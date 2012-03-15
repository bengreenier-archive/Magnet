#include "Graphics.h"

RenderObject::RenderObject( Vector position, Vector rotation, Vector up, Point origin ){
    m_position  = position;
    m_rotation  = rotation;
    m_up        = up;
    m_origin    = origin;

    m_rotation.normalize();
    m_up.normalize();
}

Point RenderObject::position() const{
    return m_origin + m_position;
}

Vector RenderObject::up() const{
    return m_up;
}

Vector RenderObject::rotation() const{
    return m_rotation;
}

Angle RenderObject::angle()const{
    return Vector::GetAngle(up(), rotation());
}

Vector RenderObject::rotate(const Angle& rotation, const Vector& axis){
    point_t x = 0;
    point_t y = 0;
    point_t z = 0;

    if(axis.x()){

    }

    if(axis.x()){

    }

    if(axis.z()){
        x += (m_rotation.x() * cos(rotation.radians())) - (m_rotation.y() * sin(rotation.radians()));
        y += (m_rotation.x() * sin(rotation.radians())) + (m_rotation.y() * cos(rotation.radians()));
        //z += 0.f;
    }

    m_rotation = m_rotation + Vector(x, y, z);
    //m_rotation.normalize();
    m_rotation.debug_output();
}
