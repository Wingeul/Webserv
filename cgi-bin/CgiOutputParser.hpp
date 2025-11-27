/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiOutputParser.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:10:53 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/27 19:03:32 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIOUTPUTPARSER_HPP
#define CGIOUTPUTPARSER_HPP

#include "../http-response/httpResponse.hpp"

class CgiOutputParser {
	public:
		CgiOutputParser() {}
		CgiOutputParser(CgiOutputParser& src);
		~CgiOutputParser() {}
		CgiOutputParser& operator=(CgiOutputParser& src);

		HttpResponse parse(const std::string& raw_cgi_output);

	private:
		void parseHeaders(const std::string& headerBlock, \
			HttpResponse& response);
};

#endif
