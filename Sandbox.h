/*
#ifndef SANDBOX_H
#define SANDBOX_H

#include "Magnet.h"
#include "World/World.h"
#include <list>
#include <sstream>


class Sandbox
{
    public:
        Sandbox();
        ~Sandbox();

        static void Init();
        static Sandbox* Access();
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
        static Sandbox* m_ptr;

        //MouseVectors
        b2Vec2 Init_Mouse;
        b2Vec2 Released_Mouse;

        //writes config loaded values into WorldStandards
        void WriteWorldStandardsFromConfig(std::string path);


};

#endif // WORLDMANAGER_H
*/
