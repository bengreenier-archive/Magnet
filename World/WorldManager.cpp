#include "WorldManager.h"

WorldManager* WorldManager::m_ptr = NULL;

WorldManager::WorldManager()
{
    //ctor
    m_curuuid=0;
    defaultconstraint=500;

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


    return true;
}

bool WorldManager::Event_KeyPresed(sf::Event evt){



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
    {
        Access()->CurrentWorld()->SetCurrentMaterial(new Material(MatType::Wood));
    }

    //for demo purposes only!!
    if (evt.Key.Code == sf::Key::Num0)
    {
        World* temp = Access()->CurrentWorld();
        Access()->AddUndefinedWorld();//autoselects it too...
        Access()->HideWorld(temp);
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

    return true;
}


bool WorldManager::Event_MouseButtonPressed(sf::Event evt)
{

    return true;
}

bool WorldManager::Event_MouseButtonReleased(sf::Event evt)
{
    int radius = 5;
    int i=0; //if for is commented out, just do this for now.
    int w = radius*2;
     int h = w;
     int tHeight=w;



         if (evt.MouseButton.Button == sf::Mouse::Left)
                //for(int i=0; i<100; i++)
                    Access()->CurrentWorld()->AddShape(new Circle(radius,sf::Vector2f(evt.MouseButton.X-radius+i*radius,evt.MouseButton.Y-radius),Access()->CurrentWorld()->CurrentMaterial()));

         if (evt.MouseButton.Button == sf::Mouse::Right)
            //for(int i=0; i<100; i++)
                Access()->CurrentWorld()->AddShape(new Rect(w,h,sf::Vector2f(evt.MouseButton.X-w+i*w,evt.MouseButton.Y-h),Access()->CurrentWorld()->CurrentMaterial()));



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
