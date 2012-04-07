#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <set>
#include <sstream>
#include <math.h>
#include <ctype.h>
#include <gl/glew.h>

#include "Matrix.h"
#include "../Utility/Exception.h"
#include "../Pipeline.h"

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

typedef GLfloat                                    point_t;
typedef unsigned char                              color_t; //RGBa value between 0-255

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
static  point_t   DotProduct(const Vector& a, const Vector& b);   //Get the dot product between two vectors

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
            set(cpy.x(), 0 );
            set(cpy.y(), 1 );
            set(cpy.z(), 2 );
        }

        return *this;
    }

    Vector operator*(const Vector& cpy) const{
        Vector dot((cpy.x()*this->x()), (cpy.y()*this->y()), (cpy.z()*this->z()));
        return dot;
    }

    Vector operator+(const Vector& add) const{
        Vector nvect(x() + add.x(), y() + add.y(), z() + add.z());
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

    angle_t  m_rot;


    public:

    static angle_t RadToDegree(const angle_t& rot);
    static angle_t DegreeToRad(const angle_t& rot);
    Angle( angle_t rotation, std::string _type = "degree" );

    Angle( const Angle& cpy );
    Angle& toRadians();
    Angle& toDegrees();
    angle_t degrees() const;
    angle_t radians() const;

#ifdef DEBUG_COMPILE
    void debug_output() const{
        std::cout << degrees() << " degrees\n";
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

typedef unsigned int vertexarr_size_t;

class VertexArray
{
    public:
        VertexArray(const vertexarr_size_t& size, const Point* values = 0);
        virtual ~VertexArray();

        const Point* pointArray() const;
        const vertexarr_size_t& size() const;
        const unsigned int numPoints() const;

        Point&  point(vertexarr_size_t i) const throw(util::Exception);
        void    point(vertexarr_size_t i, const Point& pt) throw(util::Exception);

        const point_t& operator[](vertexarr_size_t raw_index)
        {
            vertexarr_size_t pt_index = raw_index / 3;
            unsigned char    coord_id = raw_index % 3;

            if( indexOutOfBounds( pt_index ) )
            {
                dbgconsole << "WARNING: Index '" << (int)raw_index << "' is out of bounds [" << ( (int)(size() * 3) - 1 ) << "]\n";
                return 0; //Index out of bounds
            }

            point_t pt;

            if(coord_id == 0){
                pt = m_vertices[pt_index].x();
            }else if(coord_id == 1){
                pt = m_vertices[pt_index].y();
            }else if(coord_id == 2){
                pt = m_vertices[pt_index].z();
            }

            std::cout << "opengl is getting " << pt << std::endl;
            return pt;
        }

        inline
        bool indexOutOfBounds(vertexarr_size_t i) const
        {
            return ( i > (size() - 1) );
        }
    protected:
    private:
        const vertexarr_size_t  m_size;
        Point*                  m_vertices;


};

#endif // GRAPHICS_H
