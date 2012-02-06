#include "XmlParse.h"

/*
XmlParse::XmlParse(const char* path) {
    //Initialize variables
    m_loadOkay = false;
    m_path = path;
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
        std::cout<<"[XmlParse] Loading " << m_path << "\n";

    m_loadOkay = m_doc->LoadFile();

    if (( !m_loadOkay )&&(XmlGlobals::debug)){
        printf( "[XmlParse] %s.\n", m_doc->ErrorDesc() );
    }

    return m_loadOkay;
}

bool XmlParse::Load(const char* filename){
    m_doc->LoadFile(filename);
    m_path = filename;
    Load();
}

XmlNode* XmlParse::Parse(TiXmlNode* initial_node, XmlNode* node){
    if(!LoadOkay()) return node;

    //Set node to root
    if(node == NULL){
        node = new XmlNode();   //Create an empty node
        node.CreateFromDocument(initial_node); //Initialize the node with a TiXmlDocument
    }



}
*/
