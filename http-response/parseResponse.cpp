/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseResponse.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:04:27 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/28 13:57:21 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parseResponse.hpp"

//is called when loop reads EOF from pipe
//this will fill up the std::string cgi_output_buffer_ via append
void read_cgi_output(Client_request& client) {//or should it be client ?

	char buffer[4096];

	// Read raw bytes
	ssize_t bytes_read = read(client.cgi_stdout_fd, buffer, sizeof(buffer));
	if (bytes_read > 0) {

	// APPEND raw bytes to the std::string
	client.cgi_output_buffer_.append(buffer, bytes_read);
	}

	else if (bytes_read == 0) {
	// EOF: CGI is finished.
		close(client.cgi_stdout_fd);
		client.state = PARSE_CGI_RESPONSE;
	}
}

void parse_cgi_output(Client_request& client) {
	std::string& raw = client.cgi_output_buffer;
	HttpResponse& response = client.httpResponse;

	size_t header_end = raw.find("\r\n\r\n");
	size_t delim_len = 4;

	if (header_end == std::string::npos) {
		//fallback if it hasn't been found
		header_end = raw.find("\n\n");
		delim_len = 2;
	}

	std::string headers_part;

	if (header_end)
}
