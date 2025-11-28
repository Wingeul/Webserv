#ifndef CLIENT_SOCKET_HPP
# define CLIENT_SOCKET_HPP

#include "base_socket.hpp"
#include "client_request.hpp"
#include "../http-response/httpResponse.hpp"
#include "../cgi-bin/CgiInfo.hpp"

class Client_socket : public Base_socket
{
    public:
        enum ParseState
        {
            START_LINE,
            HEADERS,
            BODY,
            COMPLETED,
            CGI_WRITING_BODY,
            CGI_START,
            CGI_READ_RESPONSE,
            PARSE_CGI_RESPONSE
        };

    private:
        std::vector<char> client_buffer;
        size_t parsed_bytes;
        ParseState state;
        Client_request Client_req;
        //added
        HttpResponse http_response;
        CgiInfo cgi_info;

    public:
        Client_socket(int client_fd) : Base_socket(client_fd), parsed_bytes(0), state(START_LINE) {};

        ssize_t fill_client_buffer();

        void nextstate();

        std::vector<char>& getClient_buffer();
        Client_request& getClient_request();
        size_t& getParsed_bytes();
        ParseState& getState() const;

        void setParsed_bytes(size_t t);

        void addToParser_bytes(size_t t);

        bool isServer() const override { return (false); }
        //new
        HttpResponse& getHttpResponse() {
            return (http_response);
        }

        void setState(ParseState new_state) {
            state = new_state;
        }

        //for cgi
        CgiInfo& getCgiInfo() {
            return (cgi_info);
        }

        void attachCgi(pid_t pid, int pipe_in, int pipe_out) {
            cgi_info.pid = pid;
            cgi_info.cgi_stdin_fd = pipe_in;
            cgi_info.cgi_stdout_fd = pipe_out;
         }

        void appendCgiOutput(const char* data, size_t size) {
            cgi_info.cgi_output_buffer.append(data, size);
        }

        std::string& getCgiOutputBuffer() {
            return (cgi_info.cgi_output_buffer);
        }
        //end new stuff
};

#endif
