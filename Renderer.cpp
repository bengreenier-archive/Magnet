#include "Renderer.h"
#include "Console/Console.h"

#include <queue>
#include <iterator>
#include <typeinfo>

Renderer*               Renderer::RendererPtr = NULL;

Renderer::Renderer()
{
    //Move to loader
    WindowPtr = new sf::RenderWindow(sf::VideoMode::GetMode(3), "Magnet");
    m_cindex    =   0;

    //_renderThread(sf::Thread(&Renderer::_render));
    //_linkThread     = new sf::Thread(&_link);

    m_isValid = false;

    Console::AddCommand("Renderer::invalidate()",&Renderer::invalidate);
    Console::AddCommand("Renderer::Render()",&Renderer::Render);
    //Console::AddCommand("Renderer::isValid()",&Renderer::isValid);      //These aren't static, so don't allow useage, cause they might not work.
    //Console::AddCommand("Renderer::validate()",&Renderer::validate);

}

//Clean up all the allocated memory space
Renderer::~Renderer()
{
    delete [] WindowPtr;
    delete [] RendererPtr;
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

    Window()->Clear(sf::Color(0, 0, 0));

    std::cout << "There are " << GetObject()->struct_map.size() << " layers.\n";

    for(    GetObject()->struct_iterator = GetObject()->struct_map.begin();
            GetObject()->struct_iterator != GetObject()->struct_map.end();
            GetObject()->struct_iterator++   )
    {
        std::cout << "Layer " << GetObject()->struct_iterator->first << ":   \n";

        multimap<int, int>::iterator depth_iterator;
        for(    depth_iterator = GetObject()->struct_iterator->second.begin();
                depth_iterator != GetObject()->struct_iterator->second.end();
                depth_iterator++   )
        {
            std::cout << "\tDepth: " << depth_iterator->first << std::endl;
            std::cout << "\t\t" <<  &depth_iterator->second << std::endl;

            Window()->Draw(*GetObject()->drawable_map[depth_iterator->second]);
        }


    }

    Window()->Display();

    GetObject()->validate();
}

void Renderer::CreateLink(sf::Drawable* drawable_ptr, Layer layer, int depth){
    GetObject()->drawable_map[GetObject()->m_cindex] = &*drawable_ptr;
    drawable_ptr = &*GetObject()->drawable_map[GetObject()->m_cindex];


    if(GetObject()->struct_map.find(layer) == GetObject()->struct_map.end()){
        multimap<int, int> copyMap;
        copyMap.insert(pair<int, int>(depth, GetObject()->m_cindex));
        GetObject()->struct_map.insert(pair<int, multimap<int, int> >(layer, copyMap));
    }else{
        map< Layer, multimap<int, int> >::iterator tmp_struct_iterator;

        for(
            tmp_struct_iterator = GetObject()->struct_map.begin();
            tmp_struct_iterator != GetObject()->struct_map.end();
            tmp_struct_iterator++)
        {
            if(tmp_struct_iterator->first == layer){
                tmp_struct_iterator->second.insert(pair<int, int>(depth, GetObject()->m_cindex));
            }
        }
    }

    GetObject()->m_cindex++;
    std::cout << "Link created, there are " << GetObject()->struct_map.size() << std::endl;
}


void Renderer::CreateLink(sf::Drawable* drawable_ptr, Layer layer){
    Renderer::CreateLink(drawable_ptr, layer, 0);
}


void Renderer::CreateLink(sf::Drawable* drawable_ptr){
    Renderer::CreateLink(drawable_ptr, Renderer::GameLayer, 0);
}


void  Renderer::sort(){
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
