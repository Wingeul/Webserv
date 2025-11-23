#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Error: cannot create socket\n";
        return 1;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Error: setsockopt\n";
        return 1;
    }

    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Error: bind failed\n";
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        std::cerr << "Error: listen failed\n";
        close(server_fd);
        return 1;
    }

    std::cout << "Server running on port 8080...\n";

    while (true) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            std::cerr << "Error: accept failed\n";
            continue;
        }

        const char* response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 12\r\n"
            "\r\n"
            "Hello world";

        send(client_fd, response, std::strlen(response), 0);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}