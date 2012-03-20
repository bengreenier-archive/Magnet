#include "Graphics.h"

//public
/// Static Functions
//
GLfloat Color::GetRatio( color_t norm_color )
{
    GLfloat glnorm_color = static_cast<GLfloat>(norm_color);
    std::cout << glnorm_color << std::endl;
    GLfloat rcolor = ( ( glnorm_color * 100.f ) / 255.f ) / 100.f;
    std::cout << rcolor << std::endl;
    return rcolor;
}


//public
/// Constructors
//
Color::Color(color_t _r, color_t _g, color_t _b, color_t _a)
:   POINT_MATRIX(4, 1)
{
    r(_r);
    g(_g);
    b(_b);
    a(_a);
}
Color::Color(const POINT_MATRIX& m)
:   POINT_MATRIX(4, 1)
{
    //new color, row
    r(m.get(0));
    g(m.get(1));
    b(m.get(2));
    a(m.get(3));
}
Color::~Color(){}

//public
/// Getter Functions//
const color_t Color::r() const { return get(0); }
const color_t Color::g() const { return get(1); }
const color_t Color::b() const { return get(2); }
const color_t Color::a() const { return get(3); }

GLfloat Color::ratio_r() { return Color::GetRatio( r() ); }
GLfloat Color::ratio_g() { return Color::GetRatio( g() ); }
GLfloat Color::ratio_b() { return Color::GetRatio( b() ); }
GLfloat Color::ratio_a() { return Color::GetRatio( a() ); }

//public
/// Setter Functions//
void Color::r(color_t r) { set(r, 0); }
void Color::g(color_t g) { set(g, 1); }
void Color::b(color_t b) { set(b, 2); }
void Color::a(color_t a) { set(a, 3); }
