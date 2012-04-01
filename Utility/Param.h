#ifndef PARAM_H
#define PARAM_H

namespace util{

class Param
{
    public:
        Param(unsigned char num_args, ...);
        virtual ~Param();

    protected:
    private:
        int m_args[];
};

}//ns util

#endif // PARAM_H
