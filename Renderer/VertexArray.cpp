#include "Graphics.h"

VertexArray::VertexArray(const vertexarr_size_t& size, const Point* values)
:   m_size(size),
    m_vertices(new Point[size])
{
    if(values != 0){
        for(vertexarr_size_t i = 0; i < this->size(); i++)
        {
            m_vertices[i] = values[i];
        }
    }else{
        for(vertexarr_size_t i = 0; i < this->size(); i++)
        {
            m_vertices[i] = 0;
        }
    }

}

VertexArray::~VertexArray()
{
    delete [] m_vertices;
}

const Point* VertexArray::pointArray() const
{
    return m_vertices;
}

const vertexarr_size_t& VertexArray::size() const
{
    return m_size;
}


Point& VertexArray::point(vertexarr_size_t i) const throw(util::Exception)
{
    if(indexOutOfBounds(i))
    {
        std::stringstream msg;
        msg << "Index '" << i << "' is out of bounds (" << (size() - 1) << ")";
        throw(util::Exception("index out of bounds", msg.str() ));
    }

    return m_vertices[i];
}

void VertexArray::point(vertexarr_size_t i, const Point& pt) throw(util::Exception)
{
    if(indexOutOfBounds(i))
    {
        std::stringstream msg;
        msg << "Index '" << i << "' is out of bounds (" << (size() - 1) << ")";
        throw(util::Exception("index out of bounds", msg.str() ));
    }

    m_vertices[i] = pt;
}

const unsigned int VertexArray::numPoints() const
{
    return size() * 3;
}
