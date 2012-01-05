#include "TrailCircle.h"
#include "../Magnet.h"
TrailCircle::TrailCircle(float x, float y, float radius, const sf::Color color)
{
    m_circle = sf::Shape::Circle(x, y, radius, color);
    m_shake     =   2;
    m_initalX   =   x;
    m_initialY  =   y;
    m_scale     =   1;
    m_remove    =   false;
}

TrailCircle::~TrailCircle()
{
    Renderer::RemoveLink(&m_circle);
}

void TrailCircle::Link(){
    Renderer::CreateLink(&m_circle);
}

void TrailCircle::RemoveLink(){

    Renderer::RemoveLink(&m_circle);
}

void TrailCircle::Update(){
    m_scale -= .045;

    int neg = rand() % 3 + 1;

    if(neg == 1){
        neg = -1;
    }else if(neg == 2){
        neg = 1;
    }else{
        neg = 0;
    }

    m_circle.SetScale(m_scale, m_scale);
    m_circle.SetPosition((m_initalX-(m_initalX*m_scale))+(m_shake*neg), (m_initialY-(m_initialY*m_scale))+(m_shake*neg));

    if(m_scale < .1){
        m_remove=true;
    }
}
