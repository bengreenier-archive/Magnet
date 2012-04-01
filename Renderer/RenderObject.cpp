#include "RenderObject.h"

RenderObject::RenderObject( Point position, Vector rotation ){
    m_position  = position;
    m_rotation  = rotation;

    m_rotation.normalize();

    m_shape_type = GL_QUADS;
}

const Point& RenderObject::position() const{
    return m_position;
}

const Vector& RenderObject::rotation() const{
    return m_rotation;
}

/*
Angle RenderObject::angle()const{
    return Vector::GetAngle(up(), rotation());
}
*/

void RenderObject::rotate(const Vector& rotation){
    m_rotation = m_rotation + rotation;
}


void RenderObject::rotate(const Angle& rotation, const Vector& axis)
{

    Vector rotation_vect = axis * Vector(rotation.degrees(), rotation.degrees(), rotation.degrees()); //Get a rotation vector with rotaton on the specified axis
    rotate(rotation_vect);
}


void RenderObject::rotate(const angle_t& rotation, const Vector& axis){
    Angle ang(rotation);
    rotate(ang, axis);
}

void RenderObject::addPoint( Point* newpt ){
    m_vertexBuffer.push_back(newpt);
}

const Point& RenderObject::getPoint(unsigned int pindex) const{
    if(pindex < m_vertexBuffer.size())
    {
        return *m_vertexBuffer[pindex];
    }
}


void RenderObject::setPosition(Point newpt){
    m_position = newpt;
}
