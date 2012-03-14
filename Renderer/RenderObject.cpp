#include "Graphics.h"

RenderObject::RenderObject( Vector position, Vector rotation, Vector up ){
    m_position  = position;
    m_rotation  = rotation;
    m_up        = up;

    m_rotation.normalize();
    m_up.normalize();
}

Vector RenderObject::position() const{
    return m_position;
}

Vector RenderObject::up() const{
    return m_up;
}

Vector RenderObject::rotation() const{
    return m_rotation;
}

Angle RenderObject::angle()const{
    Angle ang = Vector::GetAngle(up(), rotation());

    return ang;
}

Vector RenderObject::rotate(const Angle& rotation, const Vector& direction = Z_AXIS){

}
