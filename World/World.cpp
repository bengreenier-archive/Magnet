#include "World.h"

World* World::m_ptr = NULL;

World::World()
{
    //ctor


    m_world1 = new b2World(b2Vec2(0.0f,10.0f));

    if (WorldStandards::debug)
        std::cout<<"[Box2D] World Created Successfully.\n";

    m_selected = m_world1;
    m_hooked = false;

	m_timeStep = 1.0f / 40.0f;
	m_velocityIterations = 8;
	m_positionIterations = 3;

    //world max/min
    worldConstraint[0].x = -500; //left
    worldConstraint[0].y = -500; //top
    worldConstraint[1].x = 500 + Renderer::GetRenderWindow()->GetWidth();
    worldConstraint[1].y = 500 + Renderer::GetRenderWindow()->GetHeight();

    //max bodies allowed
    maxPhysicsBodies = 200;

    if (WorldStandards::debug)
        std::cout<<"[World] [Init] Hooked. \n";

    Magnet::Hooks()->Register(Hook::Frame,&World::HookHelper);
    Magnet::Hooks()->Register(Hook::Setup,&World::Hook_Setup);

    EventHandler::AddEventListener(sf::Event::MouseButtonReleased, &World::ClickCircle);
    EventHandler::AddEventListener(sf::Event::MouseButtonReleased, &World::ClickBox);


    EventHandler::AddKeyListener(sf::Key::Num1,&World::Default);
    EventHandler::AddKeyListener(sf::Key::Num2,&World::Heavy);
    EventHandler::AddKeyListener(sf::Key::Num3,&World::Light);

    EventHandler::AddKeyListener(sf::Key::Num4,&World::Rubber);
    EventHandler::AddKeyListener(sf::Key::Num5,&World::Wood);

    m_curMat = new Material();
    //temp material msg
    sf::String* msg = new sf::String("Materials = 1,2(HVY),3(LGT),4(RBR),5(WOOD)");
    msg->SetPosition(540,10);
    Renderer::CreateLink(msg);
    //--

    m_hooked=true;

    Stat = new WorldStats(m_world1);


}

World* World::Access()
{
    if (!m_ptr)
        std::cout << "[World] [Access]\tWorld has not been initialized! Null pointer returned!\n";
    return m_ptr;

}

void World::Init(){
    m_ptr = new World();
}


b2World* World::CurrentWorld()
{
    return m_selected;
}


sf::Color World::B2SFColor(const b2Color &color, int alpha)
{
	sf::Color result((sf::Uint8)(color.r*255), (sf::Uint8)(color.g*255), (sf::Uint8)(color.b*255), (sf::Uint8) alpha);
	return result;
}


void World::MakeCircle(int radius,sf::Vector2f pos,Material* mat, float degangle)
{
    WorldStorage* temp = new WorldStorage();
    temp->SetParams(radius,pos,mat,degangle);
    cmdqueue.push_back(temp);
}
void World::MakeBox(int width,int height,sf::Vector2f pos,Material* mat, float degangle)
{
    WorldStorage* temp = new WorldStorage();
    temp->SetParams(width,height,pos,mat,degangle);
    cmdqueue.push_back(temp);
}
void World::MakeStaticBox(int width,int height,sf::Vector2f pos,Material* mat, float degangle)
{
    WorldStorage* temp = new WorldStorage();
    temp->SetParams(width,height,pos,mat,degangle);
    temp->MakeStatic();
    cmdqueue.push_back(temp);
}


void World::AddCircle(int radius,sf::Vector2f pos,Material* mat, float degangle)
{
    //
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
    bodyDef.allowSleep = true;
	bodyDef.awake = true;

	bodyDef.position.Set((pos.x+radius)*WorldStandards::ppm, (pos.y+radius)*WorldStandards::ppm);

    bodyDef.angle = (((-1)*degangle)*WorldStandards::degtorad);

	b2Body* bodyBox = Access()->CurrentWorld()->CreateBody(&bodyDef);

	b2CircleShape circle;

	//circle.m_p.Set(2.0f, 3.0f);

	circle.m_radius = radius*WorldStandards::ppm;

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &circle;

    /////add material class in the futurec.
    fixtureDef.density = mat->GetDensity();
    fixtureDef.friction = mat->GetFriction();
    fixtureDef.restitution = mat->GetRestitution();
	//////

	bodyBox->CreateFixture(&fixtureDef);

    //add the body to the list
    Access()->b2PhysicsObjects.push_back(bodyBox);

    if (WorldStandards::debug)
        std::cout << "[Box2D] Added Circle.\n";

    //do sfml
    sf::Shape* cb = new sf::Shape(sf::Shape::Circle(0,0,radius,mat->GetColor()));
    cb->SetPosition(pos);
    //cb->SetCenter(sf::Vector2f(radius, radius));
    cb->Rotate(degangle);

    Renderer::CreateLink(cb);

    //add body to the list
    Access()->sfPhysicsObjects.push_back(cb);

    if (WorldStandards::debug)
        std::cout << "[SFML] Added Circle.\n";

    ActivateHook();//useless really...
}

