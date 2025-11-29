#include "../../includes/client_side/client_socket.hpp"

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

void Client_socket::nextstate()
{
    switch (this->state)
    {
        case START_LINE:
            this->state = HEADERS;
            break;
        case HEADERS:
            this->state = BODY;
            break;
        case BODY:
            this->state = COMPLETED;
            break;
        case COMPLETED:
            this->state = START_LINE;
            break;
    }
}

void Client_socket::reset()
{
    this->client_buffer.erase(this->client_buffer.begin(), this->client_buffer.begin() + this->parsed_bytes);
    this->parsed_bytes = 0;
    this->state = START_LINE;
    this->Client_req.reset();
}

std::vector<char>& Client_socket::getClient_buffer()
{
    return (this->client_buffer);
}

Client_request& Client_socket::getClient_request()
{
    return (this->Client_req);
}

size_t& Client_socket::getParsed_bytes()
{
    return (this->parsed_bytes);
}

Client_socket::ParseState Client_socket::getState() const
{
    return (this->state);
}

void Client_socket::setParsed_bytes(size_t t)
{
    this->parsed_bytes = t;
}

void Client_socket::addToParser_bytes(size_t t)
{
    this->parsed_bytes+=t;
}
