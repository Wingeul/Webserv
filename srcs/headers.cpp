#include "headers.hpp"

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

int fill_headers_map(Client_socket &client)
{
    if (is_header_line_complete(client) == -2)
        return (-2);
    size_t line_begin = client.getParsed_bytes();
    size_t colon_position = client.getParsed_bytes();
    size_t end_line = client.getParsed_bytes();
    while (client.getParsed_bytes() < client.getClient_buffer().size() && client.getClient_buffer()[client.getParsed_bytes()])
    {
        if (client.getClient_buffer()[client.getParsed_bytes()] == '\n')
        {
            //on last empty line
            if (client.getParsed_bytes() - line_begin == 0 || (client.getParsed_bytes() - line_begin == 1 && client.getClient_buffer()[client.getParsed_bytes() - 1] == '\r'))
            {
                client.addToParser_bytes(1);
                return (0);
            }
            // \n too early, format incorrect
            return (-1);
        }
    }
    
}

int handle_headers(Client_socket &client)
{
    int ret = fill_headers_map(client);
    if (ret!= 0)
        return (ret);
    client.nextstate();
    return (0);
}
