#ifndef ENTITY_H
#define ENTITY_H

namespace Entity{
	Enum type{
		Circle,
		Rect,
		Triangle
		};

class Entity
{
    public:
        /** Default constructor */
        Entity(Entity::Type type);
        Entity(ShapeTransform trans,ShapeDraw draw);
        Entity(ShapeTransform trans,ShapeDraw draw,ShapeData data);

        ShapeTransform Transform;
        ShapeDraw	   Draw;
        ShapeData	   Data;
        /** Default destructor */
        ~Entity();
    protected:
    private:

        void CraftCircle();
        void CraftRect();
        void CraftTriangle();
};


	};


#endif // ENTITY_H
