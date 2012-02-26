#ifndef CONCURRENTQUEUE_H
#define CONCURRENTQUEUE_H

//Uses CAS to ensure that reads/writes are successful.
template<class T>
class ConcurrentQueue
{
    public:
        ConcurrentQueue();
        virtual ~ConcurrentQueue();

        bool isEmpty();
        bool CompareAndSwap(T* var, T oldval, T newval);
    protected:
    private:
        struct node {
            T* data_p;
            node* next;
        };

        node* head;

        node* m_read;   //Read always points to the first node in the queue
        node* m_write;  //Write always points to the last node in the queue
};

#endif // CONCURRENTQUEUE_H
