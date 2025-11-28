#include "body.hpp"

int handle_content_length(Client_socket &client, std::string str)
{
    char *endptr = 0;
    unsigned long contentLength = strtoul(str.c_str(), &endptr, 10);
    //aucun chiffres
    if (endptr == str.c_str())
        return (-1);
    //des char en trop à la fin
    if (static_cast<size_t>(endptr - str.c_str()) != str.size())
        return (-1); 
    if ((client.getClient_buffer().size() - client.getParsed_bytes()) < contentLength)
        return (-2);
    client.getClient_request().setBody(std::string(client.getClient_buffer().begin() + client.getParsed_bytes(), client.getClient_buffer().begin() + client.getParsed_bytes() + contentLength));
    client.addToParser_bytes(contentLength);
    client.nextstate();
    return (0);
}

int handle_chunked_transfer(Client_socket &client)
{
    size_t start_of_data;
    size_t offset = 0;
    size_t chunk_parser = client.getParsed_bytes();
    while (chunk_parser < client.getClient_buffer().size() && client.getClient_buffer()[chunk_parser] != '\n')
    {
        chunk_parser++;
        offset++;
    }
    if (chunk_parser == client.getParsed_bytes() || chunk_parser == client.getClient_buffer().size() || client.getClient_buffer()[chunk_parser - 1] != '\r')
        return (-1);
    start_of_data = chunk_parser + 1;
    offset++;
    std::string hexa(client.getClient_buffer().begin() + client.getParsed_bytes(), client.getClient_buffer().begin() + chunk_parser - 1);
    char *endptr;
    unsigned long chunk_size = strtoul(hexa.c_str(), &endptr, 16);
    if (endptr == hexa.c_str())
    {
        return (-1);
    }
    if (client.getClient_buffer().size() < start_of_data + chunk_size + 2)
        return (-2);
    if (chunk_size == 0)
    {
        if(client.getClient_buffer()[start_of_data] == '\r' && client.getClient_buffer()[start_of_data + 1] == '\n')
        {
            client.addToParser_bytes(offset + 2);
            client.nextstate();
            return (0);
        }
    }
    if (client.getClient_buffer()[start_of_data + chunk_size] != '\r' || client.getClient_buffer()[start_of_data + chunk_size + 1] != '\n')
        return (-1);
    client.getClient_request().getBody() += std::string(client.getClient_buffer().begin() + start_of_data , client.getClient_buffer().begin() + start_of_data + chunk_size);
    client.addToParser_bytes(offset + chunk_size + 2);
    return (handle_chunked_transfer(client));    
}

int handle_body(Client_socket &client)
{
    if (client.getClient_request().getMethod() != "POST")
    {
        client.getClient_request().setBody("");
        client.nextstate();
        return (0);
    }
    std::map<std::string, std::string>::iterator it = client.getClient_request().getHeaders().find("Content-Length");
    if (it != client.getClient_request().getHeaders().end())
    {
        return (handle_content_length(client, it->second));
    }
    std::map<std::string, std::string>::iterator it2 = client.getClient_request().getHeaders().find("Transfer-Encoding");
    if (it2 != client.getClient_request().getHeaders().end() || it2->second == "chunked")
    {
        return (handle_chunked_transfer(client));
    }
    return (-1);
}