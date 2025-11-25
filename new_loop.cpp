#include "server_socket.hpp"
#include "client_socket.hpp"

void add_to_epoll(const int epoll_fd, Base_socket &s)
{
    struct epoll_event ev{};
    ev.events = EPOLLIN;
    ev.data.ptr = &s;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, s.getFd(), &ev) == -1)
    {
        //TODO
    }

}

void loop()
{
    int epoll_fd = epoll_create1(EPOLL_CLOEXEC);
    struct epoll_event events[64];

    Server_socket ss1 = Server_socket(8080);
    Server_socket ss2 = Server_socket(8002);
    add_to_epoll(epoll_fd, ss1);
    add_to_epoll(epoll_fd, ss2);

    while (true)
    {
        int n = epoll_wait(epoll_fd, events, 64, -1);
        if (n == -1)
            //TODO
        for (int i = 0; i < n; i++)
        {
            Base_socket* sock = static_cast<Base_socket*>(events[i].data.ptr);

            if (sock->isServer())
            {
                while(true)
                {
                    Server_socket* server = static_cast<Server_socket*>(sock);
                    int client_fd = accept(server->getFd(), nullptr, nullptr);
                    if (client_fd == -1)
                        break;
                    if (client_fd >= 0)
                    {
                        fcntl(client_fd, F_SETFL, O_NONBLOCK);
                        Client_socket* client = new Client_socket(client_fd);
                        add_to_epoll(epoll_fd, *client);
                    }
                }
            }else
            {
                Client_socket* client = static_cast<Client_socket*>(sock);
            }
        }
    }
}

int main ()
{
    loop();
    return (0);
}
