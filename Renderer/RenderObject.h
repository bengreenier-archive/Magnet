#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include <gl/glew.h>

#include <vector>

class RenderObject
{
//
/// Private type definitions
typedef std::vector<const Point*> vertices_t;

//
///Member variables
Point       m_position; //The Vector from the origin to where the object should be
Vector      m_rotation; //Vector from up that indicates rotation
vertices_t  m_vertexBuffer; //A collection of points
GLenum      m_shape_type;



public:

//
/// Public type definitions
typedef unsigned int                               uint_t;   //Should be based on a 32/64 define

//
///Public member functions
//x=rows, y=cols
//If only xsize is specified, a square matrix will be made of xsize rows and cols
//If both xsize and ysize are spcified, a matrix of that size will be made
RenderObject( Point position = Point(), Vector rotation = Vector() );
//virtual ~RenderObject();
Vector      rotate(const Angle& rotation, const Vector& direction = Z_AXIS);

//
///Public setters
void        addPoint    ( Point* newpt );
void        removePoint ( const Point& newpt );
void        shape_type(GLenum shape) { m_shape_type = shape; }

//
///Public getters
GLenum            shape_type() const { return m_shape_type; }
unsigned int      points() const { return m_vertexBuffer.size(); }
const Point&      getPoint(unsigned int pindex) const;
const Point&      position() const;
void              setPosition(Point newpt);
Vector      rotation() const;
//Angle     angle() const;
};

#endif //RENDEROBJECT_H
