#include "Registry.h"

using namespace mgui;

Registry::Registry()
{
    m_focus = NULL;
    m_nextdepth = 0;
}

Registry::~Registry()
{
    //dtor
}

int Registry::GetNextDepth(){ return m_nextdepth; }

void Registry::Register(Component* newCmp){
    if(ComponentExists(newCmp)) return;

    newCmp->SetRegistry(this);
    m_cmp_vect.push_back(newCmp);
    m_nextdepth++;
}

void Registry::Remove(Component* remove){
    cmp_vect_iterator_type it;

    for(it = m_cmp_vect.begin(); it != m_cmp_vect.end(); it++){
        if((*it) == remove){
            remove->SetRegistry(NULL); //This will stop the component from calling Registry::Remove again
            remove->Remove();
            it = m_cmp_vect.erase(it);
            break;
        }
    }
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
            if(cmp != NULL){
                cmp = *it;
            }
            return true;
        }
    }

    return false;
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
            for(int i=0; i<m_cmp_vect.size(); i++){
                return m_cmp_vect[i]->onMouseEvent(evt);
            }
        }
    }while(do_iterate());

    return true;
}

Component* Registry::GetTop(cmp_queue_type stack){
    Component* cmp_top = NULL;
    int top_depth;
    int check_depth;

    while(!stack.empty()){
        if(GetFocus() != NULL){
            if(stack.front()->HasFocus()){
                cmp_top = stack.front();
                break;
            }
        }

        if(cmp_top == NULL){
            cmp_top = stack.front();
        }else{
            top_depth = 0;
            check_depth = 0;

            if(top_depth<check_depth){
                cmp_top = stack.front();
            }
        }

        stack.pop();
    }

    return cmp_top;
}

Registry::cmp_queue_type Registry::GetComponentsByCoord(sf::Vector2f coord){
    cmp_queue_type found;

    for(int i=0; i<m_cmp_vect.size(); i++){
        if(m_cmp_vect[i]->CheckBounds(coord)){
            found.push(m_cmp_vect[i]);
        }
    }

    return found;
}


Component* Registry::GetFocus(){
    return m_focus;
}

void Registry::SetFocus(Component* cmp){
    if(m_focus == NULL){
        m_focus = cmp;
    }else{
        std::cout << "Setting new focus to " << cmp->GetName() << std::endl;
        Component* tmp = m_focus;
        std::cout << "Stored old focus in" << tmp->GetName() << std::endl;
        m_focus = cmp;
        std::cout << "Set new focus, formatting old focus.\n";
        tmp->Format();
    }
}

Registry::cmp_vect_iterator_type Registry::get_iterator(){ return m_cmp_vect_it; }
