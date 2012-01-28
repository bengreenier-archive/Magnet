#include "Circle.h"
#include "../WorldManager.h"

Circle::Circle(int radius,sf::Vector2f pos,Material* mat,float degangle)
{
    //ctor
    Set_Radius(radius);
    Set_Position(sf::Vector2f(pos.x,pos.y));
    Set_Mat(mat);
    Set_Angle(degangle);
    Set_Static(false);
}

Circle::Circle(int radius,b2Vec2 tForce,sf::Vector2f pos,Material* mat,float degangle)
{
    //ctor
    Set_Radius(radius);
    Set_Position(sf::Vector2f(pos.x,pos.y));
    Set_Mat(mat);
    Set_Angle(degangle);
    Set_Static(false);
    ApplyForce(tForce);
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

    //OKAY, SO THIS WORKS ALL COMMENTED OUT.
    //if (Get_Static())
        bodyDef.position.Set((Get_Position().x/*+Get_Radius()*/)*WorldStandards::ppm, (Get_Position().y/*+Get_Radius()*/)*WorldStandards::ppm);
    //else
    //  bodyDef.position.Set(((Get_Position().x+Get_Radius())/2)*WorldStandards::ppm, ((Get_Position().y+Get_Radius())/2)*WorldStandards::ppm);

    bodyDef.angle = (((-1)*Get_Angle())*WorldStandards::degtorad);

	Set_Body(WorldManager::Access()->CurrentWorld()->CurrentB2World()->CreateBody(&bodyDef));

	b2CircleShape circle;

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

   if (WorldStandards::debug)
        std::cout << "[Box2D] Added Circle.\n";

    //do sfml

    Set_Shape(new sf::Shape(sf::Shape::Circle(0,0,Get_Radius(),Get_Mat()->GetColor())));
    Get_Shape()->SetPosition(Get_Position());
    Get_Shape()->Rotate(Get_Angle());

    Renderer::CreateLink(Get_Shape());

     if (WorldStandards::debug)
        std::cout << "[SFML] Added Circle.\n";

}

void Circle::Destroy()
{
    Renderer::RemoveLink(Get_Shape());
    WorldManager::Access()->CurrentWorld()->CurrentB2World()->DestroyBody(Get_Body());
        if (WorldStandards::debug)
        std::cout << "[SFML/Box2D] Removed Circle.\n";

}

void Circle::Update()
{
        Get_Shape()->SetPosition(Get_Position());
        Get_Shape()->Rotate(Get_Angle());
}

void Circle::Hide()
{
    Renderer::RemoveLink(Get_Shape());
}
