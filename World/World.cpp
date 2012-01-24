#include "World.h"

//!-----


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
    maxPhysicsBodies = 1000;

    //mousevector generation
    m_MouseVector1 = b2Vec2(-1,-1);
    m_MouseVector2 = b2Vec2(-1,-1);

    if (WorldStandards::debug)
        std::cout<<"[World] [Init] Hooked. \n";

    Renderer::Hooks()->Register(Hook::Frame,&World::HookHelper);
    Magnet::Hooks()->Register(Hook::Setup,&World::Hook_Setup);

    EventHandler::AddListener(new EventListener(sf::Event::MouseButtonReleased, &World::Event_Click));
    EventHandler::AddListener(new EventListener(sf::Event::MouseWheelMoved, &World::Event_Click));



    EventHandler::AddListener(new EventListener(sf::Event::MouseMoved, &World::Event_MouseMove));
    EventHandler::AddListener(new EventListener(sf::Event::KeyPressed,&World::Event_KeyPresed));

    m_curMat = new Material();
    //temp material msg
    sf::String* msg = new sf::String("Materials = 1,2(HVY),3(LGT),4(RBR),5(WOOD)");
    msg->SetPosition(540,10);
    Renderer::CreateLink(msg);
    //--

    m_hooked=true;

    Stat = new WorldStats(m_world1);

    Stat->ShowFps(10, 0);
    Stat->ShowWorldCount(10, 24);




    //this should create an XmlParse and iterate its multimap
    XmlParse xml("resource\\config\\AnimDemo.xml");
    xml.Parse(); //set the parsed data
    for (xml.Iterator=xml.Parse().begin() ; xml.Iterator != xml.Parse().end() ; xml.Iterator++ )
    {

        std::cout<<(*xml.Iterator).first<<" contains "<<(*xml.Iterator).second<<"\n";
    }

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

void World::Step()
{

    //stores erases for this step, clears before step ends
    std::vector<PhysShape*> EraseQueue;

    bool mpb_notchecked=true; //used to stop constant deletion when > maxPhysicsBodies (reset each Step)


    if ((WorldStandards::debug)&&(WorldStandards::debug_step))
        std::cout<<"[System] [Step] Stepping now...\n";


    //step world
    Access()->CurrentWorld()->Step(Access()->m_timeStep, Access()->m_velocityIterations, Access()->m_positionIterations);


    //do remapping for sfml, and process creation of deletion commands.
    for (int i=0;i<Access()->Objects.size();i++)
    {

        //get b2Body info
        float b2posx = Access()->Objects[i]->Get_Body()->GetPosition().x;
        float b2posy = Access()->Objects[i]->Get_Body()->GetPosition().y;
        float b2rot  = Access()->Objects[i]->Get_Body()->GetAngle();

        if ((WorldStandards::debug)&&(WorldStandards::debug_step))
        {
            std::cout<<"[System] [Step] [ObjectInfo] MassData.mass = "<< Access()->Objects[i]->Get_Body()->GetMass() <<".\n";
        }

        //create new angle for sf::Shape
        float deg = b2rot * WorldStandards::radtodeg;
        float alreadyrot = Access()->Objects[i]->Get_Shape()->GetRotation();
        float newrot = (-1*b2rot) * WorldStandards::radtodeg;
        float rot= newrot - alreadyrot ;

        //update sfml positions via ratio, so they are pixels, not b2 mkz units
        float sfposx = b2posx*WorldStandards::mpp;
        float sfposy = b2posy*WorldStandards::mpp;


        //if a shape.Position is inside the worldConstraints, update info, else deelte it
        if ((worldConstraint[0].x<sfposx)&&(sfposx<worldConstraint[1].x)&&(worldConstraint[0].y<sfposy)&&(sfposy<worldConstraint[1].y))
        {

                    Access()->Objects[i]->Set_Position(sf::Vector2f(sfposx,sfposy));
                    Access()->Objects[i]->Set_Angle(rot);
                    Access()->Objects[i]->Update();

        }else{

               EraseQueue.push_back(Access()->Objects[i]);
                if (WorldStandards::debug)
                        std::cout<<"[System] [Step] [Erase] Shape Erase Chained. \n";


        }


        if ((Access()->Objects.size() > Access()->maxPhysicsBodies)&&(mpb_notchecked))
        {   mpb_notchecked=false;

            for (int a=0;a<Access()->Objects.size()-Access()->maxPhysicsBodies;a++)//11 at a time from the front
            EraseQueue.push_back(Objects[a]);


            if (WorldStandards::debug)
                        std::cout<<"[System] [Step] [Erase] Shape(s) Erase Chained. \n";

        }

    }

        //add objects.
    ProcessQueue(&Access()->Queue,"create");


    //destroy objects.
    ProcessQueue(&EraseQueue,"destroy");


//to see world bodies count at pos 10,10
Stat->UpdateWorldCount(10,24);
Stat->UpdateFps(10,0);

}


