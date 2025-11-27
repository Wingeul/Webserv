/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:07:40 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/27 19:02:52 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <iostream>
#include <map>
#include "../srcs/client_socket.hpp"

class HttpResponse {

	private:
		std::string createReasonPhrase(int status_code) const;

	public:
		int	status_code; //for example 200, 404, 500
		std::string	body;
		std::map<std::string, std::string>	headers;

		HttpResponse() : status_code(200) {}
		HttpResponse(const HttpResponse& src) : \
			status_code(src.status_code) {}
		~HttpResponse();
		HttpResponse& operator=(const HttpResponse& src);

		void setHeader(const std::string& key, const std::string& value) {
			headers[key] = value;
		}

		//converts into a string that'll be sent to socket, does the
		//opposite of the request parser
		std::string serialize() const;
};

#endif
