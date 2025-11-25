#ifndef BASE_SOCKET_HPP
# define BASE_SOCKET_HPP

#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <iostream>

class Base_socket {
    protected:
        int fd;
    public:
        Base_socket(int fd) : fd(fd) {}
        virtual ~Base_socket() { if (fd >= 0) close(fd); }

        int getFd() const { return fd; }

        virtual bool isServer() const = 0;
};


#endif