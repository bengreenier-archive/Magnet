#include "WorldManager.h"

WorldManager* WorldManager::m_ptr = NULL;

WorldManager::WorldManager()
{
    //ctor
    m_curuuid=0;
    defaultconstraint=500;

    //achievs
    has_clicked=false;//player hasn't clicked originally

    //so that there is always at least one world, to prevent glitches
    AddUndefinedWorld();

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
    Magnet::Achieves()->Register(new Achievement("World_Mouse_Click","You learned to click the screen!",&WorldManager::Achievement_Completion),new EventListener(sf::Event::MouseButtonReleased,&WorldManager::Achievement_Conditions));

    //init mouseposes
    Released_Mouse = b2Vec2(0,0);
    Init_Mouse = b2Vec2(0,0);

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

//**HOOKS BELOW**/

void WorldManager::Renderer_Frame_Hook()
{
    if (Access()->CurrentWorld())
    Access()->CurrentWorld()->Step();
}

void WorldManager::Magnet_Load_Hook()
{
    //for now, we will add our demo-scape to the currentworld on load hook


}

//**HOOKS ABOVE**/
//**EVENTS BELOW**/
bool WorldManager::Event_KeyReleased(sf::Event evt){

     if (evt.Key.Code == sf::Key::LControl)
     {
         const sf::Input& inpt = Renderer::GetRenderWindow()->GetInput();
         std::cout<<inpt.GetMouseX()<<","<<inpt.GetMouseY()<<"\n";
         Access()->CurrentWorld()->AddShape(new Projectile(sf::Vector2f(inpt.GetMouseX(),inpt.GetMouseY()),b2Vec2(0,50)));
     }




    if (evt.Key.Code == sf::Key::Num1)
    {
        Access()->CurrentWorld()->SetCurrentMaterial(new Material(MatType::Default));
    }else if (evt.Key.Code == sf::Key::Num2)
    {
        Access()->CurrentWorld()->SetCurrentMaterial(new Material(MatType::Heavy));
    }else if (evt.Key.Code == sf::Key::Num3)
    {
        Access()->CurrentWorld()->SetCurrentMaterial(new Material(MatType::Light));
    }else if (evt.Key.Code == sf::Key::Num4)
    {
        Access()->CurrentWorld()->SetCurrentMaterial(new Material(MatType::Rubber));
    }else if (evt.Key.Code == sf::Key::Num5)
    {//float density,float rest,float fric,std::string path,std::string name
        Access()->CurrentWorld()->SetCurrentMaterial(new Material(2,0.5f,0.3f,"image/tire.png","Tire"));
    }

    //for demo purposes only!!
    if (evt.Key.Code == sf::Key::Num0)
    {
        World* temp = Access()->CurrentWorld();
        Access()->AddUndefinedWorld();//autoselects it too...
        Access()->HideWorld(temp);
    }

    if (evt.Key.Code == sf::Key::Num6)
    {
        //when making repellers/radial gravity, the bVec2(should be 0,-1 push or 0,1 pull) for now
        Access()->CurrentWorld()->AddShape(new Circle(50,b2Vec2(0,1),500,false,sf::Vector2f(300,300), new Material(MatType::Floor)));
        //Access()->CurrentWorld()->AddShape(new Circle(50,b2Vec2(0,1),500,true,sf::Vector2f(900,300), new Material(MatType::Floor)));
        //Access()->CurrentWorld()->AddShape(new Circle(50,b2Vec2(0,-1),500,true,sf::Vector2f(600,50), new Material(MatType::Rubber)));
        //Access()->CurrentWorld()->AddShape(new Circle(50,b2Vec2(0,-1),500,true,sf::Vector2f(600,550), new Material(MatType::Rubber)));
    }


    if (evt.Key.Code == sf::Key::Num9)
    {
            Access()->CurrentWorld()->AddShape(new Rect(400,100,true,sf::Vector2f(0,1000), new Material(MatType::Floor),340));
            Access()->CurrentWorld()->AddShape(new Rect(400,100,true,sf::Vector2f(400,1000), new Material(MatType::Floor)));
            Access()->CurrentWorld()->AddShape(new Circle(50,true,sf::Vector2f(600,550), new Material(MatType::Floor)));
            Access()->CurrentWorld()->AddShape(new Rect(460,100,true,sf::Vector2f(1033,1350), new Material(MatType::Floor),310));
            Access()->CurrentWorld()->AddShape(new Rect(400,100,true,sf::Vector2f(1500,1700), new Material(MatType::Floor)));
            Access()->CurrentWorld()->AddShape(new Rect(400,100,true,sf::Vector2f(1900,1700), new Material(MatType::Floor),30));
            Access()->CurrentWorld()->AddShape(new Line(310,100,600,200));
            Access()->CurrentWorld()->AddShape(new Line(120,390,700,240));
            Access()->CurrentWorld()->AddShape(new Line(700,180,700,240));
            Access()->CurrentWorld()->AddShape(new Line(32,435,10,200));
            Access()->CurrentWorld()->AddShape(new Line(32,435,10,200));
    }

    if (evt.Key.Code == sf::Key::Num7)
    {
        Access()->CurrentWorld()->AddShape(new Circle(40,true,sf::Vector2f(288,214),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Circle(60,true,sf::Vector2f(967,349),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Circle(10,true,sf::Vector2f(548,640),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Circle(10,true,sf::Vector2f(1187,150),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Circle(25,true,sf::Vector2f(218,626),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Circle(15,true,sf::Vector2f(1252,627),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Circle(15,true,sf::Vector2f(1252,627),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Circle(15,true,sf::Vector2f(122,57),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Circle(15,true,sf::Vector2f(177,227),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Circle(15,true,sf::Vector2f(135,527),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Circle(15,true,sf::Vector2f(152,427),new Material(MatType::Floor)));

        Access()->CurrentWorld()->AddShape(new Rect(5,10,true,sf::Vector2f(1022,57),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Rect(87,110,true,sf::Vector2f(1477,627),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Rect(7,10,true,sf::Vector2f(735,227),new Material(MatType::Floor)));
        Access()->CurrentWorld()->AddShape(new Circle(34,true,sf::Vector2f(652,827),new Material(MatType::Floor)));


    }

    if (evt.Key.Code == sf::Key::Slash)
    {
        Access()->CurrentWorld()->SetTimestep(1.0f / 40.0f);
    }


    if (evt.Key.Code == sf::Key::End)
    {
        Access()->CurrentWorld()->AwakenAll();
        Access()->CurrentWorld()->SetGravity(b2Vec2(0.0f,0.0f));
    }

    if (evt.Key.Code == sf::Key::Num8)
    {
        Access()->CurrentWorld()->AddShape(new Line(0,0,2000,0));
        Access()->CurrentWorld()->AddShape(new Line(0,0,0,2000));
        Access()->CurrentWorld()->AddShape(new Line(0,873,2000,873));
        Access()->CurrentWorld()->AddShape(new Line(1430,0,1430,2000));
    }

    if (evt.Key.Code == sf::Key::Up)
    {
        Access()->CurrentWorld()->AwakenAll();
        Access()->CurrentWorld()->SetGravity(b2Vec2(0.0f,-10.0f));
    }

    if (evt.Key.Code == sf::Key::Down)
    {
        Access()->CurrentWorld()->AwakenAll();
        Access()->CurrentWorld()->SetGravity(b2Vec2(0.0f,10.0f));
    }

    if (evt.Key.Code == sf::Key::Left)
    {
        Access()->CurrentWorld()->AwakenAll();
        Access()->CurrentWorld()->SetGravity(b2Vec2(-10.0f,0.0f));
    }

    if (evt.Key.Code == sf::Key::Right)
    {
        Access()->CurrentWorld()->AwakenAll();
        Access()->CurrentWorld()->SetGravity(b2Vec2(10.0f,0.0f));
    }


    return true;
}

bool WorldManager::Event_KeyPresed(sf::Event evt){

  if (evt.Key.Code == sf::Key::Comma)
    {
        if(Access()->CurrentWorld()->GetTimestep() > WorldStandards::minSpeed){
        Access()->CurrentWorld()->SetTimestep(Access()->CurrentWorld()->GetTimestep()-(1.0f / 1000.0f));
        }
    }

    if (evt.Key.Code == sf::Key::Period)
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

                    std::cout << "X: " << force.x << " Y: " << force.y << std::endl;




         if (evt.MouseButton.Button == sf::Mouse::Left){
                //for(int i=0; i<100; i++) //difference released-init

                    Access()->CurrentWorld()->AddShape(new Circle(radius,force,sf::Vector2f(evt.MouseButton.X-radius+i*radius,evt.MouseButton.Y-radius),Access()->CurrentWorld()->CurrentMaterial()));
         }
         if (evt.MouseButton.Button == sf::Mouse::Right)
            //for(int i=0; i<100; i++)
                Access()->CurrentWorld()->AddShape(new Rect(w,h,force,sf::Vector2f(evt.MouseButton.X-w+i*w,evt.MouseButton.Y-h),Access()->CurrentWorld()->CurrentMaterial()));



    return true;

}

bool WorldManager::Event_MouseWheelMoved(sf::Event evt)
{

        int radius = 5;
    int i=0; //if for is commented out, just do this for now.
    int w = radius*2;
     int h = w;
     int tHeight=w;


     const sf::Input& inpt = Renderer::GetRenderWindow()->GetInput();
        for(int i=0; i<5; i++)
        Access()->CurrentWorld()->AddShape(new Circle(radius,sf::Vector2f(inpt.GetMouseX()-tHeight+i*tHeight,inpt.GetMouseY()-tHeight),Access()->CurrentWorld()->CurrentMaterial()));

    return true;
}

bool WorldManager::Event_MouseMoved(sf::Event evt)
{
    return true;
}


//**EVENTS ABOVE**/
//**ACHEIVES BELOW**/
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
