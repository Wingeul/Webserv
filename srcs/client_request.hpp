#ifndef CLIENT_REQUEST_HPP
# define CLIENT_REQUEST_HPP

#include <cstring>
#include <unistd.h>
#include <iostream>
#include <map>

class Client_request
{
    private:
        std::string method;
        std::string path;
        std::string version;
        std::map<std::string, std::string> headers;
    public:
        Client_request(){};
        ~Client_request(){};


        std::string& getMethod(){return (this->method);};
        std::string& getPath(){return (this->path);};
        std::string& getVersion(){return (this->version);};
        std::map<std::string, std::string>& getHeaders(){return(this->headers);};

        void setMethod(std::string str){this->method = str;};
        void setPath(std::string str){this->path = str;};
        void setVersion(std::string str){this->version = str;};
};

#endif