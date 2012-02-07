#include "World.h"

//!-----


World::World(int constraint,b2Vec2 m_grav)
{
    //ctor


    m_world1 = new b2World(m_grav);

    if (WorldStandards::debug)
        std::cout<<"[Box2D] World Created Successfully.\n";

    m_selected = m_world1;

    m_hooked = false;

	m_timeStep = 1.0f / 40.0f;
	m_velocityIterations = 8;
	m_positionIterations = 3;

    //world max/min
    worldConstraint[0].x = -constraint; //left
    worldConstraint[0].y = -constraint; //top
    worldConstraint[1].x = constraint + Renderer::GetRenderWindow()->GetWidth();
    worldConstraint[1].y = constraint + Renderer::GetRenderWindow()->GetHeight();

    //max bodies allowed
    maxPhysicsBodies = 800;

    //mousevector generation
    m_MouseVector1 = b2Vec2(-1,-1);
    m_MouseVector2 = b2Vec2(-1,-1);

    if (WorldStandards::debug)
        std::cout<<"[World] [Init] Hooked. \n";


    m_curMat = new Material(MatType::Default);


    m_hooked=true;

    Stat = new WorldStats(m_world1);

    Stat->ShowFps(10, 0);
    Stat->ShowWorldCount(10, 24);

}

b2World* World::CurrentB2World()
{
    return m_selected;
}

void World::Step()
{

    //stores erases for this step, clears before step ends
    std::vector<PhysShape*> EraseQueue;

    bool mpb_notchecked=true; //used to stop constant deletion when > maxPhysicsBodies (reset each Step)


    if ((WorldStandards::debug)&&(WorldStandards::debug_step))
        std::cout<<"[System] [Step] Stepping now...\n";


    //step world
    CurrentB2World()->Step(m_timeStep, m_velocityIterations, m_positionIterations);

    //step StaticObjects for checking Radial gravity
    for (int i=0;i<StaticObjects.size();i++)
    {

        //radial gravity
        if (StaticObjects[i]->HasRadialGravity())
        {
             if ((WorldStandards::debug)&&(WorldStandards::debug_step))
                std::cout<<"[System] [Step] Static Radial Gravity Object!\n";

            b2Vec2 GravityPoint = StaticObjects[i]->Get_Body()->GetWorldCenter();
            float x1 = GravityPoint.x;
            float y1 = GravityPoint.y;

            for (int a=0;a<Objects.size();a++)
            {
                float x2 = Objects[a]->Get_Body()->GetWorldCenter().x;
                float y2 = Objects[a]->Get_Body()->GetWorldCenter().y;

                float dist = std::sqrt(std::pow(x2-x1,2) + std::pow(y2-y1,2));

                if ((dist <= StaticObjects[i]->Get_Radial_Gravity_Distance())&&(StaticObjects[i] != Objects[a]))
                {
                    float slope = (y2-y1)/(x2-x1);
                    float angle = std::tan(slope);//not sure if works everytime
                    b2Vec2 CalculatedForce((StaticObjects[i]->pullorpush_val()*(x1-x2)*WorldStandards::rgrav_forceConst)/dist,(StaticObjects[i]->pullorpush_val()*(y1-y2)*WorldStandards::rgrav_forceConst)/dist);

                    Objects[a]->Get_Body()->ApplyForce(CalculatedForce,Objects[a]->Get_Body()->GetWorldCenter());//apply a force to a's center that moves it toward i
                }

            }

        }

    }

    //do remapping for sfml, and process creation of deletion commands.
    for (int i=0;i<Objects.size();i++)
    {

        //radial gravity
        if (Objects[i]->HasRadialGravity())
        {
             if ((WorldStandards::debug)&&(WorldStandards::debug_step))
                std::cout<<"[System] [Step] Radial Gravity Object!\n";

            b2Vec2 GravityPoint = Objects[i]->Get_Body()->GetWorldCenter();
            float x1 = GravityPoint.x;
            float y1 = GravityPoint.y;

            for (int a=0;a<Objects.size();a++)
            {
                float x2 = Objects[a]->Get_Body()->GetWorldCenter().x;
                float y2 = Objects[a]->Get_Body()->GetWorldCenter().y;

                float dist = std::sqrt(std::pow(x2-x1,2) + std::pow(y2-y1,2));

                if ((dist <= Objects[i]->Get_Radial_Gravity_Distance())&&(Objects[i] != Objects[a]))
                {
                    float slope = (y2-y1)/(x2-x1);
                    float angle = std::tan(slope);//not sure if works everytime
                    b2Vec2 CalculatedForce(Objects[i]->pullorpush_val()*(x1-x2)*WorldStandards::rgrav_forceConst,Objects[i]->pullorpush_val()*(y1-y2)*WorldStandards::rgrav_forceConst);

                    Objects[a]->Get_Body()->ApplyForce(CalculatedForce,Objects[a]->Get_Body()->GetWorldCenter());//apply a force to a's center that moves it toward i
                }

            }

        }


        //if body is asleep, and a bullet, remove it
        if ((Objects[i]->Get_Body()->IsBullet())  &&  (!Objects[i]->Get_Body()->IsAwake()))
                EraseQueue.push_back(Objects[i]);

        //get b2Body info
        float b2posx = Objects[i]->Get_Body()->GetPosition().x;
        float b2posy = Objects[i]->Get_Body()->GetPosition().y;
        float b2rot  = Objects[i]->Get_Body()->GetAngle();

        if ((WorldStandards::debug)&&(WorldStandards::debug_step))
        {
            std::cout<<"[System] [Step] [ObjectInfo] MassData.mass = "<< Objects[i]->Get_Body()->GetMass() <<".\n";
        }

        //create new angle for sf::Shape
        float deg = b2rot * WorldStandards::radtodeg;
        float alreadyrot = Objects[i]->Get_Shape()->GetRotation();
        float newrot = (-1*b2rot) * WorldStandards::radtodeg;
        float rot= newrot - alreadyrot ;

        //update sfml positions via ratio, so they are pixels, not b2 mkz units
        float sfposx = b2posx*WorldStandards::mpp;
        float sfposy = b2posy*WorldStandards::mpp;


        //if a shape.Position is inside the worldConstraints, update info, else deelte it
        if ((worldConstraint[0].x<sfposx)&&(sfposx<worldConstraint[1].x)&&(worldConstraint[0].y<sfposy)&&(sfposy<worldConstraint[1].y))
        {

                    Objects[i]->Set_Position(sf::Vector2f(sfposx,sfposy));
                    Objects[i]->Set_Angle(rot);
                    Objects[i]->Update();

        }else{

               EraseQueue.push_back(Objects[i]);
                if (WorldStandards::debug)
                        std::cout<<"[System] [Step] [Erase] Shape Erase Chained. \n";


        }


        if ((Objects.size() > maxPhysicsBodies)&&(mpb_notchecked))
        {   mpb_notchecked=false;

            for (int a=0;a<Objects.size()-maxPhysicsBodies;a++)//11 at a time from the front
            EraseQueue.push_back(Objects[a]);


            if (WorldStandards::debug)
                        std::cout<<"[System] [Step] [Erase] Shape(s) Erase Chained. \n";

        }

        Objects[i]->Step();//call the virtual step of nonstatic PhysShapes
    }

        //add objects.
    ProcessQueue(&Queue,"create");


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
            for (int a=0;a<Objects.size();a++)
            {
                if (Q->at(i) == Objects[a]){
                    Objects[a]->Destroy(CurrentB2World());
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
            Q->at(i)->Create(CurrentB2World());
            //only add nonstatics
            if (!Q->at(i)->Get_Static())
                Objects.push_back(Q->at(i));
            else
                StaticObjects.push_back(Q->at(i));
        }

        Q->clear();
    }else{

        if (WorldStandards::debug)
            std::cout<<"[World] [Process] Invalid fx.\n";

    }


}

