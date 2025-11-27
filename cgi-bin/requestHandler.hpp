/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:17:42 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/27 20:48:21 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTHANDLER_HPP
#define REQUESTHANDLER_HPP

class RequestHandler {
	private:
		RequestHandler() {} //non-instantiable


	public:
		~RequestHandler() {}
		static void handleStatic(ClientConnection& client);
		static void handleCgi(ClientConnection& client, const std::string& interpreter);


};

#endif
