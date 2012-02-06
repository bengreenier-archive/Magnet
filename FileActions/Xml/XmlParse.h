#ifndef XMLPARSE_H
#define XMLPARSE_H

#include <iostream>
#include <string>

#include "XmlGlobals.h"

#include "tinystr.h"
#include "tinyxml.h"

#include "XmlNode.h"
/*
class XmlParse{//! The wrapper class for parsing xml
    public:
        XmlParse(const char* path); //!< Constructor from a path
        XmlParse(); //!< Default Constructor
        ~XmlParse(); //!< Virtual destructor

        XmlNode*        Parse(TiXmlNode* initial_node, XmlNode* node=NULL); //!<
        TiXmlDocument*  GetDocument();
        bool            Load();
        bool            Load(const char* filename);
        bool            LoadOkay(){ return m_loadOkay; };

        TiXmlNode*      operator[](int index){
            TiXmlNode* node = m_doc->GetRootElement()->Clone();
            for(int i=0; i < index; i++){
                node = node->IterateChildren(node);
                if(i == index){
                    return node;
                }
            }
        }
    private:
        TiXmlDocument*  m_doc;
        const char* m_path;
        bool m_loadOkay;
};
*/
#endif // XMLPARSE_H
