/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:15:25 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/27 20:21:18 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHANDLER_HPP
#define CGIHANDLER_HPP

#include "ClientConnection.hpp" //for now
#include "httpResponse.hpp"
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
#include <requestHandler.hpp>

#include "../srcs/client_socket.hpp"

class CgiHandler : RequestHandler {
	private:
		CgiHandler();
		char** build_env(int type);
		Client_socket& client;
		//attributes

	public:
		CgiHandler(Client_socket& client);
		~CgiHandler();
		void startCgi();
		HttpResponse createResponse(Client_socket& client);
		void readFromCgiPipe();

};

#endif
