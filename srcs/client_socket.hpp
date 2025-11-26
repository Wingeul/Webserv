#ifndef CLIENT_SOCKET_HPP
# define CLIENT_SOCKET_HPP

#include "base_socket.hpp"
#include "client_request.hpp"

class Client_socket : public Base_socket
{
    public:
        enum ParseState
        {
            START_LINE,
            HEADERS,
            BODY,
            COMPLETED
        };

    private:
        std::vector<char> client_buffer;
        size_t parsed_bytes;
        ParseState state;
        Client_request Client_req;
    public:
        Client_socket(int client_fd) : Base_socket(client_fd), parsed_bytes(0), state(START_LINE) {};

        ssize_t fill_client_buffer();

        void nextstate();

        std::vector<char>& getClient_buffer();
        Client_request& getClient_request();
        size_t& getParsed_bytes();
        ParseState getState() const;

        void setParsed_bytes(size_t t);
        
        void addToParser_bytes(size_t t);

        bool isServer() const override { return (false); }
};

#endif