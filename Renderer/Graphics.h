#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <iostream>
#include <math.h>
#include <ctype.h>

#include "Matrix.h"

#define X_AXIS              Vector(1, 0, 0)
#define Y_AXIS              Vector(0, 1, 0)
#define Z_AXIS              Vector(0, 0, 1)
#define IDENTITY_VECTOR     Vector(1, 1, 1)

#define DEFAULT_UP_VECTOR   Y_AXIS          //y-axis is up
#define DEFAULT_ORIGIN      Point(0, 0, 0)
#define PI 3.14159265

typedef float                                  point_t;
typedef float                                  angle_t;

class Vector;
struct Point{
    point_t x;
    point_t y;
    point_t z;

    Point(point_t _x = 0,
          point_t _y = 0,
          point_t _z = 0)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Point operator+(const Point& pt) const{
        Point result;
        result.x = x + pt.x;
        result.y = y + pt.y;
        result.z = z + pt.z;

        return result;
    }

    Point operator+(const Vector& vect) const;
};


//Should be moved to Renderer

struct Angle {

    static angle_t RadToDegree(const angle_t& rad){
        return (rad * (180.0f/PI));
    }

    static angle_t DegreeToRad(const angle_t& deg){
        return (deg * (PI/180.0f));
    }

    Angle( angle_t _angle = 0, std::string _type = "degree" ){
        std::cout << "Constructing angle " << _angle << " of type " << _type << " \n";
        m_angle = _angle; //Stored internally as radians

        for(int i = 0; i < _type.size(); i++){
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
        m_angle = cpy.m_angle;
    }

    Angle& toRadians(){
        if(type == DEGREE){
            m_angle   = DegreeToRad(m_angle);
            type = RADIAN;
        }
        return *this;
    }

    Angle& toDegrees(){
        if(type == RADIAN){
            m_angle   = RadToDegree(m_angle);
            type = DEGREE;
        }

        return *this;
    }

    angle_t degrees() const{
        if(type == DEGREE){
            return m_angle;
        }else{
            return RadToDegree(m_angle);
        }
    }

    angle_t radians() const{
        if(type == RADIAN){
            return m_angle;
        }else{
            return DegreeToRad(m_angle);
        }
    }

    private:
        enum {
            DEGREE,
            RADIAN
        } type;

        angle_t m_angle;
};

class Vector{
    point_t m_x;
    point_t m_y;
    point_t m_z;
    Point   m_origin;   //Indicates

    public:

        Vector(point_t _x=0, point_t _y=0, point_t _z=0, Point origin = Point()); //Default, Construct from three point_t x, y, and z
        Vector(const Point& pt, Point origin = Point());                          //Construct from a point
        Vector(const Vector& oldvect);


        point_t x()         const;
        point_t y()         const;
        point_t z()         const;
        float   length()    const;
        void    normalize();

        //
        /// Get the normal between two vectors
        //
        static Vector GetNormal(const Vector& x, const Vector& y){
            float nx = (x.m_y * y.m_z) - (x.m_z * y.m_y);
            float ny = (x.m_z * y.m_x) - (x.m_x * y.m_z);
            float nz = (x.m_x * y.m_y) - (x.m_y * y.m_x);

            Vector norm(nx, ny, nz);
            norm.normalize();

            return norm;
        }

        static Angle GetAngle(const Vector& up, const Vector& rotation){
            angle_t det = static_cast<angle_t>(up * rotation) / (up.length() * rotation.length());
            double  angle = acos(det);

            Angle ret = Angle(static_cast<angle_t>(angle), "radians");

            return ret;
        }

        bool isNormal();
        bool isZero();

        ///Override ='s operator
        const Vector& operator=(const Vector& cpy){
            this->m_x = cpy.x();
            this->m_y = cpy.y();
            this->m_z = cpy.z();

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

        void debug_output(){
            std::cout << "Vector (" << x() << ", " << y() << ", " << z() << ") = " << length() << "\n";
        }
};



struct TransformMatrix {
    point_t trans_matrix[4][4];
    point_t point[4];

    TransformMatrix( const Point& pt, const Vector& translation, const Vector& dtranslation ) {
        point[0] = pt.x;
        point[1] = pt.y;
        point[2] = pt.z;
        point[3] = 1; //w = 0 to indicate vector

        trans_matrix[0][0] = translation.x();
        trans_matrix[0][1] = 0;
        trans_matrix[0][2] = 0;
        trans_matrix[0][3] = dtranslation.x();

        trans_matrix[1][0] = translation.y();
        trans_matrix[1][1] = 0;
        trans_matrix[1][2] = 0;
        trans_matrix[1][3] = dtranslation.y();

        trans_matrix[2][0] = translation.z();
        trans_matrix[2][1] = 0;
        trans_matrix[2][2] = 0;
        trans_matrix[2][3] = dtranslation.z();

        trans_matrix[3][0] = 0;
        trans_matrix[3][1] = 0;
        trans_matrix[3][2] = 0;
        trans_matrix[3][3] = 1; //w = 0 to indicate vector
    }

    Point result(){
        point_t x, y, z;

        x =     (trans_matrix[0][0] * point[0])
            +   (trans_matrix[0][1] * point[1])
            +   (trans_matrix[0][2] * point[2])
            +   (trans_matrix[0][3] * point[3]);

        y =     (trans_matrix[1][0] * point[0])
            +   (trans_matrix[1][1] * point[1])
            +   (trans_matrix[1][2] * point[2])
            +   (trans_matrix[1][3] * point[3]);

        z =     (trans_matrix[2][0] * point[0])
            +   (trans_matrix[2][1] * point[1])
            +   (trans_matrix[2][2] * point[2])
            +   (trans_matrix[2][3] * point[3]);

        return Point(x, y, z);

    }
};

class RenderObject
{
    Point   m_origin;
    Vector  m_position; //The Vector from the origin to where the object should be
    Vector  m_up;       //The direction the object is facing upon creation.
    Vector  m_rotation; //Angle from up


    public:
        typedef unsigned int                               uint_t;   //Should be based on a 32/64 define

        //x=rows, y=cols
        ///If only xsize is specified, a square matrix will be made of xsize rows and cols
        ///If both xsize and ysize are spcified, a matrix of that size will be made
        RenderObject( Vector position = Vector(), Vector rotation = Vector(), Vector up = DEFAULT_UP_VECTOR, Point origin = DEFAULT_ORIGIN );
        //virtual ~RenderObject();

        Point       position() const;
        Vector      up() const;
        Vector      rotation() const;
        Angle       angle() const;

        Vector      rotate(const Angle& rotation, const Vector& direction = Z_AXIS);
};

#endif // GRAPHICS_H
