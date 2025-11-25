#ifndef CLIENT_SOCKET_HPP
# define CLIENT_SOCKET_HPP

#include "base_socket.hpp"

class Client_socket : public Base_socket
{
    private:
        std::vector<char> client_buffer;
    public:
        Client_socket(int client_fd) : Base_socket(client_fd){};

        ssize_t fill_client_buffer();

        std::vector<char> getClient_buffer();

        bool isServer() const override { return (false); }
};

#endif