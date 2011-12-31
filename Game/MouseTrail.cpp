#include "MouseTrail.h"
#include "../Magnet.h"

MouseTrail::MouseTrail()
{
    on = false;
}

MouseTrail::~MouseTrail()
{
    //dtor
}

void MouseTrail::MouseMove(sf::Vector2i mouse){
    int numCircles = rand() % 4 + 1;
    int noise      = rand();
    int size;
    for(int i = 0; i < numCircles; i++){
        size = rand()%10+5;
        //trail.push_back(std::auto_ptr<sf::Shape>(new sf::Shape::Circle(mouse.x*noise, mouse.y*noise, size, sf::Color(255, 255, 255))));
    }
}

void MouseTrail::Frame(){
    for(int i =0; i < trail.size(); i++){
        //Renderer::CreateLink(&trail[i]);
    }
}
