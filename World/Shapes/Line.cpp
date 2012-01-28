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

    //Just for shits n giggles
    Set_Width(Get_x2()-Get_x1());
}

Line::~Line()
{
    //dtor
    Destroy();
}

void Line::Create()
{

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

    Set_Body(WorldManager::Access()->CurrentWorld()->CurrentB2World()->CreateBody(&bodyDef));

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

void Line::Destroy()
{
        Renderer::RemoveLink(Get_Shape());
    WorldManager::Access()->CurrentWorld()->CurrentB2World()->DestroyBody(Get_Body());
    if (WorldStandards::debug)
        std::cout << "[SFML/Box2D] Removed Line.\n";

}

void Line::Update()
{
    Get_Shape()->SetPosition(Get_Position());
    //Get_Shape()->Rotate(Get_Angle());
}

void Line::Hide()
{
    Renderer::RemoveLink(Get_Shape());
}
