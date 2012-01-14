#include "Circle.h"
#include "../World.h"

Circle::Circle(int radius,sf::Vector2f pos,Material* mat,float degangle)
{
    //ctor
    Set_Radius(radius);
    Set_Position(sf::Vector2f(pos.x,pos.y));
    Set_Mat(mat);
    Set_Angle(degangle);
    Set_Static(false);
}

Circle::Circle(int radius,bool staticc,sf::Vector2f pos,Material* mat,float degangle)
{
    //ctor
    Set_Radius(radius);
    Set_Position(sf::Vector2f(pos.x,pos.y));
    Set_Mat(mat);
    Set_Angle(degangle);
    Set_Static(staticc);
}

Circle::~Circle()
{
    //dtor
    Destroy();
}

void Circle::Create()
{
    //
    b2BodyDef bodyDef;
    if (!Get_Static()){
	bodyDef.type = b2_dynamicBody;
    }
    bodyDef.allowSleep = true;
	bodyDef.awake = true;

	bodyDef.position.Set((Get_Position().x+Get_Radius())*WorldStandards::ppm, (Get_Position().y+Get_Radius())*WorldStandards::ppm);

    bodyDef.angle = (((-1)*Get_Angle())*WorldStandards::degtorad);

	Set_Body(World::Access()->CurrentWorld()->CreateBody(&bodyDef));

	b2CircleShape circle;

	//circle.m_p.Set(2.0f, 3.0f);

	circle.m_radius = Get_Radius()*WorldStandards::ppm;

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &circle;

    if (!Get_Static()){
    /////add material class in the futurec.
    fixtureDef.density = Get_Mat()->GetDensity();
    fixtureDef.friction = Get_Mat()->GetFriction();
    fixtureDef.restitution = Get_Mat()->GetRestitution();
	//////
    }

	Get_Body()->CreateFixture(&fixtureDef);

    //add the body to the list
    //Access()->b2PhysicsObjects.push_back(bodyBox);

    if (WorldStandards::debug)
        std::cout << "[Box2D] Added Circle.\n";

    //do sfml
    Set_Shape(new sf::Shape(sf::Shape::Circle(0,0,Get_Radius(),Get_Mat()->GetColor())));
    Get_Shape()->SetPosition(Get_Position());
    //cb->SetCenter(sf::Vector2f(radius, radius));
    Get_Shape()->Rotate(Get_Angle());

    Renderer::CreateLink(Get_Shape());

    //add body to the list
    //Access()->sfPhysicsObjects.push_back(cb);

    if (WorldStandards::debug)
        std::cout << "[SFML] Added Circle.\n";

}

void Circle::Destroy()
{
    Renderer::RemoveLink(Get_Shape());
    World::Access()->CurrentWorld()->DestroyBody(Get_Body());
}
