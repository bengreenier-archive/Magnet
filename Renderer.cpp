#include "Renderer.h"
#include "Handlers/EventHandler.h"
#include "Console/Console.h"
#include "Magnet.h"
#include <queue>
#include <iterator>
#include <typeinfo>

Renderer*               Renderer::RendererPtr         = NULL;

Renderer::Renderer()
{
    m_cindex    =   0;
    m_isValid = false;
    m_shouldDraw = true;

    EventHandler::AddKeyListener(sf::Key::Escape, &Renderer::Close);
    EventHandler::AddEventListener(sf::Event::Closed, &Renderer::Close);

   // Console::AddCommand("invalidateWindow",&Window::invalidate);
    //Console::AddCommand("render",&Window::Render);
}

//Clean up all the allocated memory space
Renderer::~Renderer()
{
    delete [] RendererPtr;
    delete [] RenderWindow_ptr;
}

void Renderer::Close(sf::Event evt){
    Magnet::Hooks()->Call(Hook::Close);

    Renderer::GetRenderWindow()->Close();
    GetObject()->renderThread_ptr->Terminate();
}

void Renderer::SetRenderWindow(sf::RenderWindow& Window){
    GetObject()->RenderWindow_ptr = &Window;
}

void Renderer::SetRenderThread(sf::Thread& renderThread){
    GetObject()->renderThread_ptr = &renderThread;
}

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
sf::RenderWindow* Renderer::GetRenderWindow(){
    return GetObject()->RenderWindow_ptr;
}
/*********************************************
            "Draw the screen "
*********************************************/
void Renderer::Render(void* threadData){
    GetObject()->m_shouldDraw = true;
    while(GetRenderWindow()->IsOpened() && GetObject()->m_shouldDraw){
        Magnet::Hooks()->Call(Hook::Frame);

        Magnet::GlobalMutex()->Lock();
        //std::cout << "Calling frame hook...\n";

        //std::cout << "Processing remove queue...\n";
        //Process the remove queue
        while(!GetObject()->remove_queue.empty()){
            GetObject()->_RemoveLink(GetObject()->remove_queue.front());
            GetObject()->remove_queue.pop();
        }

        //std::cout << "Clearning window...\n";
        GetRenderWindow()->Clear(sf::Color(0, 0, 0));

        struct_map_it_t struct_it;
        //std::cout << "Drawing...\n";
        for(    struct_it = GetObject()->struct_map.begin();
                struct_it != GetObject()->struct_map.end();
                struct_it++   )
        {
            multimap<int, int>::iterator depth_iterator;
            for(    depth_iterator = struct_it->second.begin();
                     depth_iterator != struct_it->second.end();
                    depth_iterator++   )
            {
                    GetRenderWindow()->Draw(*GetObject()->drawable_map[depth_iterator->second]);
                    //std::cout << "\tDraw\n";
            }


        }

        GetRenderWindow()->Display();
        Magnet::GlobalMutex()->Unlock();
        //std::cout << "****END FRAME****\n\n";
    }
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
}


void Renderer::CreateLink(sf::Drawable* drawable_ptr, Layer layer){
    Renderer::CreateLink(drawable_ptr, layer, 0);
}


void Renderer::CreateLink(sf::Drawable* drawable_ptr){
    Renderer::CreateLink(drawable_ptr, Renderer::GameLayer, 0);
}

void Renderer::RemoveLink(sf::Drawable* drawable_ptr){
    int linkIndex = GetObject()->GetLinkIndex(drawable_ptr);

    if(linkIndex == -1) return;

    GetObject()->remove_queue.push(linkIndex);
}

void Renderer::_RemoveLink(int linkIndex){
    struct_map_it_t struct_it;
    map<int, int>::iterator depth_it;

    for(struct_it =     struct_map.begin();
        struct_it !=    struct_map.end();
        struct_it++)
    {
        for(depth_it =  struct_it->second.begin();
            depth_it != struct_it->second.end();
            depth_it++)
        {
            if(depth_it->second == linkIndex){
                struct_it->second.erase(depth_it);
                drawable_map.erase(linkIndex);
                break;
            }
        }
    }
}



bool Renderer::LinkExists(sf::Drawable* drawable_ptr){
    if(GetLinkIndex(drawable_ptr) != -1){
        return true;
    }

    return false;
}

int Renderer::GetLinkIndex(sf::Drawable* drawable_ptr){
    drawable_map_it_t it;

    for(it  =   drawable_map.begin();
        it  !=  drawable_map.end();
        it++)
    {
        if(it->second == drawable_ptr){
            return it->first;
        }
    }

    return -1;
}


void Renderer::SetLinkLayer(sf::Drawable* drawable_ptr, Layer newLayer){
    Renderer::RemoveLink(drawable_ptr);
    Renderer::CreateLink(drawable_ptr, newLayer);
}
