/*
#include "WorldManager.h"

WorldManager* WorldManager::m_ptr = NULL;

WorldManager::WorldManager()
{
    //ctor
    m_curuuid=0;
    defaultconstraint=500;

    //achievs
    has_clicked=false;//player hasn't clicked originally


    //the hooked hooks
    Renderer::Hooks()->Register(Hook::Frame,&WorldManager::Renderer_Frame_Hook);
    Magnet::Hooks()->Register(Hook::Setup,&WorldManager::Magnet_Load_Hook);

    //all our events
    EventHandler::AddListener(new EventListener(sf::Event::MouseButtonReleased, &WorldManager::Event_MouseButtonReleased));
    EventHandler::AddListener(new EventListener(sf::Event::MouseButtonPressed, &WorldManager::Event_MouseButtonPressed));
    EventHandler::AddListener(new EventListener(sf::Event::MouseWheelMoved, &WorldManager::Event_MouseWheelMoved));
    EventHandler::AddListener(new EventListener(sf::Event::KeyReleased,&WorldManager::Event_KeyReleased));
    EventHandler::AddListener(new EventListener(sf::Event::MouseMoved, &WorldManager::Event_MouseMoved));
    EventHandler::AddListener(new EventListener(sf::Event::KeyPressed,&WorldManager::Event_KeyPresed));

    //Magnet::Achieves()->Register(new Achievement("World_Mouse_Click","You learned to click the screen!",&WorldManager::Achievement_Completion),new EventListener(sf::Event::MouseButtonReleased,&WorldManager::Achievement_Conditions));

    //init mouseposes
    Released_Mouse = b2Vec2(0,0);
    Init_Mouse = b2Vec2(0,0);

    //lol_logo
    lol_logo_counter=0;
    lol_sprite = new sf::Sprite();


}


void WorldManager::SelectWorld(World* in)
{
    std::list<World*>::iterator it;
    for (it=m_WorldList.begin();it != m_WorldList.end();it++)
    {

        if ((*it)->uuid == in->uuid)
            m_curWorld = (*it);

    }

}

World* WorldManager::GetWorld(World* in)
{
    std::list<World*>::iterator it;
        for (it=m_WorldList.begin();it != m_WorldList.end();it++)
        {

            if ((*it)->uuid == in->uuid)
                return (*it);

        }
}

void WorldManager::Remove(World* in)
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


WorldManager::~WorldManager()
{
    //dtor
}

void WorldManager::Init()
{
    m_ptr = new WorldManager();
}

WorldManager* WorldManager::Access()
{
    if (!m_ptr)
        std::cout<<"[WorldManager][Access] Returning NULL PTR.\n";

    return m_ptr;
}

World* WorldManager::CurrentWorld()
{
  if (!m_curWorld)
    std::cout<<"[WorldManager][CurrentWorld] Returning NULL PTR.\n";

  return m_curWorld;
}

//HOOKS BELOW

void WorldManager::Renderer_Frame_Hook()
{
    if (Access()->lol_logo_counter==0)
    {

    }

    if (Access()->lol_logo_counter>100)
    {
        Renderer::RemoveLink(Access()->lol_sprite);
    }


    Access()->lol_logo_counter++;

    if (Access()->CurrentWorld())
    Access()->CurrentWorld()->Step();
}

void WorldManager::Magnet_Load_Hook()
{

    //parse the resources sandbox needs loaded
    Config load;
    CfgParse cfgparser("resource/sandbox.mcf");
    cfgparser.Parse(load);
    if(!cfgparser.IsParsed()){
        if (WorldStandards::debug)
            std::cout<<"Parsing Sandbox.mcf failed.\n";
    }else{
    //parse success

    //if (load.KeyExists("resources","rscount"))
    //for (int i=0;i<load.GetVar("resources","rscount")->GetInt();i++)
    //    {
    //        std::string temp = "rs";
    //        std::stringstream ss;
    //        ss<<i;
    //        temp.append(ss.str());
    //        if (load.KeyExists("resources",temp))
    //            try{
    //               std::cout<<"Assuming no exception, added file "<<"resource/"<<load.GetVar("resources",temp)->GetString()<<"\n";
    //                Resource::AddFile("resource/"+load.GetVar("resources",temp)->GetString());
    //           }
    //            catch(Exception e)
    //            {
    //                e.output();
    //            }

    //     }


        if (load.KeyExists("resources","dir")){
            std::cout<<"adding "<<load.GetVar("resources","dir")->GetString()<<" recursively\n";
        Resource::AddDir(load.GetVar("resources","dir")->GetString()+"/",true);
        }
    }
    //create a world on startup (for now)
    Access()->SelectWorld(Access()->AddUndefinedWorld());//add a new undefined world, and select it

}

//HOOKS ABOVE
//EVENTS BELOW

bool WorldManager::Event_KeyReleased(sf::Event evt){

     if (evt.Key.Code == sf::Keyboard::LControl)
     {


         Access()->CurrentWorld()->AddShape(new Entity(EntityInfo::Bullet,new EntityDimensions("rect",5,5,sf::Mouse::GetPosition().x,sf::Mouse::GetPosition().y)));
     }




    if (evt.Key.Code == sf::Keyboard::Num1)
    {
        Access()->CurrentWorld()->SetCurrentMaterial(new Material(MatType::Default));
    }else if (evt.Key.Code == sf::Keyboard::Num2)
    {
        Access()->CurrentWorld()->SetCurrentMaterial(new Material(MatType::Heavy));
    }else if (evt.Key.Code == sf::Keyboard::Num3)
    {
        Access()->CurrentWorld()->SetCurrentMaterial(new Material(MatType::Light));
    }else if (evt.Key.Code == sf::Keyboard::Num4)
    {
        Access()->CurrentWorld()->SetCurrentMaterial(new Material(MatType::Rubber));
    }else if (evt.Key.Code == sf::Keyboard::Num5)
    {
        Access()->CurrentWorld()->SetCurrentMaterial(new Material(2,0.5f,0.3f,"image/tire.png"));
    }


    if (evt.Key.Code == sf::Keyboard::Num0)
    {
        World* temp = Access()->CurrentWorld();
        Access()->HideWorld(temp);
        Access()->SelectWorld(Access()->AddUndefinedWorld());//autoselects it too...
    }

    if (evt.Key.Code == sf::Keyboard::Slash)
    {
        Access()->CurrentWorld()->SetTimestep(1.0f / 40.0f);
    }


    if (evt.Key.Code == sf::Keyboard::End)
    {
        Access()->CurrentWorld()->AwakenAll();
        Access()->CurrentWorld()->SetGravity(b2Vec2(0.0f,0.0f));
    }

    if (evt.Key.Code == sf::Keyboard::Up)
    {
        Access()->CurrentWorld()->AwakenAll();
        Access()->CurrentWorld()->SetGravity(b2Vec2(0.0f,-10.0f));
    }

    if (evt.Key.Code == sf::Keyboard::Down)
    {
        Access()->CurrentWorld()->AwakenAll();
        Access()->CurrentWorld()->SetGravity(b2Vec2(0.0f,10.0f));
    }

    if (evt.Key.Code == sf::Keyboard::Left)
    {
        Access()->CurrentWorld()->AwakenAll();
        Access()->CurrentWorld()->SetGravity(b2Vec2(-10.0f,0.0f));
    }

    if (evt.Key.Code == sf::Keyboard::Right)
    {
        Access()->CurrentWorld()->AwakenAll();
        Access()->CurrentWorld()->SetGravity(b2Vec2(10.0f,0.0f));
    }


    return true;
}

bool WorldManager::Event_KeyPresed(sf::Event evt){

  if (evt.Key.Code == sf::Keyboard::Comma)
    {
        if(Access()->CurrentWorld()->GetTimestep() > WorldStandards::minSpeed){
        Access()->CurrentWorld()->SetTimestep(Access()->CurrentWorld()->GetTimestep()-(1.0f / 1000.0f));
        }
    }

    if (evt.Key.Code == sf::Keyboard::Period)
    {

        if(Access()->CurrentWorld()->GetTimestep() < WorldStandards::maxSpeed)
        Access()->CurrentWorld()->SetTimestep(Access()->CurrentWorld()->GetTimestep()+(1.0f / 1000.0f));
    }


    return true;
}


bool WorldManager::Event_MouseButtonPressed(sf::Event evt)
{

    Access()->Init_Mouse = b2Vec2(evt.MouseButton.X,evt.MouseButton.Y);
    return true;
}

bool WorldManager::Event_MouseButtonReleased(sf::Event evt)
{
    int radius = 5;
    int i=0; //if for is commented out, just do this for now.
    int w = radius*2;
     int h = w;
     int tHeight=w;

    Access()->Released_Mouse = b2Vec2(evt.MouseButton.X,evt.MouseButton.Y);

    if (!Access()->has_clicked)
    Access()->has_clicked=true;//now player has cliked (achieves)





    b2Vec2 force = b2Vec2(WorldStandards::rgrav_forceConst*(Access()->Released_Mouse.x-Access()->Init_Mouse.x), WorldStandards::rgrav_forceConst*(Access()->Released_Mouse.y-Access()->Init_Mouse.y));

                    if(force.x < 0){
                        if(force.x < -30){
                            force = b2Vec2(-30, force.y);
                        }
                    }else{
                        if(force.x > 30){
                            force = b2Vec2(30, force.y);
                        }
                    }

                    if(force.y < 0){
                        if(force.y < -30){
                            force = b2Vec2(force.x, -30);
                        }
                    }else{
                        if(force.y > 30){
                            force = b2Vec2(force.x, 30);
                        }
                    }

                    //std::cout << "X: " << force.x << " Y: " << force.y << std::endl;




         if (evt.MouseButton.Button == sf::Mouse::Left){
                //for(int i=0; i<100; i++) //difference released-init

                Access()->CurrentWorld()->AddShape(new Entity(EntityInfo::Circle,new EntityDimensions(5,sf::Mouse::GetPosition().x,sf::Mouse::GetPosition().y)));
         }
         if (evt.MouseButton.Button == sf::Mouse::Right)
            //for(int i=0; i<100; i++)
                Access()->CurrentWorld()->AddShape(new Entity(EntityInfo::Rect,new EntityDimensions("rect",10,10,sf::Mouse::GetPosition().x,sf::Mouse::GetPosition().y)));



    return true;

}

bool WorldManager::Event_MouseWheelMoved(sf::Event evt)
{

        int radius = 10;
    int i=0; //if for is commented out, just do this for now.
    int w = radius*2;
     int h = w;
     int tHeight=w;


        for(int i=0; i<5; i++)
        Access()->CurrentWorld()->AddShape(new Entity(EntityInfo::Circle,new EntityDimensions(radius,sf::Mouse::GetPosition().x-tHeight+i*tHeight,sf::Mouse::GetPosition().y-tHeight),new Material(2,0.5f,0.3f,"image/sandbox/tire.png")));


    return true;
}

bool WorldManager::Event_MouseMoved(sf::Event evt)
{
    return true;
}


//EVENTS ABOVE
//ACHEIVES BELOW

bool WorldManager::Achievement_Conditions(sf::Event evt)
{
    if (evt.Type == sf::Event::MouseButtonReleased)
        {
            if (Access()->has_clicked)
                std::cout<<"Clicked via achievs";
            else
                return false;
        }
}

void WorldManager::Achievement_Completion(std::string name)
{
    std::cout<<"[WorldManager][Achievement_Completion] Congrats! You completed "<<name<<"!\n";
}
*/
