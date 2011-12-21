#ifndef FUNCTIONPTRTEMPLATE_H
#define FUNCTIONPTRTEMPLATE_H

//this was sposed to be testing to see if i can use a template to take any function into Console::AddCommand
//its really hard though.


//okay, so this works..kinda. i can Add any type of function with anynumber of args like this FunctionPtrTemplate<void (*)()>Add(&Function);
//and for now i can output its typeinfo name and its different for different types, so its seemingly working.. but i cant seem to store these
//into Type, because idk. but i also feel like type might not be able to hold all these different function pointers, cause, the Type
//seems like it would be different for each <T> given, so it might work, but then there would be a million differnet types of Type. weirdness?

#include <vector>
#include <iostream>
#include <typeinfo>

template<class T>
class FunctionPtrTemplate
{
    public:

    static std::vector <T> Type;


    //static FunctionPtrTemplate* GetObject();


    static void Add(T FuncType)
    {
        std::cout<<typeid(FuncType).name();
    }



    protected:
    private:
    //static FunctionPtrTemplate* FPtr;

};


#endif // FUNCTIONPTRTEMPLATE_H
