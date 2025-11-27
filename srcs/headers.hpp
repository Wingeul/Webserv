#ifndef HEADERS_HPP
# define HEADERS_HPP

#include <algorithm>
#include "client_socket.hpp"
#include "utils.hpp"

int has_full_headers(Client_socket &client);
int fill_headers_map(Client_socket &client);
int handle_headers(Client_socket &client);

#endif