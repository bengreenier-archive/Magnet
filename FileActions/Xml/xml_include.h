#ifndef XML_INCLUDE_H
#define XML_INCLUDE_H

#include "tinystr.h"
#include "tinyxml.h"

//should be all you need to xml stuff..

#include <map>
#include <vector>
#include <string>

class XmlParse{//! The wrapper class for parsing xml
    public:
        XmlParse(const char * path) { m_doc = new TiXmlDocument(path); }//!< Default Constructor
        std::multimap < std::string, std::string > Parse() {

if (m_ElementMap.size()==0){
std::cout<<"[XmlParse] [Parse] Loading File...\n";
            bool loadOkay = m_doc->LoadFile();

            if ( !loadOkay )
            {
                printf( "[XmlParse] [Parse] %s.\n", m_doc->ErrorDesc() );

            }


            TiXmlNode* node = 0;
            TiXmlNode* inner = 0;
            recurse(m_doc->FirstChild());
/*
		for( node = m_doc->FirstChild(); node; node = node->NextSibling() )
		{
		    if (node->Value() != m_doc->RootElement()->Value())
                        m_ElementMap.insert(std::pair<std::string,std::string>(node->Parent()->Value(),node->Value()));
                     else
                        m_ElementMap.insert(std::pair<std::string,std::string>("NULL",node->Value()));

		}
*/
/*
            while (!node->NoChildren())
            {
                for( inner = node->FirstChild(); inner; inner = inner->NextSibling() )
                {
                    count++;

                     if (inner->Value() != m_doc->RootElement()->Value())
                        m_ElementMap.insert(std::pair<std::string,std::string>(inner->Parent()->Value(),inner->Value()));
                     else
                        m_ElementMap.insert(std::pair<std::string,std::string>("NULL",inner->Value()));
                }

                node = node->NextSibling();
            }
*/



}else{/*std::cout<<"[XmlParse] [Parse] ElementMap Already Set...\n";*/}
            return m_ElementMap;
		}//!< Do the grunt work, open and parse the file into a returned multimap

		std::multimap < std::string, std::string >::iterator Iterator;

    private:
        TiXmlDocument* m_doc;
        std::multimap < std::string, std::string > m_ElementMap;


        void recurse(TiXmlNode* node) {
TiXmlNode* node2 = 0;

std::cout<<"trying to iterate "<<node->Parent()->Value()<<"\n";

        if (!node->NoChildren())
        		for( node = m_doc->FirstChild(); node; node = node->NextSibling() )
                {

                    if (node->Value() != m_doc->RootElement()->Value())
                                m_ElementMap.insert(std::pair<std::string,std::string>(node->Parent()->Value(),node->Value()));
                             else
                                m_ElementMap.insert(std::pair<std::string,std::string>("NULL",node->Value()));


                    /*for ( node2 = node->FirstChild(); node2; node2 = node2->NextSibling() )
                        recurse(node2);*/

                }


        }


};

#endif
