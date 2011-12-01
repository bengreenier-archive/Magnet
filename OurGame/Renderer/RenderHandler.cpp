#include "RenderHandler.h"

#include <iostream>
#include <queue>
#include <iterator>

#include "RenderData.h"

RenderHandler*       RenderHandler::RenderHandlerPtr = NULL;

RenderHandler::RenderHandler()
{
    WindowPtr = new sf::RenderWindow(sf::VideoMode::GetMode(3), "Chess - Adam Zielinski");
    m_isValid = false;
    m_cindex    =   0;
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

void RenderHandler::RemapDepth(sf::Drawable* obj, int depth){
    /*map<int, sf::Drawable*>::iterator it;

    for(it = object_map.begin(); it != object_map.end(); it++){
        if((*it).second == obj){
            depth_map[(*it).first] = depth;
        }
    }*/
}

void RenderHandler::SwitchLayer(sf::Drawable* obj, Layer layer){
    /*map<int, sf::Drawable*>::iterator it;

    for(it = object_map.begin(); it != object_map.end(); it++){
        if((*it).second == obj){
            layer_map[(*it).first] = layer;
        }
    }*/
}
/*********************************************
            "Draw the screen"
*********************************************/
void RenderHandler::Render(){
    if(isValid()) return;

    std::cout << "Draw\n";

    Window()->Clear(sf::Color(0, 0, 0));

    //Iterate the struct_map and draw
    multimap<int, multimap<int, int> >::iterator struct_it;
    multimap<int, int>::reverse_iterator depth_rit;

    //A queue of each layer mapped to the depths within the layer with each object index mapped to that depth
    //queue<map<int, multimap<int, int> > layerQ;

    std::cout << "There are " << struct_map.size() << " layers in struct map.\n";

    for(struct_it = struct_map.begin(); struct_it != struct_map.end(); ++struct_it){
        std::cout << "Layer " << struct_it->first  << " has " << struct_it->second.size() << " objects at depth(s) ";

        for(depth_rit = struct_it->second.rbegin(); depth_rit != struct_it->second.rend(); depth_rit++){
            std::cout << depth_rit->first << " ";
            Window()->Draw(*object_map[depth_rit->second]);
        }

        std::cout << std::endl;
    }

    Window()->Display();

    validate();
}

/*********************************************
    "Add a RenderObject to the handler"

    This maps the objects depth to the object itself.
*********************************************/
void RenderHandler::Map(sf::Drawable* linkerObj, Layer layer, int depth){
    object_map[m_cindex] = linkerObj;

    if(struct_map.find(layer) == struct_map.end()){
        multimap<int, int> tmpmap;
        tmpmap.insert(pair<int, int>(depth, m_cindex));

        struct_map.insert(pair<int, multimap<int, int> >(layer, tmpmap));
    }else{
        struct_map[layer].insert(pair<int, int>(depth, m_cindex));
    }

    m_cindex++;

    invalidate();
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
