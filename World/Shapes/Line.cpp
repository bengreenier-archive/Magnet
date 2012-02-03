#include "Line.h"
#include "../WorldManager.h"

Line::Line(int x,int y,int x2,int y2,int thickness,Material* mat)
{
    //ctor
    Set_x1(x);
    Set_x2(x2);
    Set_y1(y);
    Set_y2(y2);
    Set_Thickness(thickness);
    Set_Mat(mat);
    Set_Angle(0);
    Set_Static(true);
        Set_Radial_Gravity_Distance(0);
    Set_Radial_Gravity(b2Vec2(0,0));
    Set_CreateWithForce(false);//is no

    //Just for shits n giggles
    Set_Width(Get_x2()-Get_x1());
}

Line::Line(int x,int y,int x2,int y2,bool staticc,int thickness,Material* mat)
{
    //ctor
    Set_x1(x);
    Set_x2(x2);
    Set_y1(y);
    Set_y2(y2);
    Set_Thickness(thickness);
    Set_Mat(mat);
    Set_Angle(0);
    Set_Static(staticc);
        Set_Radial_Gravity_Distance(0);
    Set_Radial_Gravity(b2Vec2(0,0));

    //Just for shits n giggles
    Set_Width(Get_x2()-Get_x1());
    Set_CreateWithForce(false);//is no
}

Line::~Line()
{
    //dtor
    Destroy(Get_C_World());
}

void Line::Create(b2World* p_world)
{
    Set_C_World(p_world);
    //do box2d first..
    b2BodyDef bodyDef;
	if (!Get_Static()){
	bodyDef.type = b2_dynamicBody;
	}
    bodyDef.allowSleep = true;
	bodyDef.awake = true;

	//??
    bodyDef.position.Set(0,0);

    //bodyDef.angle = (((-1)*Get_Angle())*WorldStandards::degtorad);

    Set_Body(p_world->CreateBody(&bodyDef));

    b2EdgeShape es;

    es.Set(b2Vec2(Get_x1()*WorldStandards::ppm,Get_y1()*WorldStandards::ppm),b2Vec2(Get_x2()*WorldStandards::ppm,Get_y2()*WorldStandards::ppm));

    //fixture stuff
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &es;

    if (!Get_Static()){
    /////add material class in the futurec.
    fixtureDef.density = Get_Mat()->GetDensity();
    fixtureDef.friction = Get_Mat()->GetFriction();
    fixtureDef.restitution = Get_Mat()->GetRestitution();
	//////
	}

	Get_Body()->CreateFixture(&fixtureDef);

    if (Get_CreateWithForce())
        ApplyForce(Get_CreateWithForce_Force());

    if (WorldStandards::debug)
        std::cout << "[Box2D] Added Line.\n";

    Set_Shape(new sf::Shape(sf::Shape::Line(Get_x1(),Get_y1(),Get_x2(),Get_y2(),Get_Thickness(),Get_Mat()->GetColor())));
    //Get_Shape()->SetCenter(sf::Vector2f(Get_x1()-Get_x2(),Get_y1()-Get_y2()));
    //Get_Shape()->SetPosition(sf::Vector2f(Get_x1()-Get_x2(),Get_y1()-Get_y2()));
    //Get_Shape()->Rotate(Get_Angle());

    Renderer::CreateLink(Get_Shape());

        if (WorldStandards::debug)
        std::cout << "[SFML] Added Line.\n";

}
