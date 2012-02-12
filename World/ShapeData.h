#ifndef SHAPEDATA_H
#define SHAPEDATA_H


class ShapeData
{
    public:
        /** Default constructor */
        ShapeData(b2body* engineBody,b2World* engineWorld);
        /** Default destructor */
        ~ShapeData();

        Create();
		Remove();

    protected:
    private:
        b2body* body;
		b2world* world;
};

#endif // SHAPEDATA_H
