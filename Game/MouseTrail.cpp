#include "MouseTrail.h"
#include "../Magnet.h"

#include "TrailCircle.h"

MouseTrail::MouseTrail()
{
    on = true;
    m_maxSize   =   1;
}

MouseTrail::~MouseTrail()
{
    //dtor
}

void MouseTrail::MouseMove(sf::Vector2i mouse){
    int circles      = rand() % 3 +1 ;
    int offsetX;
    int offsetY;
    int size;

    int negX;
    int negY;

    for(int i=0; i < circles; i++){
        offsetX      = rand() % 4;
        offsetY      = rand() % 4;
        size = rand()%5+2;

        negX =   rand() % 2 + 1;
        negY =   rand() % 2 + 1;

        if(negX == 1){
            offsetX = offsetX * -1;
        }

        if(negY == 1){
            offsetY = offsetY * -1;
        }

        trail.push_back(new TrailCircle(mouse.x+offsetX, mouse.y+offsetY, size, sf::Color(255, 255, 255)));
        trail.back()->Link();
    }
}

void MouseTrail::Frame(){
   if(!trail.empty()){
        if(trail.size() > m_maxSize){
            for(int i = 0; i < (trail.size()-m_maxSize); i++)
                trail.erase(trail.begin());
        }

        trail_it = trail.begin();
        while(trail_it != trail.end()){
            (*trail_it)->Update();

            if((*trail_it)->ShouldRemove()){
                trail_it = trail.erase(trail_it);
            }else{
                trail_it++;
            }
        }
    }
}
