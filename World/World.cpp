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
    m_hooked=true;

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

//erasechains (really only need one...)
    std::vector<int> b2chain;
    std::vector<int> sfchain;
//--



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
                sfchain.push_back(i);
                b2chain.push_back(i);
                if (WorldStandards::debug)
                        std::cout<<"[System] [Step] [Erase] Shape Erase Chained. \n";


        }


        if (Access()->b2PhysicsObjects.size() > Access()->maxPhysicsBodies)
        {
            //add the last position of each (ie pop the last)
            sfchain.push_back(Access()->sfPhysicsObjects.size());
            b2chain.push_back(Access()->b2PhysicsObjects.size());

            if (WorldStandards::debug)
                        std::cout<<"[System] [Step] [Erase] Shape Erase Chained. \n";

        }

    }


    //scroll our erase chains, and execute their stuff.
    for (int i=0;i<sfchain.size();i++)
    {
                Renderer::RemoveLink(Access()->sfPhysicsObjects[sfchain[i]]);
                Access()->sfPhysicsObjects.erase(Access()->sfPhysicsObjects.begin()+sfchain[i]);

    }

    for (int i=0;i<b2chain.size();i++)
    {
                Access()->CurrentWorld()->DestroyBody(Access()->b2PhysicsObjects[b2chain[i]]);
                Access()->b2PhysicsObjects.erase(Access()->b2PhysicsObjects.begin()+b2chain[i]);
    }
    //clear them.
    sfchain.clear();
    b2chain.clear();


}


void World::ActivateHook()
{
    //useless....
}


void World::HookHelper()
{
    Access()->Step();
}



void World::Hook_Setup()
{
    World::Access()->AddBox(10,10,sf::Vector2f(100,100));
    //World::Access()->AddBox(0,0,100,100,sf::Vector2f(230,100), new Material(MatType::Light)) ;
    World::Access()->AddBox(10,10,sf::Vector2f(100,-10));

    World::Access()->AddBox(10,10,sf::Vector2f(100,130));

    World::Access()->AddStaticBox(400,100,sf::Vector2f(0,500), new Material(MatType::Floor),340);
    World::Access()->AddStaticBox(400,100,sf::Vector2f(400,500), new Material(MatType::Floor));
    //Renderer::CreateLink(new sf::Shape(sf::Shape::Rectangle(430,500,830,600,sf::Color(255,0,0))),Renderer::HudLayer);
}


void World::SetTimestep(float in)
{
    m_timeStep = in;
}

float World::GetTimestep()
{
    return m_timeStep;
}
