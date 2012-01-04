#include "MouseTrail.h"
#include "../Magnet.h"

#include "TrailCircle.h"

MouseTrail::MouseTrail()
{
    on = true;
}

MouseTrail::~MouseTrail()
{
    //dtor
}

void MouseTrail::MouseMove(sf::Vector2i mouse){
    int numCircles = rand() % 4 + 1;
    int offsetX      = rand() % 5;
    int offsetY      = rand() % 5;
    int size;

    int negX =   rand() % 2 + 1;
    int negY =   rand() % 2 + 1;

    if(negX == 1){
        offsetX = offsetX * -1;
    }

    if(negY == 1){
        offsetY = offsetY * -1;
    }

    for(int i = 0; i < numCircles; i++){
        size = rand()%5+2;

        trail.push_back(new TrailCircle(mouse.x+offsetX, mouse.y+offsetY, size, sf::Color(255, 255, 255)));
        trail.back()->Link();
    }
}

void MouseTrail::Frame(){
   if(!trail.empty()){
        trail_it = trail.begin();

        while(trail_it != trail.end()){
            (*trail_it)->Update();

            if((*trail_it)->ShouldRemove()){
                (*trail_it)->RemoveLink();
                trail_it = trail.erase(trail_it);
            }else{
                trail_it++;
            }
        }
    }
}
