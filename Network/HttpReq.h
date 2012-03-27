#ifndef HTTPREQ_H
#define HTTPREQ_H

#include <SFML/Network.hpp>
#include <string>

class HttpReq //! Wrap a sfml::Http::Request.
{
    public:

        HttpReq(sf::Http::Request::Method in,std::string host,std::string path);//!< Default constructor

        ~HttpReq();//!< Default destructor

        void SetUrl(std::string path);//!< change url, just /pages/me.html part
        void SetHost(std::string host);//!< change url, just http://servername.com part
        void Set(std::string host,std::string path);//!< change url host=http://servername.com path=/index.html

        std::string GetResponse();//!< If Executed already, returns response

        bool Execute(); //!< Runs the request, true if it worked.
    protected:
    private:
        sf::Http::Request Request;
        sf::Http Http;
        std::string bodyResponse;
        bool m_exec;

};

#endif // HTTPREQ_H
