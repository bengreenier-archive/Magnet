/*
#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "../Magnet.h"
#include "World.h"
#include <list>
#include <sstream>


class WorldManager
{
    public:
        WorldManager();
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


        World* Add(World* in){ m_WorldList.push_back(in); m_WorldList.back()->uuid = m_curuuid; m_curuuid++; return m_WorldList.back(); }
        World* AddUndefinedWorld(){ return Add(new World()); }
        void RemoveCurrentWorld() { Remove(CurrentWorld()); }
        void HideWorld(World* in){ GetWorld(in)->Hide(); }

        void SelectWorld(World* in);
        World* CurrentWorld();
        World* GetWorld(World* in);
        void Remove(World* in);

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

        //lol logo
        int lol_logo_counter;
        sf::Sprite* lol_sprite;

};

#endif // WORLDMANAGER_H
*/
