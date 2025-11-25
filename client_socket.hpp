#ifndef CLIENT_SOCKET_HPP
# define CLIENT_SOCKET_HPP

#include "base_socket.hpp"

class Client_socket : public Base_socket
{
    public:
        Client_socket(int client_fd) : Base_socket(client_fd){};

        bool isServer() const override { return (false); }
};

#endif