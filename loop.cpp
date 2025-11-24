#include "structure.hpp"

Structure::Structure()
{
    my_sockaddr.sin_family = AF_INET;
    my_sockaddr.sin_addr.s_addr = INADDR_ANY;
    my_sockaddr.sin_port = htons(8080);

    my_pollfd.fd = -1;
    my_pollfd.events = POLLIN;
    my_pollfd.revents = -1;
}

void main_loop()
{
    Structure st;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    fcntl(sock, F_SETFL, O_NONBLOCK);

    st.setFd(sock);

    bind(sock, st.getSockAddr(), st.getSize());

    listen(sock, SOMAXCONN);

    while (true) {
        int client_fd = accept(sock, NULL, NULL);

        const char* response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 12\r\n"
            "\r\n"
            "Hello world";

        send(client_fd, response, std::strlen(response), 0);
        close(client_fd);
    }
    close(sock);
    //poll(st.getMypollfd(), st.getEvent(), -1);
}

const sockaddr* Structure::getSockAddr()
{
    return ((const struct sockaddr *)&(this->my_sockaddr));
}

socklen_t Structure::getSize() 
{
    return (sizeof(my_sockaddr));
}

void Structure::setFd(int sock)
{
    this->my_pollfd.fd = sock;
}

pollfd* Structure::getMypollfd()  
{
    return (&(this->my_pollfd));
}

nfds_t Structure::getEvent() 
{
    return (this->my_pollfd.events);
}