void World::ProcessQueue(std::vector<PhysShape*>* Q,std::string fx)
{


    if (fx == "destroy")
    {

        for (int i =0; i<Q->size(); i++)
        {
            //iterate Q, match Q's PhysShape to an Objects, and destroy it, and erase the Objects.
            for (int a=0;a<Access()->Objects.size();a++)
            {
                if (Q->at(i) == Objects[a]){
                    Objects[a]->Destroy();
                    Objects.erase(Objects.begin() + a);
                    }
            }

        }
        Q->clear();

    }else if (fx == "create")
    {
        for (int i =0; i< Q->size(); i++)
        {
            //iterate Q, calling each PhysShapes create.
            Q->at(i)->Create();
            //only add nonstatics
            if (!Q->at(i)->Get_Static())
                Access()->Objects.push_back(Q->at(i));
        }

        Q->clear();
    }else{

        if (WorldStandards::debug)
            std::cout<<"[World] [Process] Invalid fx.\n";

    }


}



void World::HookHelper()
{
    Access()->Step();
}

void World::AddShape(PhysShape* shape){
    World::Access()->Queue.push_back(shape);
}

void World::Hook_Setup()
{

    //add our demo-world-scape
     World::Access()->Queue.push_back(new Rect(400,100,true,sf::Vector2f(0,1000), new Material(MatType::Floor),340));
     World::Access()->Queue.push_back(new Rect(400,100,true,sf::Vector2f(400,1000), new Material(MatType::Floor)));
     World::Access()->Queue.push_back(new Circle(50,true,sf::Vector2f(600,550), new Material(MatType::Floor)));
     World::Access()->Queue.push_back(new Rect(460,100,true,sf::Vector2f(1033,1350), new Material(MatType::Floor),310));
     World::Access()->Queue.push_back(new Rect(400,100,true,sf::Vector2f(1500,1700), new Material(MatType::Floor)));
     World::Access()->Queue.push_back(new Rect(400,100,true,sf::Vector2f(1900,1700), new Material(MatType::Floor),30));
     World::Access()->Queue.push_back(new Line(310,100,600,200));
     World::Access()->Queue.push_back(new Line(120,390,700,240));
     World::Access()->Queue.push_back(new Line(700,180,700,240));
     //World::Access()->Queue.push_back(new Line(100,390,320,390));
     World::Access()->Queue.push_back(new Line(32,435,10,200));





}
//sf::Vector2f pos1,sf::Vector2f pos2,sf::Vector2f pos3,sf::Vector2f Globalpos

void World::SetTimestep(float in)
{
    m_timeStep = in;
}

float World::GetTimestep()
{
    return m_timeStep;
}

bool World::Event_KeyPresed(sf::Event evt){
    if(evt.Key.Code == sf::Key::Num1)
        World::Default(evt);

    if(evt.Key.Code == sf::Key::Num2)
        World::Heavy(evt);

    if(evt.Key.Code == sf::Key::Num3)
        World::Light(evt);

    if(evt.Key.Code == sf::Key::Num4)
        World::Rubber(evt);

    if(evt.Key.Code == sf::Key::Num5)
        World::Wood(evt);

    return true;
}


bool World::Event_Click(sf::Event evt)
{
    int radius = 5;
    int i=0; //if for is commented out, just do this for now.
    int w = radius*2;
     int h = w;
     int tHeight=w;

    if(evt.Type == sf::Event::MouseButtonReleased){
     if (evt.MouseButton.Button == sf::Mouse::Left)
            //for(int i=0; i<100; i++)
                Access()->Queue.push_back(new Circle(radius,sf::Vector2f(evt.MouseButton.X-radius+i*radius,evt.MouseButton.Y-radius),Access()->CurrentMaterial()));

     if (evt.MouseButton.Button == sf::Mouse::Right)
        //for(int i=0; i<100; i++)
            Access()->Queue.push_back(new Rect(w,h,sf::Vector2f(evt.MouseButton.X-w+i*w,evt.MouseButton.Y-h),Access()->CurrentMaterial()));

     if (evt.MouseButton.Button == sf::Mouse::Middle)
        //for(int i=0; i<100; i++)
            Access()->Queue.push_back(new Triangle(tHeight,sf::Vector2f(evt.MouseButton.X-tHeight+i*tHeight,evt.MouseButton.Y-tHeight),Access()->CurrentMaterial()));
    }else{
        const sf::Input& inpt = Renderer::GetRenderWindow()->GetInput();
        for(int i=0; i<5; i++)
        Access()->Queue.push_back(new Circle(radius,sf::Vector2f(inpt.GetMouseX()-tHeight+i*tHeight,inpt.GetMouseY()-tHeight),Access()->CurrentMaterial()));

    }



    return true;

}




/* MATERIAL SELECTOR STUFF */
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


bool World::Event_MouseMove(sf::Event evt)
{
    int curx = evt.MouseButton.X;
    int cury = evt.MouseButton.Y;

    if ((Access()->m_MouseVector1.x == -1)&&(Access()->m_MouseVector1.y == -1))
    {
        Access()->m_MouseVector1.x = curx;
        Access()->m_MouseVector1.y = cury;
    }else
    {
        if ((Access()->m_MouseVector2.x == -1)&&(Access()->m_MouseVector2.y == -1))
        {
            Access()->m_MouseVector2.x = curx;
            Access()->m_MouseVector2.y = cury;
        }else
        {
            Access()->m_MouseVector1.x = -1;
            Access()->m_MouseVector1.y = -1;
            Access()->m_MouseVector2.x = -1;
            Access()->m_MouseVector2.y = -1;
            //reset.
        }

    }

return true;
}
