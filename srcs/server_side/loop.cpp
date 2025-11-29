#include "../../includes/server_side/server_socket.hpp"
#include "../../includes/server_side/handle_request.hpp"
#include "../../includes/client_side/client_socket.hpp"
#include "../../includes/request_parsing/start_line.hpp"
#include "../../includes/request_parsing/headers.hpp"
#include "../../includes/request_parsing/body.hpp"

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

int handle_server(Base_socket *sock, int epoll_fd)
{
    Server_socket* server = static_cast<Server_socket*>(sock);
    
    while(true)
    {
        int client_fd = accept(server->getFd(), nullptr, nullptr);
        if (client_fd == -1)
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                break;
            else
                return -1;
        if (client_fd >= 0)
        {
            fcntl(client_fd, F_SETFL, O_NONBLOCK);
            Client_socket* client = new Client_socket(client_fd);
            add_to_epoll(epoll_fd, *client);
        }
    }
    return (0);
}

int parse_request(Client_socket &client)
{
    int return_status = 0;
    switch (client.getState())
    {
        case Client_socket::START_LINE:
            return_status = handle_start_line(client);
            if (return_status > -1)
                return (parse_request(client));
            return (return_status);
        case Client_socket::HEADERS:
            return_status = handle_headers(client);
            if (return_status > -1)
                return parse_request(client);
            return (return_status);
        case Client_socket::BODY:
            return_status = handle_body(client);
            if (return_status > -1)
                return parse_request(client);
            return (return_status);
        case Client_socket::COMPLETED:
            return (handle_request(client));
    }
    return (return_status);
}

int handle_client(Base_socket *sock, int epoll_fd)
{
    Client_socket* client = static_cast<Client_socket*>(sock);

    ssize_t data_received = client->fill_client_buffer();

    if (data_received <= 0)
    {
        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client->getFd(), nullptr);
        close(client->getFd());
        delete client;
        return ((int)data_received);
    }
    if (parse_request(*client) == -1)
    {
        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client->getFd(), nullptr);
        close(client->getFd());
        delete client;
    }
    return (0);
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
        {
            if (errno == EINTR)
                continue;
            //TODO
            break;
        }
        for (int i = 0; i < n; i++)
        {
            Base_socket* sock = static_cast<Base_socket*>(events[i].data.ptr);

            if (sock->isServer())
            {
                if (handle_server(sock, epoll_fd) == -1)
                    break;
            }else
            {
                handle_client(sock, epoll_fd);
            }
        }
    }
}

int main ()
{
    loop();
    return (0);
}
