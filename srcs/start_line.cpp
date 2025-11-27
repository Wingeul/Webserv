#include "start_line.hpp"

int extract_path(Client_socket &client)
{
    std::string ret;

    size_t i = client.getParsed_bytes();
    while (i < client.getClient_buffer().size() && client.getClient_buffer()[i] != ' ')
    {
        if (client.getClient_buffer()[i] == '\n' || client.getClient_buffer()[i] == '\r')
            return (-1);
        ret += client.getClient_buffer()[i];
        i++;
    }
    client.addToParser_bytes(i - client.getParsed_bytes() + 1);
    client.getClient_request().setPath(ret);
    return (0);
}

int extract_version(Client_socket &client)
{
    size_t i = client.getParsed_bytes();

    while (i < client.getClient_buffer().size() && client.getClient_buffer()[i] != '\n')
        i++;
    if (i == client.getClient_buffer().size())
        return (-1);
    size_t line_end = i;
    if (i > 0 && client.getClient_buffer()[i-1] == '\r')
        line_end = i-1;
    std::string ret(client.getClient_buffer().begin() + client.getParsed_bytes(), client.getClient_buffer().begin() + line_end);
    client.getClient_request().setVersion(ret);
    client.addToParser_bytes(i - client.getParsed_bytes() + 1);
    return (0);
}

int extract_method(Client_socket &client)
{
    if (isIdentical(client.getClient_buffer(), "GET "))
    {
        client.getClient_request().setMethod("GET");
        client.addToParser_bytes(4);
        return (0);
    } 
    else if (isIdentical(client.getClient_buffer(), "POST "))
    {
        client.getClient_request().setMethod("POST");
        client.addToParser_bytes(5);
        return (0);
    }
    else if (isIdentical(client.getClient_buffer(), "DELETE "))
    {
        client.getClient_request().setMethod("DELETE");
        client.addToParser_bytes(7);
        return (0);
    }
    else
        return (-1);
}

int has_full_start_line(Client_socket &client)
{
    if (std::find(client.getClient_buffer().begin(), client.getClient_buffer().end(), '\n') != client.getClient_buffer().end())
    {
        return (0);
    }
    return (-2);
}

int handle_start_line(Client_socket &client)
{
    if (has_full_start_line(client) == -2)
        return (-2);
    if (extract_method(client) == -1)
        return (-1);
    if (extract_path(client) == -1)
        return (-1);
    if (extract_version(client) == -1)
        return (-1);
    client.nextstate();
    return (0);
}
