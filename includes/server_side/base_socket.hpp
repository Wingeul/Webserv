#ifndef BASE_SOCKET_HPP
# define BASE_SOCKET_HPP

#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cstddef>

class Base_socket {
    protected:
        int fd;
        bool isServer;
    public:
        Base_socket(int fd, bool server) : fd(fd), isServer(server) {}
        virtual ~Base_socket() { if (fd >= 0) close(fd); }

        int getFd() const { return fd; }
        bool getIsServer() const { return isServer; }
};


#endif