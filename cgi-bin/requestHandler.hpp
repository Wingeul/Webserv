/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:17:42 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/28 18:03:56 by jschmitz         ###   ########.fr       */
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
		static void handleCgi(Client_socket& client);

		static void createHttpResponse(Client_socket& client);
		void readFromCgiPipe();
};

#endif
