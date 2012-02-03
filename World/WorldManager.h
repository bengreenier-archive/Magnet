#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "../Magnet.h"
#include "World.h"
#include <list>



class WorldManager
{
    public:
        /** Default constructor */
        WorldManager();
        /** Default destructor */
        ~WorldManager();

        static void Init();
        static WorldManager* Access();
        static void Renderer_Frame_Hook();
        static void Magnet_Load_Hook();
        static bool Event_MouseButtonReleased(sf::Event evt);
        static bool Event_MouseButtonPressed(sf::Event evt);
        static bool Event_MouseWheelMoved(sf::Event evt);
        static bool Event_KeyReleased(sf::Event evt);
        static bool Event_MouseMoved(sf::Event evt);
        static bool Event_KeyPresed(sf::Event evt);

        static bool Achievement_Conditions(sf::Event evt);
        static void Achievement_Completion(std::string name);


        World* Add(World* in){ m_WorldList.push_back(in); m_WorldList.back()->uuid = m_curuuid; m_curuuid++;  m_curWorld=m_WorldList.back(); return m_WorldList.back(); }
        World* AddUndefinedWorld(){ return Add(new World(defaultconstraint,b2Vec2(0.0f,10.0f))); }
        void Remove(World* in)
            {
                std::list<World*>::iterator it;
                for (it=m_WorldList.begin();it != m_WorldList.end();it++)
                {

                    if ((*it)->uuid == in->uuid){
                        (*it)->Unload();
                        m_WorldList.erase(it);
                    }

                }
            }

        void HideWorld(World* in){ GetWorld(in)->Hide(); }

        World* CurrentWorld();

        void RemoveCurrentWorld() { Remove(CurrentWorld()); }

        void SelectWorld(World* in)
            {
                std::list<World*>::iterator it;
                for (it=m_WorldList.begin();it != m_WorldList.end();it++)
                {

                    if ((*it)->uuid == in->uuid)
                        m_curWorld = (*it);

                }

            }

        World* GetWorld(World* in)
        {
            std::list<World*>::iterator it;
                for (it=m_WorldList.begin();it != m_WorldList.end();it++)
                {

                    if ((*it)->uuid == in->uuid)
                        return (*it);

                }
        }
    protected:
    private:
        std::list<World*> m_WorldList;
        World* m_curWorld;
        int m_curuuid;
        int defaultconstraint;
        static WorldManager* m_ptr;

        //achiev varibles
        bool has_clicked;

        //MouseVectors
        b2Vec2 Init_Mouse;
        b2Vec2 Released_Mouse;

};

#endif // WORLDMANAGER_H
