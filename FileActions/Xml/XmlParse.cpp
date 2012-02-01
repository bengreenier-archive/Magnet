#include "XmlParse.h"
/*
XmlParse::XmlParse(const char* path) {
    //Initialize variables
    m_loadOkay = false;

    m_doc = new TiXmlDocument(path);

    Load();
}

XmlParse::XmlParse(){
    //Initialize variables
    m_loadOkay = false;
    m_doc = new TiXmlDocument();

}

XmlParse::~XmlParse()
{
    //dtor
}

TiXmlDocument* XmlParse::GetDocument(){
    return m_doc;
}

bool XmlParse::Load(){
    if (XmlGlobals::debug)
        std::cout<<"[XmlParse] Loading " << m_doc->ValueStr() << "\n";

    m_loadOkay = m_doc->LoadFile();

    if (( !m_loadOkay )&&(XmlGlobals::debug)){
        printf( "[XmlParse] %s.\n", m_doc->ErrorDesc() );
    }

    return m_loadOkay
}

bool XmlParse::Load(const char* filename){
    m_doc->LoadFile(filename);
    Load();
}

XmlNode* Parse(TiXmlNode* initial_node, XmlNode* node=NULL){
    if(!LoadOkay()) return node;

    //Set node to root
    if(node == NULL){
        node = new XmlNode();   //Create an empty node
        node.CreateFromDocument(initial_node); //Initialize the node with a TiXmlDocument
    }



}

/*
void XmlParse::recurse(TiXmlNode* incomingNode){
    TiXmlNode* temp = 0;
    TiXmlAttribute* tempElem = 0;

    for (temp=incomingNode->FirstChild(); temp; temp = temp->NextSibling() ){
        if (!temp->NoChildren()){
            //is <TAG></TAG>
            //if root element, ie: document, just recurse
            if (temp != m_doc->RootElement() ){
                //xml_node* tmnode = new xml_node;
                for (tempElem = temp->ToElement()->FirstAttribute(); tempElem; tempElem = tempElem->Next() ){
                    //scroll the attrs
                    if (XmlGlobals::debug)
                        std::cout<<"Attr = "<<tempElem->Value()<<"\n";
                }

                if (XmlGlobals::debug)
                    std::cout<<"[XmlParse] [Recurse]"<<temp->Value()<<"\n";
            }
            recurse(temp);

        }
        else
        {
            //is content


                for (tempElem = temp->ToElement()->FirstAttribute(); tempElem; tempElem = tempElem->Next() )
                {
                    //scroll the attrs
                    if (XmlGlobals::debug)
                        std::cout<<"Attr = "<<tempElem->Value()<<"\n";
                }

            //this is a child node of Parent...


            if (XmlGlobals::debug)
                std::cout<<"[XmlParse] [Recurse]"<<temp->Parent()->Value()<<" contains "<<temp->Value()<<"\n";
        }
    }
}
*/
