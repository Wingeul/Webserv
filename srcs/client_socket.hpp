#ifndef CLIENT_SOCKET_HPP
# define CLIENT_SOCKET_HPP

#include "base_socket.hpp"
#include "client_request.hpp"
#include "../http-response/httpResponse.hpp"

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
        //added
        httpResponse http_response;

        //for cgi
        int   _cgi_stdin_fd;
        int   _cgi_stdout_fd;
        pid_t _cgi_pid; //possible to kill process if timed out
        std::string _cgi_output_buffer;
        //end new stuff

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
        //new
        HttpResponse& createHttpResponse() {
            return (HttpResponse(_cgi_output_buffer));
        }
        //for cgi
        int getCgiReadFd() const { return (_cgi_stdout_fd); }
        int getCgiWriteFd() const { return (_cgi_stdin_fd); }
        void attachCgi(pid_t pid, int pipe_in, int pipe_out) {
            _cgi_pid = pid;
            _cgi_stdin_fd = pipe_in;
            _cgi_stdout_fd = pipe_out;
         }

        void appendCgiOutput(const char* data, size_t size) {
            _cgi_output_buffer.append(data, size);
        }

        std::string& getCgiOutputBuffer() {
            return (_cgi_output_buffer);
        }

        void	readFromCgiPipe(void) {
            char buf[4096];
            ssize_t bytes_read = read(_cgi_stdout_fd, buf, 4096);
            if (bytes_read > 0) {
                _cgi_output_buffer.append(buf, bytes_read);
            }
            else if (bytes_read == 0) {
                //EOF
            }
        }
        //end new stuff
};

#endif
