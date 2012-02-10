/*#include "Registry.h"

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
}

void Registry::Remove(Component* remove){
    cmp_vect_iterator_type it;

    for(it = m_cmp_vect.begin(); it != m_cmp_vect.end(); it++){
        if((*it) == remove){
            const char* name = remove->GetName();
            if(GetFocus() == remove){
                ReleaseFocus();
            }
            remove->SetRegistry(NULL); //This will stop the component from calling Registry::Remove again
            remove->Remove();
            it = m_cmp_vect.erase(it);
            std::cout << "[Registry][Remove]\t" << name << ": Removed.\n";
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
    if(evt.Type == sf::Event::MouseWheelMoved || evt.Type == sf::Event::MouseMoved || evt.Type == sf::Event::MouseButtonPressed || evt.Type == sf::Event::MouseButtonReleased){
        if(evt.Type == sf::Event::MouseButtonPressed){
            cmp_queue_type cmp_queue = GetComponentQueue(sf::Vector2f(evt.MouseButton.X, evt.MouseButton.Y));

            if(!cmp_queue.empty()){
                SetFocus(GetTop(cmp_queue));
            }else{
                ReleaseFocus();
            }
        }

        if(GetFocus() != NULL){
            return GetFocus()->onMouseEvent(evt);
        }
    }

    return true;
}

Component* Registry::GetTop(cmp_queue_type stack){
    Component* cmp_top = NULL;
    Component* cur = NULL;
    int top_depth;
    int check_depth;

    while(!stack.empty()){
        cur = stack.front();

        if(cmp_top == NULL){
            cmp_top = cur;
            top_depth = cmp_top->GetDepth();
        }else{
            check_depth = cur->GetDepth();

            if(top_depth<check_depth){
                cmp_top = cur;
                top_depth = cmp_top->GetDepth();
            }
        }

        stack.pop();
    }

    return cmp_top;
}

Registry::cmp_queue_type Registry::GetComponentQueue(sf::Vector2f coord){
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
    if(!cmp->CanFocus()) return;

    if(m_focus == NULL){
        m_focus = cmp;
    }else{
        ReleaseFocus();
        m_focus = cmp;
    }

    m_focus->SetDepth(1);
    m_focus->Format();
}

void Registry::ReleaseFocus(){
    if(m_focus == NULL) return;

    Component* tmp = m_focus;
    m_focus = NULL;
    tmp->SetDepth(tmp->GetDepth()-1);
    tmp->Format();

}

Registry::cmp_vect_iterator_type Registry::get_iterator(){ return m_cmp_vect_it; }
*/