void World::AwakenAll()
{
    //toggle sleeping, so that everything becomes moveable, if only for a second
    CurrentB2World()->SetAllowSleeping(false);
    CurrentB2World()->SetAllowSleeping(true);
}

void World::SetTimestep(float in)
{
    m_timeStep = in;
}

float World::GetTimestep()
{
    return m_timeStep;
}

void World::SetGravity(b2Vec2 in)
{
    m_grav = in;
    CurrentB2World()->SetGravity(m_grav);
}

b2Vec2 World::GetGravity()
{
    return m_grav;
}


Material* World::CurrentMaterial()
{
    return m_curMat;
}

void World::AddShape(PhysShape* in)
{
    Queue.push_back(in);
}

void World::Unload()
{
    std::cout<<"Unload Called!\n";//then it crashes....

    //the problem with this is gunna be how well can Renderer hold up, cause , at least for now imma make a shitton of RemoveLinks really fast
    for (int i=0;i<StaticObjects.size();i++)
    delete StaticObjects[i];


    for (int i=0;i<Objects.size();i++)
    delete Objects[i];

    //now do stats
    Stat->HideAll();

    //then delete other things
    delete Stat;
    delete m_curMat;
    delete m_selected;
    delete m_world1;

}

void World::Hide()
{
    for (int i=0;i<Objects.size();i++)
        Objects[i]->Hide();

    for (int i=0;i<StaticObjects.size();i++)
        StaticObjects[i]->Hide();

    Stat->HideAll();
}
