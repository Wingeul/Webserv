/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:21:02 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/27 15:18:54 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//merge with Paul's version!! or integrate, into Client_socket probably

#ifndef CLIENTCONNECTION_HPP
#define CLIENTCONNECTION_HPP

#include <iostream>
#include "../http-response/httpResponse.hpp"

struct ClientConnection {
	//socket fd, request object etc

	//for CGI:
	int		cgi_stdin_fd;	// Pipe to child
	int		cgi_stdout_fd;	// Pipe from child
	pid_t	cgi_pid;		// Child PID

	//buffer
	std::string		cgi_output_buf; //raw data from pipe put here via append

	//response
	HttpResponse	http_response;
};

#endif
