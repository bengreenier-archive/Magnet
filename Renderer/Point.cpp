#include "Graphics.h"


Point::Point( point_t x,
              point_t y,
              point_t z)
            : POINT_MATRIX(4, 1, 0)
{
    set(x, 0, 0);
    set(y, 1, 0);
    set(z, 2, 0);
    set(1, 3, 0);
}

Point::Point( const POINT_MATRIX& matrix )
              : Matrix<point_t>(matrix)
{
    if(isCorrupt()){
        throw(0);
    }
}

inline bool Point::isCorrupt() const
{
    return ( w() != 1.f ) ? true : false;
}

Point Point::operator+(const Point& a) const{
    Point result = POINT_MATRIX::operator+(a);

    if(result.isCorrupt()){
        std::cout << "result is corrupt\n";
        result = a;
    }

    return result;
}

Point Point::operator-(const Point& a) const{
    Point result = POINT_MATRIX::operator-(a);

    if(result.isCorrupt()){
        std::cout << "result is corrupt\n";
        result = a;
    }

    return result;
}

Point Point::operator*(const Point& a) const{
    throw(1); //cannot multiply 4x1 * 4x1
}

Point& Point::operator=(const Point& cpy){
    if(!isCorrupt()){
        set(cpy.x(), 0, 0);
        set(cpy.y(), 1, 0);
        set(cpy.z(), 2, 0);
    }

    return *this;
}

inline void Point::debug_output() const
{
    std::cout << "p{ " << x() << ", " << y() << ", " << z() << ", " << w() << " }";

    if(isCorrupt()){
        std::cout << " WARNING: Point is corrupt!";
    }

    std::cout << std::endl;
}
