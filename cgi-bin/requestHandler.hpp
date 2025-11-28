/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:17:42 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/28 12:48:00 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTHANDLER_HPP
#define REQUESTHANDLER_HPP

#include <iostream>
#include "../srcs/client_socket.hpp"

class RequestHandler {
	private:
		RequestHandler() {} //non-instantiable
		~RequestHandler() {}

	public:
		//static methods
		static void handleStatic(Client_socket& client);
		static void handleCgi(Client_socket& client, const std::string& interpreter);

		void createHttpResponse(Client_socket& client);
		void readFromCgiPipe();
};

#endif
