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

void cut_vect(std::vector<char> &vect, int size)
{
    vect.erase(vect.begin(), vect.begin() + size);
}

std::string extract_path(std::vector<char> &vect)
{
    std::string ret;

    size_t i = 0;
    while (i < vect.size() && vect[i] != ' ' && vect[i] != '\n' && vect[i] != '\r')
    {
        ret += vect[i];
        i++;
    }
    if (i>0)
        cut_vect(vect, i + 1);
    return (ret);
}

std::string extract_version(std::vector<char> &vect)
{
    size_t i = 0;

    while (i<vect.size() && vect[i] != '\n')
        i++;
    size_t line_end = i;
    if (i > 0 && vect[i-1] == '\r')
        line_end = i-1;
    std::string ret(vect.begin(), vect.begin() + line_end);
    cut_vect(vect, i + 1);
    return (ret);
}

bool isIdentical(std::vector<char> vect, std::string str)
{
    if (vect.size() < str.size())
        return false;
    for (int i = 0; i < str.size(); i++)
    {
        if(vect[i] != str[i])
            return (false);
    }
    return (true);
}

int process_request(Client_socket *client)
{

    if (isIdentical(client->getClient_buffer(), "GET "))
    {
        cut_vect(client->getClient_buffer(), 4);
        //apply GET
        std::cout << "is a GET method" << std::endl;
        return (0);
    }
    else if (isIdentical(client->getClient_buffer(), "POST "))
    {
        cut_vect(client->getClient_buffer(), 5);
        //apply POST
        std::cout << "is a POST method" << std::endl;
        return (0);
    }
    else if (isIdentical(client->getClient_buffer(), "DELETE "))
    {
        cut_vect(client->getClient_buffer(), 7);
        //apply DELETE
        std::cout << "is a DELETE method" << std::endl;
        return (0);
    }
    else
        return (-1);
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
    //this write is just for test
    std::cout.write(client->getClient_buffer().data(), client->getClient_buffer().size());
    std::cout << std::endl;
    if (process_request(client) == -1)
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
