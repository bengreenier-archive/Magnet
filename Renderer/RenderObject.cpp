#include "Graphics.h"

RenderObject::RenderObject( Vector position, Vector rotation, Vector up ){
    m_position  = position;
    m_rotation  = rotation;
    m_up        = up;
    m_origin    = DEFAULT_ORIGIN;

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
    point_t x = (m_rotation.x() * cos(rotation)) - (m_rotation.y() * sin(rotation));
    point_t y = (m_rotation.y() * cos(rotation)) - (m_rotation.y() * sin(rotation));

    if(axis.x() && !(axis.y() || axis.z())){

    }

    //Vector new_rotation;

}
