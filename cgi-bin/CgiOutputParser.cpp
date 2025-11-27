/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiOutputParser.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:22:01 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/27 17:17:16 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../http-response/httpResponse.hpp"
#include "CgiOutputParser.hpp"

CgiOutputParser::CgiOutputParser(CgiOutputParser& src) {

}

CgiOutputParser::~CgiOutputParser() {}

CgiOutputParser& CgiOutputParser::operator=(CgiOutputParser& src) {}

HttpResponse CgiOutputParser::parse(const std::string& raw_cgi_output) {}

void CgiOutputParser::parseHeaders(const std::string& headerBlock, \
			HttpResponse& response) {}
