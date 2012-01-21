#include "Renderer.h"
#include "../Magnet.h"

Renderer*               Renderer::RendererPtr         = NULL;

Renderer::Renderer()
{
    m_cindex        =   0;
    m_isValid       = false;
    m_shouldDraw    = true;

    EventHandler::AddListener(new EventListener(sf::Event::KeyPressed, &Renderer::Event_KeyPressed));
}

//Clean up all the allocated memory space
Renderer::~Renderer()
{
    delete [] RendererPtr;
    delete [] RenderWindow_ptr;
}

bool Renderer::Event_KeyPressed(sf::Event evt){
    if(evt.Key.Code == sf::Key::Escape){
        Renderer::Close(evt);
    }

    return true;
}

bool Renderer::Close(sf::Event evt){

    Renderer::GetRenderWindow()->Close();
    GetObject()->renderThread_ptr->Wait();

    return true;
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
    while(GetRenderWindow()->IsOpened() && Magnet::Initialized()){
        //Process the new link queue
        while(!GetObject()->newlink_queue.empty()){
            GetObject()->_CreateLink(GetObject()->newlink_queue.front());
            GetObject()->newlink_queue.pop();
        }
        //Process the remove link queue
        while(!GetObject()->delete_queue.empty()){
            GetObject()->_RemoveLink(GetObject()->delete_queue.front());
            GetObject()->delete_queue.pop();
        }

        GetRenderWindow()->Clear(sf::Color(0, 0, 0));

        for(int i=0; i < GetObject()->links.size(); i++){
            GetRenderWindow()->Draw(*GetObject()->links[i]->object);
        }

        GetRenderWindow()->Display();


        Magnet::Hooks("Renderer::Render")->Call(Hook::Frame);
    }
}

Renderer::Link* Renderer::CreateLink(sf::Drawable* drawable_ptr, Layer layer, int depth){
    Link* newLink   =   new Link();
    newLink->object  = drawable_ptr;
    newLink->layer   = layer;
    newLink->depth   = depth;

    GetObject()->newlink_queue.push(newLink);
    return newLink;
}

void Renderer::_CreateLink(Renderer::Link* newLink){
    if(GetObject()->links.empty()){
        GetObject()->links.push_back(newLink);
    }else{
        links_iterator_t it;
        bool insertBefore = false;
        bool insertAfter = false;

        for(it = links.begin(); it != links.end(); it++){

            if((*it)->layer > newLink->layer){
                insertBefore = true;
            }else if((*it)->layer == newLink->layer){
                if((*it)->depth > newLink->depth){
                    insertBefore = true;
                }else if((*it)->depth == newLink->depth){
                    if((it+1) == links.end() || (*(it+1))->layer != newLink->layer || (*(it+1))->depth != newLink->depth){
                        insertAfter = true;
                    }
                }
            }
            if(!insertBefore && !insertAfter){
                if((it+1) == links.end()){
                    insertAfter = true;
                }
            }

            if(insertBefore){
                links.insert(it, newLink);
                break;
            }

            if(insertAfter){
                links.insert(it+1, newLink);
                break;
            }
        }
    }
}

void Renderer::CreateLink(Link* link_ptr){
    GetObject()->newlink_queue.push(link_ptr);
}

Renderer::Link* Renderer::CreateLink(sf::Drawable* drawable_ptr, Layer layer){
    return Renderer::CreateLink(drawable_ptr, layer, 0);
}


Renderer::Link* Renderer::CreateLink(sf::Drawable* drawable_ptr){
    return Renderer::CreateLink(drawable_ptr, Renderer::GameLayer, 0);
}

void Renderer::RemoveLink(sf::Drawable* drawable_ptr){
    Link* link = GetObject()->GetLinkByDrawable(drawable_ptr);

    if(link == NULL) return;

    GetObject()->delete_queue.push(link);
}

void Renderer::RemoveLink(Link* link_ptr){
    if(GetObject()->LinkExists(link_ptr)){
        GetObject()->delete_queue.push(link_ptr);
    }
}

void Renderer::_RemoveLink(Link* oldLink){
    int linkIndex = GetLinkIndex(oldLink);

    if(linkIndex == -1) return;

    links.erase(links.begin()+linkIndex);
}

Renderer::Link* Renderer::GetLinkByDrawable(sf::Drawable* drawable_ptr){
    Link* link = NULL;

    for(int i = 0; i < links.size(); i++){
        if(links[i]->object == drawable_ptr){
            link = links[i];
        }
    }

    return link;
}

bool Renderer::LinkExists(Renderer::Link* link_ptr){
    if(GetLinkIndex(link_ptr) != -1){
        return true;
    }

    return false;
}

int Renderer::GetLinkIndex(Link* link_ptr){
    links_iterator_t it;

    for(int i = 0; i < links.size(); i++){
        if(links[i] == link_ptr){
            return i;
        }
    }

    return -1;
}

void Renderer::SetLinkLayer(sf::Drawable* drawable_ptr, Layer newLayer){
    //Renderer::RemoveLink(drawable_ptr);
    //Renderer::CreateLink(drawable_ptr, newLayer);
}
