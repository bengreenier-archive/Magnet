#include "Triangle.h"
#include "../World.h"

Triangle::Triangle(int size,sf::Vector2f Globalpos,Material* mat,float degangle)
{
    //ctor
    Set_Mat(mat);
    Set_Angle(degangle);
    Set_Position(Globalpos);
    m_size=size;
}

Triangle::Triangle(int size,sf::Vector2f Globalpos,b2Vec2 tForce,Material* mat,float degangle)
{
    //ctor
    Set_Mat(mat);
    Set_Angle(degangle);
    Set_Position(Globalpos);
    ApplyForce(tForce);
    m_size=size;
}


Triangle::Triangle(int size,sf::Vector2f Globalpos,bool staticc,Material* mat,float degangle)
{
    //ctor
    Set_Mat(mat);
    Set_Angle(degangle);
    Set_Position(Globalpos);
    Set_Static(staticc);
    m_size=size;
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


    float size = m_size;
    bodyDef.angle = (((-1)*Get_Angle())*WorldStandards::degtorad);

	Set_Body(World::Access()->CurrentWorld()->CreateBody(&bodyDef));

	b2PolygonShape dynamicBox;

    //set 3 pts
      b2Vec2 vertices[3];

      //perhaps the order of operations is wrong here, maybe we should Get_Position().x*ppm and then size

      vertices[0].Set(Get_Position().x*WorldStandards::ppm,Get_Position().y*WorldStandards::ppm);
      //vertices[1].Set(600*WorldStandards::ppm,500*WorldStandards::ppm);
      vertices[1].Set((Get_Position().x+size)*WorldStandards::ppm,(Get_Position().y+size)*WorldStandards::ppm);
      vertices[2].Set(Get_Position().x*WorldStandards::ppm,(Get_Position().y+size)*WorldStandards::ppm);

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
      Get_Shape()->AddPoint(sf::Vector2f(Get_Position().x,Get_Position().y),Get_Mat()->GetColor());
      //Get_Shape()->AddPoint(sf::Vector2f(600,500),Get_Mat()->GetColor());
      Get_Shape()->AddPoint(sf::Vector2f(Get_Position().x+size,Get_Position().y+size),Get_Mat()->GetColor());
      Get_Shape()->AddPoint(sf::Vector2f(Get_Position().x,Get_Position().y+size),Get_Mat()->GetColor());

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
