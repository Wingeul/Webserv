#include "handle_request.hpp"

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
    client.reset();
    return (0);
}