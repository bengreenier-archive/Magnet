#include "ImageHandler.h"
//#include "../../Console/Console.h"

ImageHandler* ImageHandler::ImageHandlerPtr = NULL;

ImageHandler::ImageHandler()
{
    //ctor
    //Console::AddCommand("ImageHandler::PrintAvailableImages()",&ImageHandler::PrintAvailableImages);
}

ImageHandler::~ImageHandler()
{
    //dtor
}

sf::Image& ImageHandler::GetImage(std::string in)
{
    if (GetObject()->object_map.count(in) <= 0)
    {
        //throw
    }else{
        //return reference to image
        return GetObject()->object_map[in];
    }



}

bool ImageHandler::AddImage(std::string in)  throw(Exception::ob)
{
    sf::Image Image;

    GetObject()->object_map[in] = Image;

    if (!GetObject()->object_map[in].LoadFromFile(in))
    {
        return false;
    }

    return true;
}

ImageHandler* ImageHandler::GetObject(){
    if(ImageHandlerPtr == NULL){
        ImageHandlerPtr = new ImageHandler();
    }

    return ImageHandlerPtr;
}


void ImageHandler::PrintAvailableImages()
{
    for ( GetObject()->Oit=GetObject()->object_map.begin() ; GetObject()->Oit != GetObject()->object_map.end(); GetObject()->Oit++ )
        std::cout<<GetObject()->Oit->first<<"\n";

}
