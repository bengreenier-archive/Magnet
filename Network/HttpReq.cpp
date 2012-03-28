<<<<<<< HEAD
#include "HttpReq.h"

HttpReq::HttpReq(sf::Http::Request::Method in,std::string host,std::string path)
{
    //ctor

/*
    Request = new sf::Http::Request();
    Request.SetMethod(in);
    Request.SetURI(path);
    Http.SetHost(host);
    m_exec=false;
*/
}

HttpReq::~HttpReq()
{
    //dtor
}

void HttpReq::SetUrl(std::string path)
{
//    Request.SetURI(path);
}

void HttpReq::SetHost(std::string host)
{
    Http.setHost(host);
}

void HttpReq::Set(std::string host,std::string path)
{
//    Request.SetURI(path);
    Http.setHost(host);
}

bool HttpReq::Execute()
{
    sf::Http::Response Response = Http.sendRequest(Request);

    if (Response.getStatus() == sf::Http::Response::Ok)//most common good response
    {
        bodyResponse = Response.getBody();
        m_exec=true;
        return true;
    }
    else
        return false;

}

std::string HttpReq::GetResponse()
{
    if (m_exec)
        return bodyResponse;
    else
        return NULL;
}
=======
#include "HttpReq.h"

HttpReq::HttpReq(sf::Http::Request::Method in,std::string host,std::string path)
{
    //ctor

/*
    Request = new sf::Http::Request();
    Request.SetMethod(in);
    Request.SetURI(path);
    Http.SetHost(host);
    m_exec=false;
*/
}

HttpReq::~HttpReq()
{
    //dtor
}

void HttpReq::SetUrl(std::string path)
{
//    Request.SetURI(path);
}

void HttpReq::SetHost(std::string host)
{
    Http.setHost(host);
}

void HttpReq::Set(std::string host,std::string path)
{
//    Request.SetURI(path);
    Http.setHost(host);
}

bool HttpReq::Execute()
{
    sf::Http::Response Response = Http.sendRequest(Request);

    if (Response.getStatus() == sf::Http::Response::Ok)//most common good response
    {
        bodyResponse = Response.getBody();
        m_exec=true;
        return true;
    }
    else
        return false;

}

std::string HttpReq::GetResponse()
{
    if (m_exec)
        return bodyResponse;
    else
        return NULL;
}
>>>>>>> a9a393b6b22809f78e91ffd177db1142bb9050f1
