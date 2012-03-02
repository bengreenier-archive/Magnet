#ifndef CONCURRENTQUEUE_H
#define CONCURRENTQUEUE_H

#include "SharedVar.h"

enum CQFLAG{
    CQ_F_WEAK   = 1,
    CQ_F_STRONG = 2
};


template<class T>
class ConcurrentQueue
{
    struct node {
        SharedVar<T>        value;
        SharedVar<node>*    next;
    };
    CQFLAG m_mode;
    SharedVar<node>*        m_head;
    SharedVar<node>*        m_tail;
    public:
        ConcurrentQueue(CQFLAG mode = CQ_F_WEAK){
            m_head = m_tail = 0;
            m_mode = mode;
        }

        virtual ~ConcurrentQueue();

        void Insert(const T& val){
        }

        bool IsEmpty(){
            if(m_head == m_tail){
                return true;
            }else{
                return false;
            }
        }
};

#endif // CONCURRENTQUEUE_H
