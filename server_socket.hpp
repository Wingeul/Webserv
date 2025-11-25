#ifndef SERVER_SOCKET_HPP
# define SERVER_SOCKET_HPP

#include "base_socket.hpp"

class Server_socket : public Base_socket
{
    public:
        Server_socket(const int port) : Base_socket(socket(AF_INET, SOCK_STREAM, 0))
        {
            struct sockaddr_in sockaddr;

            memset(&sockaddr, 0, sizeof(sockaddr));
            sockaddr.sin_family = AF_INET;
            sockaddr.sin_addr.s_addr = INADDR_ANY;
            sockaddr.sin_port = htons(port);

            fcntl(fd, F_SETFL, O_NONBLOCK);
            if (bind(fd, (const struct sockaddr *)&(sockaddr), sizeof(sockaddr)) == -1)
                std::cout << "failed bind" << std::endl;
            if (listen(fd, SOMAXCONN) == -1)
                std::cout << "failed bind" << std::endl;
        };

        bool isServer() const override { return (true); }
};

#endif