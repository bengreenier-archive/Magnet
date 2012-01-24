#ifndef XML_INCLUDE_H
#define XML_INCLUDE_H

#include "tinystr.h"
#include "tinyxml.h"

//should be all you need to xml stuff..

#include <map>
#include <vector>
#include <string>

/*
class XmlObject{//! The Object class for an XML storage
    public:
        XmlObject(std::string vin,int total) {Value=vin; UUID=total;}
        AddInternalObject(XmlObject* in){ Internals.push_back(in); }
        std::string Value;
        XmlObject* Child(int i) {return Internals[i];}


    private:
        std::vector <XmlObject*> Internals;
        int UUID;


};
*/
namespace xmlglobals{ const static bool debug = true; };


class XmlParse{//! The wrapper class for parsing xml
    public:

            struct xml_node{
            std::vector<xml_node*> children;
            bool isdata;
            std::string data;
            std::string name;
            std::map<std::string,std::string> attribute;

        };


        XmlParse(const char * path) { m_doc = new TiXmlDocument(path); }//!< Default Constructor
        xml_node* Parse()
        {

            if (xmlglobals::debug)
                std::cout<<"[XmlParse] [Parse] Loading File...\n";

            bool loadOkay = m_doc->LoadFile();

            if (( !loadOkay )&&(xmlglobals::debug))
            {
                printf( "[XmlParse] [Parse] %s.\n", m_doc->ErrorDesc() );

            }



            root = new xml_node;
            root->name="root";
            root->isdata=false;



            recurse(m_doc);

            return Tree();

		}//!< Do the grunt work, open and parse the file...returns the nodetree




    private:
        TiXmlDocument* m_doc;

        xml_node* Tree(){ return root; }//!< Return the nodetree of the xml document.

        xml_node* root; //root for this xml


               void recurse(TiXmlNode* incomingNode) {

                TiXmlNode* temp = 0;
                TiXmlAttribute* tempElem = 0;

            for (temp=incomingNode->FirstChild(); temp; temp = temp->NextSibling() )
                {



                    if (!temp->NoChildren())
                    {
                        //is <TAG></TAG>

                        //if root element, ie: document, just recurse
                        if (temp != m_doc->RootElement() )
                        {

                            xml_node* tmnode = new xml_node;

                            for (tempElem = temp->ToElement()->FirstAttribute(); tempElem; tempElem = tempElem->Next() )
                            {
                                //scroll the attrs
                                if (xmlglobals::debug)
                                    std::cout<<"Attr = "<<tempElem->Value()<<"\n";

                                tmnode->attribute.insert(std::pair<std::string,std::string>(tempElem->Name(),tempElem->Value()));
                            }

                            if (xmlglobals::debug)
                                std::cout<<"[XmlParse] [Recurse]"<<temp->Value()<<"\n";

                            tmnode->isdata=false;
                            tmnode->name = temp->Value();

                            root->children.push_back(tmnode);
                        }
                        recurse(temp);

                    }
                    else
                    {
                        //is content
                         xml_node* tmnode = new xml_node;
                            tmnode->isdata=true;
                            tmnode->data = temp->Value();

                            for (tempElem = temp->ToElement()->FirstAttribute(); tempElem; tempElem = tempElem->Next() )
                            {
                                //scroll the attrs
                                if (xmlglobals::debug)
                                    std::cout<<"Attr = "<<tempElem->Value()<<"\n";

                                tmnode->attribute.insert(std::pair<std::string,std::string>(tempElem->Name(),tempElem->Value()));
                            }

                        //this is a child node of Parent...


                        if (xmlglobals::debug)
                            std::cout<<"[XmlParse] [Recurse]"<<temp->Parent()->Value()<<" contains "<<temp->Value()<<"\n";
                    }
                }



        }


};

#endif
