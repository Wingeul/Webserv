/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:07:40 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/28 17:53:43 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <iostream>
#include <map>
#include <sstream>
#include "../srcs/client_socket.hpp"

class HttpResponse {

	private:
		std::string	body_;
		int	status_code_; //for example 200, 404, 500
		std::string status_msg_;
		std::map<std::string, std::string>	headers_;

	public:
		HttpResponse();
		HttpResponse(std::string cgi_output_buffer);
		HttpResponse(const HttpResponse& src);
		~HttpResponse();
		HttpResponse& operator=(const HttpResponse& src);

		//setters
		void setStatusCode(int status_code);
		void setStatusMessage(std::string message);
		void setBody(std::string body);

		//getters
		std::string getBody();

		//member functions
		void addToHeader(const std::string& key, const std::string& value);
		bool findInHeader(const std::string& key);
		std::string	sizeHeader();

		std::string serialize() const;
};

#endif
