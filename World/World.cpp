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

	m_timeStep = 1.0f / 60.0f;
	m_velocityIterations = 6;
	m_positionIterations = 2;

    //--demo msg
	sf::String* msg = new sf::String("Sposed To Collide...");
	msg->SetPosition(420,100);
	Renderer::CreateLink(msg);
    //--

    if (WorldStandards::debug)
        std::cout<<"[World] [Init] Hooked. \n";

    Magnet::Hooks()->Register(Hook::Frame,&World::HookHelper);
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


void World::AddStaticBox(int x,int y,int x2,int y2,sf::Vector2f pos)
{
    //do box2d first..
    b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.allowSleep = true;
	bodyDef.awake = true;
	bodyDef.position.Set(pos.x*WorldStandards::unratio, pos.y*WorldStandards::unratio);
	bodyDef.angle = 0*WorldStandards::degtorad;
	b2Body* bodyBox = Access()->CurrentWorld()->CreateBody(&bodyDef);
	b2PolygonShape staticBox;
	staticBox.SetAsBox(((x2-x)/2)*WorldStandards::unratio, ((y2-y)/2)*WorldStandards::unratio);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
    fixtureDef.density = 0;


	bodyBox->CreateFixture(&fixtureDef);

    //add the body to the list
    Access()->b2PhysicsObjects.push_back(bodyBox);

    if (WorldStandards::debug)
        std::cout << "[Box2D] Added static Box.\n";

    //do sfml
    sf::Shape* visibox = new sf::Shape(sf::Shape::Rectangle(x,y,x2,y2,sf::Color(21,0,255))); //create a new rect with color red (for now)
    visibox->SetPosition(pos);

    Renderer::CreateLink(visibox);

    //add body to the list
    Access()->sfPhysicsObjects.push_back(visibox);

    if (WorldStandards::debug)
        std::cout << "[SFML] Added static Box.\n";

    ActivateHook();//tell the program to Hook World::Step for us.
}


void World::AddBox(int x,int y,int x2,int y2,sf::Vector2f pos)  //a sort of trial function , to make sure were getting basic physics.
{
    //do box2d first..
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
    bodyDef.allowSleep = true;
	bodyDef.awake = true;

    //see if this hlps..
    bodyDef.bullet = true;

	bodyDef.position.Set(pos.x*WorldStandards::unratio, pos.y*WorldStandards::unratio);

	bodyDef.angle = 0;

	b2Body* bodyBox = Access()->CurrentWorld()->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;

	dynamicBox.SetAsBox(((x2-x)/2)*WorldStandards::unratio, ((y2-y)/2)*WorldStandards::unratio);

	//fixture stuff
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;

    /////add material class in the futurec.
    fixtureDef.density = 1.00f;
    fixtureDef.friction = 0.30f;
    fixtureDef.restitution = 0.2f;
	//////
	bodyBox->CreateFixture(&fixtureDef);

    //add the body to the list
    Access()->b2PhysicsObjects.push_back(bodyBox);

    if (WorldStandards::debug)
        std::cout << "[Box2D] Added dynamic Box.\n";

    //do sfml
    sf::Shape* visibox = new sf::Shape(sf::Shape::Rectangle(x,y,x2,y2,sf::Color(255,0,0))); //create a new rect with color red (for now)
    visibox->SetPosition(pos);

    Renderer::CreateLink(visibox);

    //add body to the list
    Access()->sfPhysicsObjects.push_back(visibox);

    if (WorldStandards::debug)
        std::cout << "[SFML] Added dynamic Box.\n";

    ActivateHook();//tell the program to Hook World::Step for us.

}



void World::Step()
{

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
            std::cout<<"[System] [Step] [ObjectInfo] MassData.mass = "<< Access()->b2PhysicsObjects[i]->GetMass() <<".\n";

        Access()->sfPhysicsObjects[i]->SetPosition(b2posx*WorldStandards::ratio,b2posy*WorldStandards::ratio);
        Access()->sfPhysicsObjects[i]->Rotate(b2rot * WorldStandards::radtodeg);

    }




}


void World::ActivateHook()
{/*
 std::vector<World*>::iterator it;
    bool found = false;

    for (it=Access()->worldList.begin();it<Access()->worldList.end();it++)
    {
        if ((*it)==Access()){
            found=true;
        }
    }

    if (!found)
    {
        Ptr()->Access()->worldList.push_back(Access()); //add our world to this list... ?
            if (WorldStandards::debug)
                std::cout<<"[System] [ActivateHook] Added to worldList. \n";

            Magnet::Hooks()->Register(Hook::Frame,&World::HookHelper);

    }

*/

/*
    if (!Access()->m_hooked)
    {
        if (WorldStandards::debug)
                std::cout<<"[System] [ActivateHook] Hooked. \n";

        Magnet::Hooks()->Register(Hook::Frame,&World::HookHelper);
        Access()->m_hooked=true;
    }else{
        if (WorldStandards::debug)
                std::cout<<"[System] [ActivateHook] Already hooked. \n";

    }*/
}


void World::HookHelper()
{
/*
    std::vector<World*>::iterator it;

    for (it = Ptr()->Access()->worldList.begin();it<Ptr()->Access()->worldList.end();it++)
    {
        (*it)->Step(); //step each world in worldList
    }
*/

Access()->Step();
}
