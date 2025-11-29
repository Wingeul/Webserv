#include "../../includes/request_parsing/headers.hpp"

int has_full_headers(Client_socket &client)
{
    const char endSeq[] = "\r\n\r\n";
    const char endSeq2[] = "\n\n";

    if (client.getParsed_bytes() >= client.getClient_buffer().size())
        return (-2);

    std::vector<char>::iterator it = std::search(client.getClient_buffer().begin() + client.getParsed_bytes(), client.getClient_buffer().end(), endSeq, endSeq + 4);
    std::vector<char>::iterator it2 = std::search(client.getClient_buffer().begin() + client.getParsed_bytes(), client.getClient_buffer().end(), endSeq2, endSeq2 + 2);

    if (it == client.getClient_buffer().end() && it2 == client.getClient_buffer().end())
        return (-2);
    return (0);
}

int is_header_line_complete(Client_socket &client)
{
    size_t t = client.getParsed_bytes();
    if (t >= client.getClient_buffer().size())
        return (-2);
    while (t < client.getClient_buffer().size() && client.getClient_buffer()[t] != '\n')
        t++;
    if (t == client.getClient_buffer().size())
        return (-2);
    return (0);
}

void trim_trailling_spaces(std::string &str)
{
    size_t end = str.find_last_not_of(" \t");
    if (end != std::string::npos)
    {
        str.erase(end + 1);
    }
}

int parse_key(Client_socket &client, size_t &line_begin, size_t &colon_position)
{
    while (client.getParsed_bytes() < client.getClient_buffer().size() && client.getClient_buffer()[client.getParsed_bytes()] != ':')
    {
        if (client.getClient_buffer()[client.getParsed_bytes()] == '\n')
        {
            //on last empty line
            if (client.getParsed_bytes() - line_begin == 0 || (client.getParsed_bytes() - line_begin == 1 && client.getClient_buffer()[client.getParsed_bytes() - 1] == '\r'))
            {
                client.addToParser_bytes(1);
                return (1);
            }
            // \n too early, format incorrect
            return (-1);
        }
        if (client.getClient_buffer()[client.getParsed_bytes()] == ' ')
            return (-1);
        client.addToParser_bytes(1);
    }
    if (client.getClient_buffer()[client.getParsed_bytes()] == ':')
    {
        //invalide  start avec : 
        if (line_begin == client.getParsed_bytes())
            return (-1);
        colon_position = client.getParsed_bytes();
        client.addToParser_bytes(1);
    }
    // securite fin de buffer atteint
    else
        return (-1);
    return (0);
}

int parse_value(Client_socket &client, size_t &end_line, size_t &space_count)
{
   while (client.getParsed_bytes() < client.getClient_buffer().size() && client.getClient_buffer()[client.getParsed_bytes()] == ' ')
    {
        space_count++;
        client.addToParser_bytes(1);
    }
    while(client.getParsed_bytes() < client.getClient_buffer().size() && client.getClient_buffer()[client.getParsed_bytes()] != '\n')
        client.addToParser_bytes(1);
    if (client.getClient_buffer()[client.getParsed_bytes()] == '\n')
    {
        end_line = client.getParsed_bytes();
        if (client.getClient_buffer()[client.getParsed_bytes() - 1] == '\r')
            end_line -=1;
        //mettre sur le debut de la prochaine ligne
        client.addToParser_bytes(1);
    }
    //securite fin de buffer atteint
    else
        return(-1);
    return (0);
}

int fill_headers_map(Client_socket &client)
{
    std::string key;
    std::string value;
    size_t line_begin = client.getParsed_bytes();
    size_t colon_position = client.getParsed_bytes();
    size_t end_line = client.getParsed_bytes();
    size_t space_count = 0;
    if (is_header_line_complete(client) == -2)
        return (-2);
    int ret = parse_key(client, line_begin, colon_position);
    if (ret == 1)
        return (0);
    if (ret == -1)
        return (-1);
    if (parse_value(client, end_line, space_count) == -1)
        return (-1);
    key = std::string(client.getClient_buffer().begin() + line_begin, client.getClient_buffer().begin() + colon_position);
    value = std::string(client.getClient_buffer().begin() + colon_position + 1 + space_count, client.getClient_buffer().begin() + end_line);
    trim_trailling_spaces(value);
    client.getClient_request().getHeaders()[key] = value;
    return (fill_headers_map(client));
}

int handle_headers(Client_socket &client)
{
    int ret = fill_headers_map(client);
    if (ret != 0)
        return (ret);
    client.nextstate();
    return (0);
}
