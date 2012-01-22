#include "Renderer.h"
#include "../Magnet.h"

Renderer*               Renderer::RendererPtr         = NULL;

Renderer::Renderer()
{
    m_cindex        =   0;
    m_isValid       = false;
    m_shouldDraw    = true;
    m_running       = false;
    //m_max_process   =   1;  //The total amount of objects to add/remove in a frame
    //m_max_atempts   =   5;  //The total amount of attempts to process in a frame

    Magnet::Hooks()->Register(Hook::Frame, &Renderer::Frame);
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

sf::Mutex* Renderer::Mutex(){
    return &Object("Renderer::Mutex")->renderMutex;
}

bool Renderer::Close(sf::Event evt){
    std::cout << "Closed\n";
    Renderer::GetRenderWindow()->Close();
    Object("Renderer::Close")->renderThread_ptr->Wait();

    return true;
}

void Renderer::SetRenderWindow(sf::RenderWindow& Window){
    Object("Renderer::SetRenderWindow")->RenderWindow_ptr = &Window;
}

void Renderer::SetRenderThread(sf::Thread& renderThread){
    Object("Renderer::SetRenderThread")->renderThread_ptr = &renderThread;
}

/*********************************************
    "Get the RenderHandler object"

    Returns a pointer to the RenderHandler

    *Uses lazy initialization
*********************************************/
Renderer* Renderer::Object(std::string from){
    if(RendererPtr == NULL){
        std::cout << "Renderer::Object("<<from<<")-> WARNING: Renderer not initialized! Null pointer returned\n";
    }

    return RendererPtr;
}

void Renderer::Init(sf::RenderWindow& window, sf::Thread& renderThread){
    RendererPtr = new Renderer();

    Renderer::SetRenderWindow(window);
    Renderer::SetRenderThread(renderThread);
}

/*********************************************
    "Gets a pointer to the current window"

    Returns a pointer to the sf::RenderWindow
*********************************************/
sf::RenderWindow* Renderer::GetRenderWindow(){
    return Object("Renderer::GetRenderWindow()")->RenderWindow_ptr;
}

void Renderer::Frame(){

    //Process the remove link queue
    while(!Object("Frame")->delete_queue.empty()){
        Object("Frame")->_RemoveLink(Object("Frame")->delete_queue.front());

        if(!Renderer::Object("Frame")->LinkExists(Object("Frame")->delete_queue.front())){
            Object("Frame")->delete_queue.pop();
        }
    }

    while(!Object("Frame")->newlink_queue.empty()){
        Object("Frame")->_CreateLink(Object("Frame")->newlink_queue.front());

        if(Renderer::Object("Frame")->LinkExists(Object("Frame")->newlink_queue.front())){
            Object("Frame")->newlink_queue.pop();
        }
    }
}

/*********************************************
            "Draw the screen "
*********************************************/
void Renderer::Render(void* threadData){
    if(!GetRenderWindow()->IsOpened()) return;

    Renderer::Mutex()->Lock();
    Object("Frame")->m_running = true;

    GetRenderWindow()->Clear(sf::Color(0, 0, 0));

    for(int i=0; i < Object("Frame")->links.size(); i++){
        GetRenderWindow()->Draw(*Object("Frame")->links[i]->object);
    }

    GetRenderWindow()->Display();

    Renderer::Mutex()->Unlock();
    Object("Frame")->m_running = false;
}

Renderer::Link* Renderer::CreateLink(sf::Drawable* drawable_ptr, Layer layer, int depth){
    Link* newLink   =   new Link();
    newLink->object  = drawable_ptr;
    newLink->layer   = layer;
    newLink->depth   = depth;

    Object("Frame")->newlink_queue.push(newLink);
    return newLink;
}

void Renderer::_CreateLink(Renderer::Link* newLink){
    Renderer::Mutex()->Lock();

    if(Object("Frame")->links.empty()){
        Object("Frame")->links.push_back(newLink);
    }else{
        links_iterator_t it;
        bool insertBefore = false;
        bool insertAfter = false;

        for(it = Object("Create")->links.begin(); it != Object("Create")->links.end(); it++){

            if((*it)->layer > newLink->layer){
                insertBefore = true;
            }else if((*it)->layer == newLink->layer){
                if((*it)->depth > newLink->depth){
                    insertBefore = true;
                }else if((*it)->depth == newLink->depth){
                    if((it+1) == Object("Create")->links.end() || (*(it+1))->layer != newLink->layer || (*(it+1))->depth != newLink->depth){
                        insertAfter = true;
                    }
                }
            }
            if(!insertBefore && !insertAfter){
                if((it+1) == Object("Create")->links.end()){
                    insertAfter = true;
                }
            }

            if(insertBefore){
                Object("Create")->links.insert(it, newLink);
                break;
            }

            if(insertAfter){
                Object("Create")->links.insert(it+1, newLink);
                break;
            }
        }
    }
    Renderer::Mutex()->Unlock();
}

void Renderer::CreateLink(Link* link_ptr){
    Object("Create")->newlink_queue.push(link_ptr);
}

Renderer::Link* Renderer::CreateLink(sf::Drawable* drawable_ptr, Layer layer){
    return Renderer::CreateLink(drawable_ptr, layer, 0);
}


Renderer::Link* Renderer::CreateLink(sf::Drawable* drawable_ptr){
    return Renderer::CreateLink(drawable_ptr, Renderer::GameLayer, 0);
}

void Renderer::RemoveLink(sf::Drawable* drawable_ptr){
    Link* link = Object("RemoveLink")->GetLinkByDrawable(drawable_ptr);

    if(link == NULL) return;

    Object("RemoveLink")->delete_queue.push(link);
}

void Renderer::RemoveLink(Link* link_ptr){
    if(Object("RemoveLink")->LinkExists(link_ptr)){
        Object("RemoveLink")->delete_queue.push(link_ptr);
    }
}

void Renderer::_RemoveLink(Link* oldLink){
    Renderer::Mutex()->Lock();
    int linkIndex = GetLinkIndex(oldLink);

    if(linkIndex == -1) return;

    links.erase(links.begin()+linkIndex);

    //Make sure the link has been erased
    while(LinkExists(oldLink)){}

    Renderer::Mutex()->Unlock();
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
