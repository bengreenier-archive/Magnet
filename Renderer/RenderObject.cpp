#include "RenderObject.h"

RenderObject::RenderObject( VertexArray* vertices, Point position, Vector rotation ){
    m_vertices  = vertices;
    m_position  = position;
    m_rotation  = rotation;

    m_rotation.normalize();

    m_shape_type = GL_LINE_LOOP;
}

RenderObject::~RenderObject()
{
    delete m_vertices;
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



void RenderObject::draw() const
{
    glTranslatef(0.0f, 0.0f, -5.0f);
    glTranslatef(position().x(), position().y(), position().z());

    glRotatef(rotation().x(), 1, 0, 0);
    glRotatef(rotation().y(), 0, 1, 0);
    glRotatef(rotation().z(), 0, 0, 1);

    glBegin(shape_type());
        /*for(int j = 0; j < points(); j++){
            const Point& pt = getPoint(j);

            glColor3f( ((float)(rand()%100))/100
                      ,((float)(rand()%100))/100
                      ,((float)(rand()%100))/100 );
            //glVertex3f(pt.x(), pt.y(), pt.z());
        }*/
        glColor3f( ((float)(rand()%100))/100
                  ,((float)(rand()%100))/100
                  ,((float)(rand()%100))/100 );

        glVertexPointer(3, GL_FLOAT, 0, m_vertices);
    glEnd();

    glDrawArrays(shape_type(), 0, m_vertices->numPoints()); //Change to draw elements, use index mapping in vertex array class
}
