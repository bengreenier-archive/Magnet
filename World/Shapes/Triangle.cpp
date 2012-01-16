#include "Triangle.h"
#include "../World.h"

Triangle::Triangle(sf::Vector2f pos1,sf::Vector2f pos2,sf::Vector2f pos3,sf::Vector2f Globalpos,Material* mat,float degangle)
{
    //ctor
    Set_Mat(mat);
    Set_Angle(degangle);
    Set_Position(Globalpos);
}

Triangle::Triangle(sf::Vector2f pos1,sf::Vector2f pos2,sf::Vector2f pos3,sf::Vector2f Globalpos,b2Vec2 tForce,Material* mat,float degangle)
{
    //ctor
    Set_Mat(mat);
    Set_Angle(degangle);
    Set_Position(Globalpos);
    ApplyForce(tForce);
}


Triangle::Triangle(sf::Vector2f pos1,sf::Vector2f pos2,sf::Vector2f pos3,sf::Vector2f Globalpos,bool staticc,Material* mat,float degangle)
{
    //ctor
    Set_Mat(mat);
    Set_Angle(degangle);
    Set_Position(Globalpos);
    Set_Static(staticc);
}

Triangle::~Triangle()
{
    //dtor
    Destroy();
}


void Triangle::Create()
{
    //do box2d first..
    b2BodyDef bodyDef;
	if (!Get_Static()){
	bodyDef.type = b2_dynamicBody;
	}
    bodyDef.allowSleep = true;
	bodyDef.awake = true;


    bodyDef.angle = (((-1)*Get_Angle())*WorldStandards::degtorad);

	Set_Body(World::Access()->CurrentWorld()->CreateBody(&bodyDef));

	b2PolygonShape dynamicBox;

    //set 3 pts
      b2Vec2 vertices[3];
      vertices[0].Set(pos1.x*WorldStandards::ppm,pos1.y*WorldStandards::ppm);
      vertices[1].Set(pos2.x*WorldStandards::ppm,pos2.y*WorldStandards::ppm);
      vertices[2].Set(pos3.x*WorldStandards::ppm,pos3.y*WorldStandards::ppm);

    dynamicBox.Set(vertices,3);
	//fixture stuff
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;

    if (!Get_Static()){
    /////add material class in the futurec.
    fixtureDef.density = Get_Mat()->GetDensity();
    fixtureDef.friction = Get_Mat()->GetFriction();
    fixtureDef.restitution = Get_Mat()->GetRestitution();
	//////
	}

	Get_Body()->CreateFixture(&fixtureDef);

    if (WorldStandards::debug)
        std::cout << "[Box2D] Added Triangle.\n";

    //do sfml
    Set_Shape(new sf::Shape());
    //set 3 pts
    Get_Shape()->AddPoint(pos1,Get_Mat()->GetColor());
    Get_Shape()->AddPoint(pos2,Get_Mat()->GetColor());
    Get_Shape()->AddPoint(pos3,Get_Mat()->GetColor());

    //Get_Shape()->SetPosition(sf::Vector2f(sfposx, sfposy)); //Get_Position()
    //Get_Shape()->SetCenter(sf::Vector2f((Get_Width()/2), (Get_Height()/2)));
    Get_Shape()->Rotate(Get_Angle());

    Renderer::CreateLink(Get_Shape());

    if (WorldStandards::debug)
        std::cout << "[SFML] Added Triangle.\n";


}

void Triangle::Destroy()
{
    //
    Renderer::RemoveLink(Get_Shape());
    World::Access()->CurrentWorld()->DestroyBody(Get_Body());
    if (WorldStandards::debug)
        std::cout << "[SFML/Box2D] Removed Triangle.\n";

}


void Triangle::Update()
{
    Get_Shape()->SetPosition(Get_Position());
    Get_Shape()->Rotate(Get_Angle());
}
