#include "client_socket.hpp"

ssize_t Client_socket::fill_client_buffer()
{
    char tmp[1024];
    ssize_t total_data = 0;

    while(true)
    {
        ssize_t data = recv(fd, tmp, sizeof(tmp), 0);
        if (data > 0)
        {
            client_buffer.insert(client_buffer.end(), tmp, tmp + data);
            total_data += data;
        }
        else if (data == 0)
        {
            return (0);
        }
        else
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                    break;
            return (-1);
        }
    }
    return (total_data);
}

std::vector<char> Client_socket::getClient_buffer()
{
    return (this->client_buffer);
}