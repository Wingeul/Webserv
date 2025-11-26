#ifndef START_LINE_HPP
# define START_LINE_HPP

#include "client_socket.hpp"
#include "utils.hpp"

int extract_path(Client_socket &client);
int extract_version(Client_socket &client);
int extract_method(Client_socket &client);
int handle_start_line(Client_socket &client);

#endif