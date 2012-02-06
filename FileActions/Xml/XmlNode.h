#ifndef XMLNODE_H
#define XMLNODE_H


#include "tinystr.h"
#include "tinyxml.h"
#include <vector>

class XmlNode
{
    public:
        XmlNode();
        virtual ~XmlNode();

        void CreateFromDocument(TiXmlDocument* document);

        XmlNode& operator[](int index){
            return *m_children[index];
        }
    protected:
    private:
        typedef std::vector<XmlNode*>    node_vect_type;

        node_vect_type m_children;
        unsigned int level;
};

#endif // XMLNODE_H
