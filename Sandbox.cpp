#include "Sandbox.h"

Sandbox* Sandbox::m_ptr = NULL;

Sandbox::Sandbox()
{
    WriteWorldStandardsFromConfig("resource/config/sandbox.mcf");


    //ctor
    m_curuuid=0;
    defaultconstraint=500;




    //the hooked hooks
    Renderer::Hooks()->Register(Hook::Frame,&Sandbox::Renderer_Frame_Hook);
    Magnet::Hooks()->Register(Hook::Setup,&Sandbox::Magnet_Load_Hook);

    //all our events
    EventHandler::AddListener(new EventListener(sf::Event::MouseButtonReleased, &Sandbox::Event_MouseButtonReleased));
    EventHandler::AddListener(new EventListener(sf::Event::MouseButtonPressed, &Sandbox::Event_MouseButtonPressed));
    EventHandler::AddListener(new EventListener(sf::Event::MouseWheelMoved, &Sandbox::Event_MouseWheelMoved));
    EventHandler::AddListener(new EventListener(sf::Event::KeyReleased,&Sandbox::Event_KeyReleased));
    EventHandler::AddListener(new EventListener(sf::Event::MouseMoved, &Sandbox::Event_MouseMoved));
    EventHandler::AddListener(new EventListener(sf::Event::KeyPressed,&Sandbox::Event_KeyPresed));

    //Magnet::Achieves()->Register(new Achievement("World_Mouse_Click","You learned to click the screen!",&Sandbox::Achievement_Completion),new EventListener(sf::Event::MouseButtonReleased,&Sandbox::Achievement_Conditions));

    //init mouseposes
    Released_Mouse = b2Vec2(0,0);
    Init_Mouse = b2Vec2(0,0);



}


void Sandbox::SelectWorld(World* in)
{
    std::list<World*>::iterator it;
    for (it=m_WorldList.begin();it != m_WorldList.end();it++)
    {

        if ((*it)->uuid == in->uuid)
            m_curWorld = (*it);

    }

}

World* Sandbox::GetWorld(World* in)
{
    std::list<World*>::iterator it;
        for (it=m_WorldList.begin();it != m_WorldList.end();it++)
        {

            if ((*it)->uuid == in->uuid)
                return (*it);

        }
}

void Sandbox::Remove(World* in)
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


Sandbox::~Sandbox()
{
    //dtor
}

void Sandbox::Init()
{
    m_ptr = new Sandbox();
}

Sandbox* Sandbox::Access()
{
    if (!m_ptr)
        std::cout<<"[Sandbox][Access] Returning NULL PTR.\n";

    return m_ptr;
}

World* Sandbox::CurrentWorld()
{
  if (!m_curWorld)
    std::cout<<"[Sandbox][CurrentWorld] Returning NULL PTR.\n";

  return m_curWorld;
}

//**HOOKS BELOW**/

void Sandbox::Renderer_Frame_Hook()
{

    if (Access()->CurrentWorld())
    Access()->CurrentWorld()->Step();
}

void Sandbox::Magnet_Load_Hook()
{


    //parse the resources sandbox needs loaded
    Config load;
    CfgParse cfgparser("resource/config/sandbox.mcf");
    cfgparser.Parse(load);
    if(!cfgparser.IsParsed()){
        if (WorldStandards::debug)
            std::cout<<"Parsing Sandbox.mcf failed.\n";
    }else{
        if (load.KeyExists("resources","dir"))
        {
            std::cout<<"adding "<<load.GetKeyObject("resources","dir")->GetString()<<" recursively\n";
            Resource::AddDir(load.GetKeyObject("resources","dir")->GetString()+"/",true);
        }
    }
    //create a world on startup (for now)
    Access()->SelectWorld(Access()->AddUndefinedWorld());//add a new undefined world, and select it

}

//**HOOKS ABOVE**/
//**EVENTS BELOW**/

bool Sandbox::Event_KeyReleased(sf::Event evt){

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

bool Sandbox::Event_KeyPresed(sf::Event evt){

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


bool Sandbox::Event_MouseButtonPressed(sf::Event evt)
{

    Access()->Init_Mouse = b2Vec2(evt.MouseButton.X,evt.MouseButton.Y);
    return true;
}

bool Sandbox::Event_MouseButtonReleased(sf::Event evt)
{
    int radius = 5;
    int i=0; //if for is commented out, just do this for now.
    int w = radius*2;
    int h = w;
    int tHeight=w;

    Access()->Released_Mouse = b2Vec2(evt.MouseButton.X,evt.MouseButton.Y);






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

bool Sandbox::Event_MouseWheelMoved(sf::Event evt)
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

bool Sandbox::Event_MouseMoved(sf::Event evt)
{
    return true;
}


//**EVENTS ABOVE**/
//**ACHEIVES BELOW**/

bool Sandbox::Achievement_Conditions(sf::Event evt)
{

}

void Sandbox::Achievement_Completion(std::string name)
{
    std::cout<<"[Sandbox][Achievement_Completion] Congrats! You completed "<<name<<"!\n";
}



void Sandbox::WriteWorldStandardsFromConfig(std::string path)
{

    Config load;
    CfgParse cfgparser(path.c_str());
    cfgparser.Parse(load);
    if(cfgparser.IsParsed()){

        if (load.KeyExists("standards","ratio"))
         WorldStandards::ratio = load.GetKeyObject("standards","ratio")->GetFloat();
        if (load.KeyExists("standards","ppm"))
         WorldStandards::ppm = load.GetKeyObject("standards","ppm")->GetFloat();
        if (load.KeyExists("standards","mpp"))
         WorldStandards::mpp = load.GetKeyObject("standards","mpp")->GetFloat();
        if (load.KeyExists("standards","unratio"))
         WorldStandards::unratio = load.GetKeyObject("standards","unratio")->GetFloat();
        if (load.KeyExists("standards","degtorad"))
         WorldStandards::degtorad = load.GetKeyObject("standards","degtorad")->GetFloat();
        if (load.KeyExists("standards","radtodeg"))
         WorldStandards::radtodeg = load.GetKeyObject("standards","radtodeg")->GetFloat();
        if (load.KeyExists("standards","debug"))
         WorldStandards::debug = load.GetKeyObject("standards","debug")->GetBool();
        if (load.KeyExists("standards","debug_step"))
         WorldStandards::debug_step = load.GetKeyObject("standards","debug_step")->GetBool();
        if (load.KeyExists("standards","rgrav_forceConst"))
         WorldStandards::rgrav_forceConst = load.GetKeyObject("standards","rgrav_forceConst")->GetFloat();
        if (load.KeyExists("standards","minSpeed"))
         WorldStandards::minSpeed = load.GetKeyObject("standards","minSpeed")->GetFloat();
        if (load.KeyExists("standards","maxSpeed"))
         WorldStandards::maxSpeed = load.GetKeyObject("standards","maxSpeed")->GetFloat();

    }else{

    if (WorldStandards::debug)
        std::cout<<"Failure To Load sandbox.cfg, though not to worry, WorldStandards will use defaults.\n";

    }
}

