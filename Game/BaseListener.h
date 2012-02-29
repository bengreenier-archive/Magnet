#ifndef BASELISTENER_H
#define BASELISTENER_H

#include "Parameter.h"

#include <vector>
#include <cstdarg>

class BaseListener {
    private:

        /*template <class T>
        struct callobject{
            T*  ptr;
        };*/

    public:

        /*union {
            m_callobject CallObject
        }*/


        typedef unsigned char num_arg_t;  // The number of extra arguments to take
        typedef std::vector<Parameter>   param_list_t;

        BaseListener(){ }
        virtual ~BaseListener() {}
        virtual bool onHear(num_arg_t size, ...){
            if(size == 0){
               // callback();
            }else{
                Parameter val;
                param_list_t params;

                va_list args;
                va_start(args, size);

                for(num_arg_t i = 0; i<size; i++){
                    val = va_arg(args, Parameter);
                    params.push_back(val);
                }

                return executeCallback(params);
            }
        }

        protected:
            virtual bool executeCallback(param_list_t params) = 0;
};

#endif //ABASTRACTLISTENER_H
