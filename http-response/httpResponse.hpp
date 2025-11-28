/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:07:40 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/28 12:38:43 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <iostream>
#include <map>
#include "../srcs/client_socket.hpp"

class HttpResponse {

	private:
		std::string createReasonPhrase_(int status_code) const;
		std::string	body_;
		int	status_code_; //for example 200, 404, 500
		std::map<std::string, std::string>	headers_;

	public:
		HttpResponse();
		HttpResponse(std::string cgi_output_buffer);
		HttpResponse(const HttpResponse& src);
		~HttpResponse();
		HttpResponse& operator=(const HttpResponse& src);

		void setHeader(const std::string& key, const std::string& value);
		std::string serialize() const;
};

#endif
