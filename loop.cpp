#include "structure.hpp"

void main_loop()
{
    /*
    TODO ->parse config and get a struct with all the info
    */
    std::vector <int> ports = {8080, 8002};

    Structure st;
    int vsize = ports.size();
    int portsparser = 0;
    while (portsparser< vsize)
    {
        st.addListener(ports, portsparser);
        portsparser++;
    }

    while (true)
    {
        std::vector <struct pollfd> pollFdArray = makeArray(st);
        int n = poll(pollFdArray.data(), pollFdArray.size(), -1);
        if (n < 0)
        {
            //FAIL STATE
        }
        for(size_t i = 0; i < pollFdArray.size(); i++)
        {
            st.getEntry(i).setRevent(pollFdArray[i].revents);
            if (pollFdArray[i].revents == 0)
                continue;
            if (st.getEntry(i).getIsListener() && (pollFdArray[i].revents & POLLIN))
            {
                struct sockaddr_in client_addr;
                socklen_t addrlen = sizeof(client_addr);
                int client_fd = accept(pollFdArray[i].fd, (struct sockaddr *)&client_addr, &addrlen);
                if (client_fd < 0)
                {
                    //FAIL STATE
                }else{
                    st.addClient(client_fd);
                    const char* response =
                        "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 12\r\n"
                        "\r\n"
                        "Hello world";

                        send(client_fd, response, std::strlen(response), 0);
                }
            }   
        }
    }

}

void Structure::addListener(std::vector <int> ports, int portsparser)
{
    struct sockaddr_in sockaddr;

    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(ports[portsparser]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK);
    bind(sock, (const struct sockaddr *)&(sockaddr), sizeof(sockaddr));
    listen(sock, SOMAXCONN);

    struct pollfd pfd;
    pfd.fd = sock;
    pfd.events = POLLIN;
    pfd.revents = 0;

    this->pollEntries.push_back(PollEntry(pfd, true));
}

void Structure::addClient(int client_fd)
{
    struct pollfd client_pfd;
    client_pfd.fd = client_fd;
    client_pfd.events = POLLIN;
    client_pfd.revents = 0;
    this->pollEntries.push_back(PollEntry(client_pfd, false));
}

std::vector <struct pollfd> makeArray(Structure st)
{
    std::vector <struct pollfd> ret;
    for(size_t i = 0; i < st.getEntries().size(); i++)
    {
        ret.push_back(st.getEntry(i).getPollfd());
    }
    return (ret);
}

std::vector <PollEntry> Structure::getEntries()
{
    return (this->pollEntries);
}

PollEntry Structure::getEntry(int index)
{
    return (this->pollEntries[index]);
}
