#include "TrailCircle.h"
#include "../Renderer.h"
TrailCircle::TrailCircle(float x, float y, float radius, const sf::Color color)
{
    m_circle = sf::Shape::Circle(x, y, radius, color);
    m_shake     =   2;
    m_initalX   =   x;
    m_initialY  =   y;
    m_scale     =   1;
    m_remove    =   false;
    _m_removed  =   false;
}

TrailCircle::~TrailCircle()
{
    Renderer::RemoveLink(&m_circle);
}

void TrailCircle::Link(){
    Renderer::CreateLink(&m_circle);
}

void TrailCircle::RemoveLink(){
    if(_m_removed) return;

    Renderer::RemoveLink(&m_circle);
    _m_removed  =   true;
}

void TrailCircle::Update(){
    m_scale -= .01;

    m_circle.SetScale(m_scale, m_scale);

    if(m_scale < .1){
        m_remove=true;
        //Renderer::RemoveLink(&m_circle);
    }
}