void World::AddStaticBox(int width,int height,sf::Vector2f pos,Material* mat,float degangle)
{

    //do box2d first..
    b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
    bodyDef.allowSleep = true;
	bodyDef.awake = true;

    //see if this hlps..

	bodyDef.position.Set(((pos.x+width)/2)*WorldStandards::ppm, ((pos.y+height)/2)*WorldStandards::ppm);

    bodyDef.angle = (((-1)*degangle)*WorldStandards::degtorad);

	b2Body* bodyBox = Access()->CurrentWorld()->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;

	dynamicBox.SetAsBox(((width)/2)*WorldStandards::ppm, ((height)/2)*WorldStandards::ppm);

	//fixture stuff
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;

    /////add material class in the futurec.
    //fixtureDef.density = mat->GetDensity();
    //fixtureDef.friction = mat->GetFriction();
    //fixtureDef.restitution = mat->GetRestitution();
	//////

	bodyBox->CreateFixture(&fixtureDef);

    //add the body to the list
    Access()->b2PhysicsObjects.push_back(bodyBox);

    if (WorldStandards::debug)
        std::cout << "[Box2D] Added Static Box.\n";

    //do sfml
    sf::Shape* visibox = new sf::Shape(sf::Shape::Rectangle(0,0,width,height,mat->GetColor()));
    visibox->SetPosition(pos);
    visibox->SetCenter(sf::Vector2f(width/2, height/2));
    visibox->Rotate(degangle);

    Renderer::CreateLink(visibox);

    //add body to the list
    Access()->sfPhysicsObjects.push_back(visibox);

    if (WorldStandards::debug)
        std::cout << "[SFML] Added Static Box.\n";

    ActivateHook();//tell the program to Hook World::Step for us.
}


void World::AddBox(int width,int height,sf::Vector2f pos,Material* mat,float degangle)
{
    //do box2d first..
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
    bodyDef.allowSleep = true;
	bodyDef.awake = true;

    //see if this hlps..

	bodyDef.position.Set(pos.x*WorldStandards::ppm, pos.y*WorldStandards::ppm);

    bodyDef.angle = (((-1)*degangle)*WorldStandards::degtorad);

	b2Body* bodyBox = Access()->CurrentWorld()->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;

	dynamicBox.SetAsBox(((width)/2)*WorldStandards::ppm, ((height)/2)*WorldStandards::ppm);

	//fixture stuff
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;

    /////add material class in the futurec.
    fixtureDef.density = mat->GetDensity();
    fixtureDef.friction = mat->GetFriction();
    fixtureDef.restitution = mat->GetRestitution();
	//////

	bodyBox->CreateFixture(&fixtureDef);

    //add the body to the list
    Access()->b2PhysicsObjects.push_back(bodyBox);

    if (WorldStandards::debug)
        std::cout << "[Box2D] Added dynamic Box.\n";

    //do sfml
    sf::Shape* visibox = new sf::Shape(sf::Shape::Rectangle(0,0,width,height,mat->GetColor()));
    visibox->SetPosition(pos);
    visibox->SetCenter(sf::Vector2f(width/2, height/2));
    visibox->Rotate(degangle);

    Renderer::CreateLink(visibox);

    //add body to the list
    Access()->sfPhysicsObjects.push_back(visibox);

    if (WorldStandards::debug)
        std::cout << "[SFML] Added dynamic Box.\n";

    ActivateHook();//tell the program to Hook World::Step for us.

}



