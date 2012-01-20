#include "Registry.h"

using namespace mgui;

Registry::Registry()
{
    //ctor
}

Registry::~Registry()
{
    //dtor
}

void Registry::Register(Component* newCmp){
    if(ComponentExists(newCmp)) return;

    m_cmp_vect.push_back(newCmp);
}

Component* Registry::GetByName(const char* cmpName) throw(Exception){
    Component* find;
    if(ComponentExists(cmpName, find)){
        return find;
    }

    //create new exception
    Exception ne;
    ne.type = Exception::NullPointer;
    ne.what  = "Null Pointer";
    char* why = "No component by the name ";
    strcat(why, cmpName);
    strcat(why, " exists");
    ne.why  = why;

    throw(ne);

}

bool Registry::ComponentExists(Component* checkcmp, Component* cmp){
    return ComponentExists(checkcmp->GetName(), cmp);
}

bool Registry::ComponentExists(const char* cmpname,  Component* cmp){
    cmp_vect_iterator_type it;

    for(it = m_cmp_vect.begin(); it != m_cmp_vect.end(); it++){
        if((*it)->GetName() == cmpname){
            cmp = *it;
            return true;
        }
    }
}

bool Registry::cmp_iterator_start(){
    if(m_cmp_vect.empty()) return false;

    m_cmp_vect_it = m_cmp_vect.begin();
    return true;
}

bool Registry::do_iterate(){
    m_cmp_vect_it++;

    if(m_cmp_vect_it == m_cmp_vect.end()){
        return false;
    }

    return true;
}

bool Registry::onEvent(sf::Event evt){
    if(!cmp_iterator_start()) return true;

    Component* currentComponent;

    do{
        if(evt.Type == sf::Event::MouseWheelMoved || evt.Type == sf::Event::MouseMoved || evt.Type == sf::Event::MouseButtonPressed || evt.Type == sf::Event::MouseButtonReleased){
            cmp_queue_type component_q;
            if(evt.Type == sf::Event::MouseMoved){
                for(int i=0; i<m_cmp_vect.size(); i++)
                    component_q.push(m_cmp_vect[i]);

            }else{
                const sf::Input&    input = Renderer::GetRenderWindow()->GetInput();
                Component* component = GetComponentsByCoord(sf::Vector2f(input.GetMouseX(), input.GetMouseY()));

                if(component == NULL) return true;

                component_q.push(component);
            }

            while(!component_q.empty()){
                if(!component_q.front()->onMouseEvent(evt)){
                    return false;
                }

                component_q.pop();
            }
        }
    }while(do_iterate());

    return true;
}

Component* Registry::GetComponentsByCoord(sf::Vector2f coord){
    Component* top_cmp = NULL;
    int         top_i   =   -1;
    int         checkDepth = 0;
    int         topDepth = 0;

    for(int i=0; i<m_cmp_vect.size(); i++){
        if(m_cmp_vect[i]->CheckBounds(coord)){
            if(top_cmp == NULL){
                top_cmp = m_cmp_vect[i];
                top_i = i;
            }else{
                checkDepth = Renderer::GetObject()->GetLinkDepth(static_cast<sf::Drawable*>(m_cmp_vect[i]));
                topDepth = Renderer::GetObject()->GetLinkDepth(static_cast<sf::Drawable*>(top_cmp));

                if(checkDepth == topDepth){
                    if(i > top_i){
                        top_cmp = m_cmp_vect[i];
                        top_i = i;
                    }
                }else if(checkDepth > topDepth){
                    top_cmp = m_cmp_vect[i];
                    top_i   =   i;
                }
            }
        }
    }

    return top_cmp;
}


Registry::cmp_vect_iterator_type Registry::get_iterator(){ return m_cmp_vect_it; }
