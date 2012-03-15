#include "Graphics.h"

Point Point::operator+(const Vector& vect) const{
    Point result;
    result.x = x + vect.x();
    result.y = y + vect.y();
    result.z = z + vect.z();

    return result;
}
