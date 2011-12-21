#include "Renderer.h"
#include "Handlers/EventHandler.h"
#include "Console/Console.h"

#include <queue>
#include <iterator>
#include <typeinfo>

Renderer*               Renderer::RendererPtr         = NULL;

Renderer::Renderer()
{
    m_cindex    =   0;
    m_isValid = false;
    renderThreadPtr = NULL;


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
    delete [] renderThreadPtr;
}

void Renderer::Close(sf::Event evt){
    GetObject()->renderThreadPtr->isRunning = false;
    GetObject()->renderThreadPtr->threadPtr->Terminate();
    Renderer::GetRenderWindow()->Close();
}

void Renderer::SetRenderWindow(sf::RenderWindow& Window){
    RenderWindow_ptr = &Window;
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

void Renderer::InitRenderThread(void* threadData){
    if(renderThreadPtr == NULL){
        std::string* threadName = static_cast<std::string*>(threadData);
        renderThreadPtr =   Magnet::GetManagedThread(*threadName);
    }
}
/*********************************************
            "Draw the screen "
*********************************************/
void Renderer::Render(void* threadData){
    GetObject()->InitRenderThread(threadData);

    while(GetRenderWindow()->IsOpened()){
        if(GetObject()->isValid()){ return; }

        GetRenderWindow()->Clear(sf::Color(0, 0, 0));

        for(    GetObject()->struct_iterator = GetObject()->struct_map.begin();
                GetObject()->struct_iterator != GetObject()->struct_map.end();
                GetObject()->struct_iterator++   )
        {
            multimap<int, int>::iterator depth_iterator;
            for(    depth_iterator = GetObject()->struct_iterator->second.begin();
                    depth_iterator != GetObject()->struct_iterator->second.end();
                    depth_iterator++   )
            {
                GetRenderWindow()->Draw(*GetObject()->drawable_map[depth_iterator->second]);
            }


        }

        GetRenderWindow()->Display();

        GetObject()->validate();
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

/*
void Renderer::SetLayer(sf::Drawable* drawable_ptr, Layer newLayer){
    map<int, sf::Drawable*>::iterator it;

    int index = -1;

    for(it = GetObject()->drawable_map.begin();
        it != GetObject()->drawable_map.end();
        it++   )
    {
        if(drawable_ptr == it->second){
            index = it->first;
        }
    }

    if(index == -1){
        std::cout << "Could not change layer, drawable not linked!\n";
    }else{
        int linkedDepth;
        bool depthSet = false;
        bool layerSet = false;
        map<Layer, multimap<int, int> >::iterator sit;
        map<Layer, multimap<int, int> >::iterator sit_storage;
        map<Layer, multimap<int, int> >::iterator sit_storage_old;
        multimap<int, int>::iterator              dit;

        std::cout << "Moving " << &*drawable_ptr << " to layer " << newLayer << std::endl;

        for(sit =   GetObject()->struct_map.begin();
            sit !=  GetObject()->struct_map.end();
            sit++  )
        {
            std::cout << sit->first << " == " << newLayer << " && " << (!layerSet) << std::endl;
            if(sit->first == newLayer && !layerSet){
                std::cout << "Found the layer we want to move to, storing into sit storage...\n";
                sit_storage = sit;
                layerSet = true;
                std::cout << "\tlayerSet = true\n";

                if(depthSet){
                    std::cout << "Depth already set, exiting loop\n";
                    break;
                }
            }

            if(!depthSet){
                std::cout << "Searching for index in layer " << sit->first << std::endl;
                for(dit = sit->second.begin();
                    dit != sit->second.end();
                    dit++ )
                {
                    std::cout << dit->second << " == " << index << std::endl;
                    if(dit->second == index){
                        std::cout << "Index found in layer " << sit->first << " at depth " << dit->first << ", storing the depth\n";
                        linkedDepth = dit->first;
                        sit_storage_old = sit;
                        depthSet = true;
                        std::cout << "\depthSet = true\n";

                        if(layerSet){
                            std::cout << "Layer already set, exiting loop\n";
                            break;
                        }
                    }
                }
            }
        }

        if(GetObject()->struct_map.find(newLayer) == GetObject()->struct_map.end()){
            multimap<int, int> copyMap;
            copyMap.insert(pair<int, int>(linkedDepth, index));
            GetObject()->struct_map.insert(pair<int, multimap<int, int> >(newLayer, copyMap));

        std::cout << "Here\n";
            sit_storage_old->second.erase(dit);

        std::cout << "Here2\n";
        }else{
            sit_storage->second.insert(pair<int, int>(linkedDepth, index));
            sit_storage_old->second.erase(dit);
        }
    }

    //invalidate();
}
*/
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
