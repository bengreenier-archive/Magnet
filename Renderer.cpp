#include "Renderer.h"
#include "Handler/Renderer/LinkableSprite.h"

#include <iostream>
#include <queue>
#include <iterator>
#include <typeinfo>

Renderer*               Renderer::RendererPtr = NULL;

Renderer::Renderer()
{
    //Move to loader
    WindowPtr = new sf::RenderWindow(sf::VideoMode::GetMode(3), "Chess - Adam Zielinski");
   // m_isValid = false;
    m_cindex    =   0;

    m_isValid = false;

    //AddLayer(Layer newLayer);
}

//Clean up all the allocated memory space
Renderer::~Renderer()
{
    delete [] WindowPtr;
    delete [] RendererPtr;
}

void Renderer::Link(LinkableSprite& sprite){
    GetObject()->linkables.push_back(sprite);
    GetObject()->m_cindex++;
    GetObject()->invalidate();
}
/*
void Renderer::Link(sf::Drawable* linkedObj, Layer layer){
    GetObject()->Map(linkedObj, layer, 0);
}

void Renderer::Link(sf::Drawable* linkedObj, Layer layer, int depth){
    GetObject()->Map(linkedObj, layer, depth);
}
*/
/*
template<typename _T>
static void Renderer::Link(RenderObject<_T> &linkedObj){
    RenderHandler::GetObject()->Add(linkedObj);
}
*/
/*********************************************
    "Get the RenderHandler object"

    Returns a pointer to the RenderHandler

    *Uses lazy initialization
*********************************************/
Renderer* Renderer::GetObject(){
    if(RendererPtr == NULL){
        RendererPtr = new Renderer();
    }

    return RendererPtr;
}

/*********************************************
    "Gets a pointer to the current window"

    Returns a pointer to the sf::RenderWindow
*********************************************/
sf::RenderWindow* Renderer::Window(){
    return GetObject()->WindowPtr;
}
/*********************************************
            "Draw the screen "
*********************************************/
void Renderer::Render(){
    if(GetObject()->isValid()) return;

    //std::cout << "Draw\n";

    //Iterate the struct_map and draw
    /*multimap<int, multimap<int, int> >::iterator struct_it;
    multimap<int, int>::reverse_iterator depth_rit;

    map<int, sf::Drawable*>::iterator ob_it;
    */
    //A queue of each layer mapped to the depths wi thin the layer with each object index mapped to that depth
    //queue<map<int, multimap<int, int> > layerQ;

    //std::cout << "There are " << object_map.size() << " object(s) in struct map.\n";

    Window()->Clear(sf::Color(0, 0, 0));
/*
    for(ob_it = object_map.begin(); ob_it != object_map.end(); ob_it++){
        Window()->Draw(*(*ob_it).second);
    }
*/
    /*
    for(struct_it = struct_map.begin(); struct_it != struct_map.end(); ++struct_it){
        std::cout << "Layer " << struct_it->first  << " has " << struct_it->second.size() << " objects at depth(s) ";

        for(depth_rit = struct_it->second.rbegin(); depth_rit != struct_it->second.rend(); depth_rit++){
            std::cout << depth_rit->first << "(" << depth_rit->second << ") ";

            Window()->Draw(*object_map[depth_rit->second]);

        }

        std::cout << std::endl;
    }
    */
/*
    for(GetObject()->layer_iterator = GetObject()->layer_map.begin(); GetObject()->layer_iterator != GetObject()->layer_map.end(); GetObject()->layer_iterator++){
        for(GetObject()->object_iterator = GetObject()->layer_iterator->second.begin(); GetObject()->object_iterator != GetObject()->layer_iterator->second.end(); GetObject()->object_iterator++){
            Window()->Draw(GetObject()->object_iterator->second);
        }
    }
*/
    for(GetObject()->linkables_it = GetObject()->linkables.begin(); GetObject()->linkables_it != GetObject()->linkables.end(); GetObject()->linkables_it++){
        Window()->Draw(*GetObject()->linkables_it);
    }

    Window()->Display();

    GetObject()->validate();
}

/*********************************************
    "Add a RenderObject to the handler"

    This maps the objects depth to the object itself.
*********************************************/
void Renderer::Map(LinkableSprite object){
   // std::cout << "Inserting new object index: " << m_cindex << "\n";
   //std::cout << "Index: " << m_cindex << "  ->  " << linkerObj.GetImage() << std::endl;
   // object_map[m_cindex] = linkerObj;
   // std::cout << "Index: " << m_cindex << "  ->  " << linkerObj.GetImage() << std::endl;
    //std::cout << "Added new object, new object_map size: " << object_map.size() << "\n";
    /*
    if(struct_map.find(layer) == struct_map.end()){
        multimap<int, int> tmpmap;
        tmpmap.insert(pair<int, int>(depth, m_cindex));

        struct_map.insert(pair<int, multimap<int, int> >(layer, tmpmap));
    }else{
        struct_map[layer].insert(pair<int, int>(depth, m_cindex));
    }


*/
    //pair<int, LinkableObject*> tmpPair (m_cindex, object);
    //map<layer_t, map<int, LinkableObject*> > layer_map;

}

/*********************************************
    "Check if the screen is valid"

    returns TRUE if the screen is valid
            FALSE if the screen is invalid, aka doesn't represent the current data
*********************************************/
bool Renderer::isValid(){ return m_isValid; }

/*********************************************
    "Force the screen to redraw"
*********************************************/
void Renderer::invalidate(){ GetObject()->m_isValid = false; }

/*********************************************
    "sets m_isValid to true"
*********************************************/
void Renderer::validate(){ m_isValid = true; }
