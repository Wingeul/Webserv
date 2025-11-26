#ifndef POLLENTRY_HPP
# define POLLENTRY_HPP

#include <poll.h>

class PollEntry
{
    private:
        struct pollfd pollfd;
        bool isListener;
    public:
        PollEntry(){};
        PollEntry(struct pollfd pollfd, bool isListener)
        {
            this->pollfd = pollfd;
            this->isListener = isListener;
        };
        ~PollEntry(){};

        struct pollfd getPollfd(){return (this->pollfd);};
        bool getIsListener(){return (this->isListener);};

        void setRevent(short Revent){this->pollfd.revents = Revent;};

        void setIsListener(bool toSet){this->isListener = toSet;};
};

#endif