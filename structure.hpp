#ifndef STRUCTURE_HPP
# define STRUCTURE_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>
#include <cstring>
#include <unistd.h>


class Structure
{
    private:
        struct sockaddr_in my_sockaddr;
        struct pollfd my_pollfd;
        socklen_t addrlen;
    public:
        Structure();
        ~Structure(){};

        pollfd* getMypollfd();

        const sockaddr* getSockAddr();
        socklen_t getSize();
        nfds_t getEvent();
        void setFd(int sock);
};

void main_loop();


#endif