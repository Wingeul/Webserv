#ifndef STRUCTURE_HPP
# define STRUCTURE_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <vector>
#include "pollEntry.hpp"


class Structure
{
    private:
        std::vector<PollEntry> pollEntries;
    public:
        Structure(){};
        ~Structure(){};

        void addListener(std::vector <int> ports, int portsparser);
        void addClient(int client_fd);

        pollfd* getMypollfd();

        std::vector <PollEntry> getEntries();
        PollEntry getEntry(int index);

        void setRevent(short revent);

        const sockaddr* getSockAddr();
        socklen_t getSize();
        nfds_t getEvent();
};

void main_loop();
std::vector <struct pollfd> makeArray(Structure st);

#endif