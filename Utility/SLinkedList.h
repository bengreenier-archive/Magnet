#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H

#include "../Pipeline.h"

#define NULL 0

namespace util
{

template<typename T>
struct node_t
{
    node_t* next;
    T       value;

    node_t(const T& val, node_t* next = NULL)
    {
        this->value = val;
        this->next  = next;
    }
    node_t(const node_t& cpy)
    {
        *this = cpy;
    }

    node_t& operator=(const node_t& cpy)
    {
        this->next = cpy->next;
        this->value = cpy->value;

        return *this;
    }
};

template<typename T>
class SLinkedList
{
    public:


        SLinkedList();
        virtual ~SLinkedList();

        void insert( const T& val );
        void remove(const node_t<T>* node);
        bool isEmpty() const;

        void debug_output() const;
    protected:
    private:
        node_t<T>* m_head;
};

template<typename T>
SLinkedList<T>::SLinkedList()
{
    m_head = NULL;
}


template<typename T>
SLinkedList<T>::~SLinkedList()
{
    //dtor
}

template<typename T>
void SLinkedList<T>::insert(const T& val)
{
    if(isEmpty())
    {
        dbgconsole << "Inserting into empty list\n";
        m_head = new node_t<T>(val, NULL);
    }else{
        dbgconsole << "Inserting " << val << "\n";
        dbgconsole << "HEAD: " << m_head->value << std::endl;
        m_head = new node_t<T>(val, m_head->next);
        dbgconsole << "AFTER: " << m_head->value << std::endl;
        dbgconsole << "HEAD-next: " << m_head->next->value << std::endl;
    }
}

template<typename T>
void SLinkedList<T>::remove(const node_t<T>* node)
{
    node_t<T>* prev = m_head;
    for( node_t<T>* it = m_head; it != NULL; it = it->next )
    {
        if(it == node)
        {
            prev->next = node;
            node->next = it->next;
            delete it;

            return;
        }

        prev = it;
    }
}

template<typename T>
bool SLinkedList<T>::isEmpty() const {
    return (m_head == NULL);
}

template<typename T>
void SLinkedList<T>::debug_output() const
{
    dbgconsole << "Debug output\n";
    int i = 0;
    for( node_t<T>* it = m_head; it != NULL; it = it->next )
    {
        dbgconsole << it->value << std::endl;
        i++;
    }

    std::cout << i << std::endl;
}

}//ns util
#endif // SLINKEDLIST_H
