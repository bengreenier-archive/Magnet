#include "RenderHandler.h"

#include <iostream>

RenderHandler*       RenderHandler::RenderHandlerPtr = NULL;

RenderHandler::RenderHandler()
{
    WindowPtr = new sf::RenderWindow(sf::VideoMode::GetMode(3), "Chess - Adam Zielinski");
    m_isValid = false;
}

//Clean up all the allocated memory space
RenderHandler::~RenderHandler()
{
    delete [] WindowPtr;
    delete [] RenderHandlerPtr;
}


/*********************************************
    "Get the RenderHandler object"

    Returns a pointer to the RenderHandler

    *Uses lazy initialization
*********************************************/
RenderHandler* RenderHandler::GetObject(){
    if(RenderHandlerPtr == NULL){
        RenderHandlerPtr = new RenderHandler();
    }

    return RenderHandlerPtr;
}

/*********************************************
    "Gets a pointer to the current window"

    Returns a pointer to the sf::RenderWindow
*********************************************/
sf::RenderWindow* RenderHandler::Window(){
    return this->WindowPtr;
}

/*********************************************
            "Draw the screen"
*********************************************/
void RenderHandler::Render(){
    RenderHandler* r = RenderHandler::GetObject();

    if(r->isValid()) return;

    std::cout << "Draw " << r->isValid() << "\n";

    r->Window()->Clear(sf::Color(0, 0, 0));

    //Draw contents
    //multimap<int, sf::Drawable>::iterator it;


    r->Window()->Display();

    r->validate();
}

/*********************************************
    "Add a RenderObject to the handler"

    This maps the objects depth to the object itself.
*********************************************/
void RenderHandler::Add(sf::Drawable* linkedObj, Layer layer, int depth){
    multimap<int, sf::Drawable*> depthMap;
    depthMap.insert(pair<int, sf::Drawable*>(depth, linkedObj));

    rmap.insert(pair< int, multimap<int, sf::Drawable* >(layer, depthMap));
}

template<typename T>
void RenderHandler::CreateObject(T newOb){
    //RenderObject<T> newObject(newOb);
    //newObject->_obType = T;

    //return newObject;
}


/*********************************************
    "Check if the screen is valid"

    returns TRUE if the screen is valid
            FALSE if the screen is invalid, aka doesn't represent the current data
*********************************************/
bool RenderHandler::isValid(){ return this->m_isValid; }

/*********************************************
    "Force the screen to redraw"
*********************************************/
void RenderHandler::invalidate(){ this->m_isValid = false; }

/*********************************************
    "sets m_isValid to true"
*********************************************/
void RenderHandler::validate(){ this->m_isValid = true; }
