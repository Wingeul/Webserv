#include "../../includes/server_side/handle_request.hpp"

#include <sys/socket.h>
#include <fstream>
#include <vector>
#include <string>

int handle_request(Client_socket &client)
{
    //TODO PROPER REQUEST HANDLE
    std::cout << "what did we parse ? :"<< std::endl;
    std::cout << "method: " << client.getClient_request().getMethod() << " ";
    std::cout << "path: " << client.getClient_request().getPath()<< " ";
    std::cout << "version: " << client.getClient_request().getVersion() << std::endl;
    std::cout << "--headers--"<< std::endl;
    for (std::map<std::string, std::string>::const_iterator it = client.getClient_request().getHeaders().begin(); it != client.getClient_request().getHeaders().end(); ++it) {
        std::cout << it->first << " : " << it->second << std::endl;
    }
    std::cout << "--body--"<<std::endl;
    std::cout << client.getClient_request().getBody() << std::endl ;



    std::ifstream f("../docs/this-is.gif", std::ios::binary);
    std::vector<char> body((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());


    std::string header;
    header += "HTTP/1.1 200 OK\r\n";
    header += "Content-Type: image/gif\r\n";
    header += "Content-Length: " + std::to_string(body.size()) + "\r\n";
    header += "Connection: close\r\n";
    header += "\r\n";

    send(client.getFd(), header.c_str(), header.size(), 0);

    send(client.getFd(), &body[0], body.size(), 0);

    client.reset();
    return (0);
}