void World::Step()
{

/*
if (!Access()->CurrentWorld()->IsLocked())
    return;
*/

//erasechains (really only need one...)
    std::vector<b2Body*> b2chain;
    std::vector<sf::Drawable*> sfchain;
//--
    bool mpb_notchecked=true;


    if ((WorldStandards::debug)&&(WorldStandards::debug_step))
        std::cout<<"[System] [Step] Stepping now...\n";


    Access()->CurrentWorld()->Step(Access()->m_timeStep, Access()->m_velocityIterations, Access()->m_positionIterations);
    //remap values now... :(


    for (int i=0;i<Access()->b2PhysicsObjects.size();i++)
    {

        float b2posx = Access()->b2PhysicsObjects[i]->GetPosition().x;
        float b2posy = Access()->b2PhysicsObjects[i]->GetPosition().y;
        float b2rot  = Access()->b2PhysicsObjects[i]->GetAngle();

        if ((WorldStandards::debug)&&(WorldStandards::debug_step))
        {
            std::cout<<"[System] [Step] [ObjectInfo] MassData.mass = "<< Access()->b2PhysicsObjects[i]->GetMass() <<".\n";
        }

        float deg = b2rot * WorldStandards::radtodeg;
        float alreadyrot = Access()->sfPhysicsObjects[i]->GetRotation();
        float newrot = (-1*b2rot) * WorldStandards::radtodeg;
        float rot= newrot - alreadyrot ;

        float sfposx = b2posx*WorldStandards::mpp;//(b2posx-(Access()->sfPhysicsObjects[i]->GetWidth()/2))
        float sfposy = b2posy*WorldStandards::mpp;


        if ((worldConstraint[0].x<sfposx)&&(sfposx<worldConstraint[1].x)&&(worldConstraint[0].y<sfposy)&&(sfposy<worldConstraint[1].y))
        {

                    Access()->sfPhysicsObjects[i]->SetPosition(sfposx,sfposy);
                    Access()->sfPhysicsObjects[i]->Rotate(rot);

        }else{
                //erase based on "outside constraints"
                //add positions to erasechains
                //sfchain.push_back(i);
               //b2chain.push_back(i);

                sfchain.push_back(Access()->sfPhysicsObjects[i]);
                b2chain.push_back(Access()->b2PhysicsObjects[i]);

                if (WorldStandards::debug)
                        std::cout<<"[System] [Step] [Erase] Shape Erase Chained. \n";


        }


        if ((Access()->b2PhysicsObjects.size() > Access()->maxPhysicsBodies)&&(mpb_notchecked))
        {   mpb_notchecked=false;
            //add the last position of each (ie pop the front)

            b2Body* temp = FirstNonStatic(Access()->b2PhysicsObjects);
            int tIndex = GetIndexOf(temp);
            sfchain.push_back(Access()->sfPhysicsObjects[tIndex]);
            b2chain.push_back(Access()->b2PhysicsObjects[tIndex]);

            if (WorldStandards::debug)
                        std::cout<<"[System] [Step] [Erase] Shape Erase Chained. \n";

        }

    }


    for (int i=0;i<cmdqueue.size();i++)
    {

    if (cmdqueue[i]->IsType(WorldShape::Circle))
        AddCircle(cmdqueue[i]->GetRadius(),cmdqueue[i]->GetPos(),cmdqueue[i]->GetMat(),cmdqueue[i]->GetAngle());

    if (cmdqueue[i]->IsType(WorldShape::Box))
        AddBox(cmdqueue[i]->GetWidth(),cmdqueue[i]->GetHeight(),cmdqueue[i]->GetPos(),cmdqueue[i]->GetMat(),cmdqueue[i]->GetAngle());

    if (cmdqueue[i]->IsType(WorldShape::StaticBox))
        AddStaticBox(cmdqueue[i]->GetWidth(),cmdqueue[i]->GetHeight(),cmdqueue[i]->GetPos(),cmdqueue[i]->GetMat(),cmdqueue[i]->GetAngle());

    }
        cmdqueue.clear();

    //scroll our erase chains, and execute their stuff.
    for (int i=0;i<sfchain.size();i++)
    {
                Renderer::RemoveLink(Access()->sfPhysicsObjects[GetIndexOf(sfchain[i])]);
                Access()->sfPhysicsObjects.erase(Access()->sfPhysicsObjects.begin()+GetIndexOf(sfchain[i]));

    }

    for (int i=0;i<b2chain.size();i++)
    {
                Access()->CurrentWorld()->DestroyBody(Access()->b2PhysicsObjects[GetIndexOf(b2chain[i])]);
                Access()->b2PhysicsObjects.erase(Access()->b2PhysicsObjects.begin()+GetIndexOf(b2chain[i]));
    }
    //clear them.
    sfchain.clear();
    b2chain.clear();


//to see world bodies count at pos 10,10
Stat->UpdateWorldCount(10,24);
Stat->UpdateFps(10,0);

}


