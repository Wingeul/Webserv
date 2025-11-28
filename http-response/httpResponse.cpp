/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:54:28 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/28 12:40:51 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "httpResponse.hpp"

//CONSTRUCTORS ETC
HttpResponse::HttpResponse() : status_code_(200) {}

HttpResponse::HttpResponse(std::string _cgi_output_buffer) {

}

HttpResponse::HttpResponse(const HttpResponse& src) :
			status_code_(src.status_code_) {}

HttpResponse::~HttpResponse() {}

HttpResponse& HttpResponse::operator=(const HttpResponse& src) {
	if (this != &src) {
		this->status_code_ = src.status_code_;
	}
	return (*this);
}

//MEMBER FUNCTIONS


std::string HttpResponse::createReasonPhrase_(int status_code) const {
	std::string reason;
	//
	return (reason);
}


void HttpResponse::setHeader(const std::string& key, const std::string& value) {
	headers_[key] = value;
}

//serialize converts into a string that'll be sent to socket (does the
//opposite of the request parser)
std::string HttpResponse::serialize() const {

}
