#include "body.hpp"

int handle_content_length(Client_socket &client, std::string str)
{
    char *endptr = 0;
    unsigned long contentLength = strtoul(str.c_str(), &endptr, 10);
    if (endptr == str.c_str() || contentLength < 0)
        return (-1);
    if ((client.getClient_buffer().size() - client.getParsed_bytes()) >= contentLength)
        return (-1);
    client.getClient_request().setBody(std::string(client.getClient_buffer().begin() + client.getParsed_bytes(), client.getClient_buffer().begin() + client.getParsed_bytes() + contentLength));
    return (0);
}

int handle_body(Client_socket &client)
{
    if (client.getClient_request().getMethod() != "POST")
    {
        client.getClient_request().setBody("");
        return (0);
    }
    std::map<std::string, std::string>::iterator it = client.getClient_request().getHeaders().find("content-length");
    if (it != client.getClient_request().getHeaders().end())
    {
        if (handle_content_length(client, it->second) == -1)
            return (-1);
        return (0);
    }

    return (0);
}