void World::ActivateHook()
{
    //useless....
}


void World::HookHelper()
{
    Access()->Step();
}

int World::GetIndexOf(b2Body* in)
{
    //scroll b2PhysicsObjects until  = in, then return counter/i
    for (int i=0;i<Access()->b2PhysicsObjects.size();i++)
    {
        if (Access()->b2PhysicsObjects[i] == in)
            return i;
    }
    return -1;
}

int World::GetIndexOf(sf::Drawable* in)
{
    //scroll sfPhysicsObjects until  = in, then return counter/i
    for (int i=0;i<Access()->sfPhysicsObjects.size();i++)
    {
        if (Access()->sfPhysicsObjects[i] == in)
            return i;
    }
    return -1;
}

b2Body* World::FirstNonStatic(std::vector <b2Body*> in)
{
    for (int i=0;i<in.size();i++)
    {
        if (in[i]->GetType() == b2_dynamicBody)
            return in[i];
    }
}



void World::Hook_Setup()
{
    World::Access()->MakeBox(10,10,sf::Vector2f(100,100));
    //World::Access()->AddBox(0,0,100,100,sf::Vector2f(230,100), new Material(MatType::Light)) ;
    World::Access()->MakeBox(10,10,sf::Vector2f(100,-10));

    World::Access()->MakeBox(10,10,sf::Vector2f(100,130));

    World::Access()->MakeCircle(10,sf::Vector2f(100,20));

    World::Access()->MakeStaticBox(400,100,sf::Vector2f(0,1000), new Material(MatType::Floor),340);
    World::Access()->MakeStaticBox(400,100,sf::Vector2f(400,1000), new Material(MatType::Floor));
    World::Access()->MakeStaticBox(400,100,sf::Vector2f(980,1400), new Material(MatType::Floor),300);
    World::Access()->MakeStaticBox(400,100,sf::Vector2f(1500,1700), new Material(MatType::Floor),0);
    World::Access()->MakeStaticBox(400,100,sf::Vector2f(1900,1700), new Material(MatType::Floor),30);

    //Renderer::CreateLink(new sf::Shape(sf::Shape::Rectangle(400,500,800,600,sf::Color(255,0,0))),Renderer::HudLayer);
}


void World::SetTimestep(float in)
{
    m_timeStep = in;
}

float World::GetTimestep()
{
    return m_timeStep;
}


void World::ClickBox(sf::Event evt)
{
     const sf::Input& Input = Renderer::GetRenderWindow()->GetInput();
     if (evt.MouseButton.Button == sf::Mouse::Right)
        //if (!Access()->CurrentWorld()->IsLocked())
            Access()->MakeBox(10,10,sf::Vector2f(Input.GetMouseX(),Input.GetMouseY()),Access()->CurrentMaterial());
       // else
        //    std::cout<<"[System] [World] is locked. cannot add box.\n";
}

void World::ClickCircle(sf::Event evt)
{
    int radius = 10;

     const sf::Input& Input = Renderer::GetRenderWindow()->GetInput();
     if (evt.MouseButton.Button == sf::Mouse::Left){
            Access()->MakeCircle(radius,sf::Vector2f(Input.GetMouseX()-radius,Input.GetMouseY()-radius),Access()->CurrentMaterial());
     }
}



Material* World::CurrentMaterial()
{
    return Access()->m_curMat;
}

void World::Default(sf::Event evt)
{
    Access()->m_curMat=new Material(MatType::Default);
}
void World::Heavy(sf::Event evt)
{
    Access()->m_curMat=new Material(MatType::Heavy);
}
void World::Light(sf::Event evt)
{
    Access()->m_curMat=new Material(MatType::Light);
}
void World::Rubber(sf::Event evt)
{
    Access()->m_curMat=new Material(MatType::Rubber);
}
void World::Wood(sf::Event evt)
{
    Access()->m_curMat=new Material(MatType::Wood);
}
