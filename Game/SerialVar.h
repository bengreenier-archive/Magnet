#ifndef SERIALVAR_H
#define SERIALVAR_H

template<class T>
class SerialVar
{
    public:
        SerialVar(); //Default
        SerialVar(T val); //Construct with value

        virtual ~SerialVar();
    protected:
    private:
        T* m_location;


};

#endif // SERIALVAR_H
