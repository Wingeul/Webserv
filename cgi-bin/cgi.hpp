/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:13:18 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/26 21:54:58 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <unistd.h> //for fork and execve
#include <fcntl.h> //for fcntl
#include <sys/types.h> //for fork
#include <vector>
#include <string.h>

#include "../srcs/client_socket.hpp"

//placeholder:
class Client_request {
	public:
		std::string path;
		std::string body;
		int state;
		int cgi_stdin_fd;
		int cgi_stdout_fd;
};

#endif
