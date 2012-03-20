#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <set>
#include <iostream>
#include <math.h>
#include <ctype.h>
#include <gl/glew.h>

#include "Matrix.h"

///**ADD: CONDITIONAL CONFIG
#define DEBUG true


#define X_AXIS              Vector(1, 0, 0)
#define Y_AXIS              Vector(0, 1, 0)
#define Z_AXIS              Vector(0, 0, 1)
//#define IDENTITY_VECTOR     Vector(1, 1, 1)

#define UP_VECTOR           Y_AXIS          //y-axis is up
#define DEFAULT_ORIGIN      Point(0, 0, 0)
#define PI 3.14159265

#define POINT_MATRIX          Matrix<point_t>
#define COLOR_MATRIX          Matrix<color_t>

typedef float                                    point_t;
typedef unsigned char                            color_t; //RGBa value between 0-255

class Point;
class Angle;
class Vector : public POINT_MATRIX{

///Private members
point_t m_x;
point_t m_y;
point_t m_z;

///Public members///
public:

//////// Constructors////////
Vector(point_t _x=0, point_t _y=0, point_t _z=0); //Default, Construct from three point_t x, y, and z
Vector(const Point& pt);                          //Construct from a point
Vector(const POINT_MATRIX& pt);
Vector(const Vector& oldvect);

//////// Static Functions ////////
static  Vector   Cross(const Vector& x, const Vector& y);        //Get the cross vector
static  Vector   GetNormal(const Vector& x, const Vector& y);    // Get the normal between two vectors
static  angle_t  GetAngle(const Vector& a, const Vector& b);     //Get the angle between two vectors

//////// Getters /////////
        bool    isNormal()  const;
        bool    isZero()    const;
inline  bool    isCorrupt() const;
        point_t x()         const;
        point_t y()         const;
        point_t z()         const;
        point_t w()         const;
        point_t length()    const;


//////// Setters /////////
        void    normalize();

//////// Overloads ////////
virtual inline void debug_output() const;

    const Vector& operator=(const Vector& cpy){
        if(!cpy.isCorrupt()){
            set(0, 0, cpy.x());
            set(1, 0, cpy.y());
            set(2, 0, cpy.z());
        }

        return *this;
    }

    point_t operator*(const Vector& cpy) const{
        point_t dot = (cpy.x()*this->x()) + (cpy.y()*this->y()) + (cpy.z()*this->z());

        return dot;
    }

    Vector operator+(const Vector& add) const{
        Vector nvect = Vector(x() + add.x(), y() + add.y(), z() + add.z());
        return nvect;
    }
};

class Point : public POINT_MATRIX{
    public:
          static Point CreateRotatedPoint(const Point& orig_pt, Vector axis){
            Point rot_p = POINT_MATRIX::CreateRotationMatrix(axis) * orig_pt; //Get rotated point

            return rot_p;

        }

        Point(point_t x = 0,
              point_t y = 0,
              point_t z = 0);    //Default constructor
        Point(const POINT_MATRIX& matrix); //Construct froma a matrix

        point_t x()const{
            return get(0, 0);
        }

        point_t y()const{
            return get(1, 0);
        }

        point_t z()const{
            return get(2, 0);
        }

        point_t w()const{
            return get(3, 0);
        }

        Point& rotate(const Vector& rot_v){
            *this = POINT_MATRIX::CreateRotationMatrix(rot_v) * (*this);
            return *this;
        }

        inline bool isCorrupt() const;
        virtual inline void debug_output() const;

        Point operator+(const Point& a) const;
        Point operator-(const Point& a) const;
        Point operator*(const Point& a) const;
        Point& operator=(const Point& cpy);

};


//Should be moved to Renderer
//Move to .cpp
class Angle {

    enum {
        DEGREE,
        RADIAN
    } type;

    Vector  m_rot;


    public:

    static angle_t RadToDegree(const Vector& rot){
        return (rot * (180.0f/PI));
    }

    static angle_t DegreeToRad(const Vector& rot){
        return (rot * (PI/180.0f));
    }

    Angle( Vector rotation, std::string _type = "degree" ){
        m_rot   = rotation;

        for(width_t i = 0; i < _type.size(); i++){
            _type[i] = tolower(_type[i]);
        }

        if(_type == "radian"  ||
           _type == "radians" ||
           _type == "rad"     ||
           _type == "rads"      )
        {
            type    = RADIAN;
        }else{
            type    = DEGREE;
        }
    }

    Angle( const Angle& cpy ){
        std::cout << "Copy\n";
        type    = cpy.type;
        m_rot   = cpy.m_rot;
    }

    Angle& toRadians(){
        if(type == DEGREE){
            m_rot   = DegreeToRad(m_rot);
            type = RADIAN;
        }
        return *this;
    }

    Angle& toDegrees(){
        if(type == RADIAN){
            m_rot   = RadToDegree(m_rot);
            type = DEGREE;
        }

        return *this;
    }

    Vector degrees() const{
        if(type == DEGREE){
            return m_rot;
        }else{
            return RadToDegree(m_rot);
        }
    }

    Vector radians() const{
        if(type == RADIAN){
            return m_rot;
        }else{
            return DegreeToRad(m_rot);
        }
    }

#ifdef DEBUG_COMPILE
    void debug_output(){
        std::string measure;
        Vector     angle;

        if( type == RADIAN )
        {
            measure = "radians";
            angle   = radians();

        } else {

            measure = "degrees";
            angle   = radians();

        }

        std::cout << "Angle vector (" << measure << ")\n";
        angle.debug_output();
        std::cout << "X: " << Vector::GetAngle(UP_VECTOR, Vector(angle.x(), 0, 0)) << std::endl;
        std::cout << "Y: " << Vector::GetAngle(UP_VECTOR, Vector(0, angle.y(), 0)) << std::endl;
        std::cout << "Z: " << Vector::GetAngle(UP_VECTOR, Vector(0, 0, angle.z())) << std::endl;
    }
#endif //Debug Compile
};

class Color : public POINT_MATRIX
{
    public:

    //public
    /// Static Functions
    //
    GLfloat GetRatio( color_t norm_color );


    //public
    /// Constructors
    //
    Color(color_t r=255, color_t g=255, color_t b=255, color_t a=255);
    Color(const POINT_MATRIX& m);
    virtual ~Color();



    //public
    /// Getter Functions
    //
    const color_t r() const;
    const color_t g() const;
    const color_t b() const;
    const color_t a() const;

    GLfloat ratio_r();
    GLfloat ratio_g();
    GLfloat ratio_b();
    GLfloat ratio_a();

    //public
    /// Setter Functions
    //
    void r(color_t r);
    void g(color_t g);
    void b(color_t b);
    void a(color_t a);
};

#endif // GRAPHICS_H
