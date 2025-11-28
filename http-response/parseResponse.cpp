/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseResponse.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:04:27 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/28 18:43:46 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "httpResponse.hpp"

//is called when loop reads EOF from pipe
//this will fill up the std::string cgi_output_buffer_ via append
void read_cgi_output(Client_socket& client) {//or should it be client ?

	CgiInfo cgi_info = client.getCgiInfo();
	char buffer[4096];

	// Read raw bytes
	ssize_t bytes_read = read(cgi_info.cgi_stdout_fd, buffer, sizeof(buffer));
	if (bytes_read > 0) {

	// APPEND raw bytes to the std::string
	cgi_info.cgi_output_buffer.append(buffer, bytes_read);
	}

	else if (bytes_read == 0) {
	// EOF: CGI is finished.
		close(cgi_info.cgi_stdout_fd);
		client.setState(PARSE_CGI_RESPONSE);
	}
}

void parse_cgi_output(Client_socket& client) {
	std::string& raw = client.getCgiOutputBuffer();
	HttpResponse& response = client.getHttpResponse();

	size_t header_end = raw.find("\r\n\r\n");
	size_t delim_len = 4;

	if (header_end == std::string::npos) {
		//fallback if it hasn't been found
		header_end = raw.find("\n\n");
		delim_len = 2;
	}

	std::string headers_part;

	if (header_end != std::string::npos) {
		//headers found
		headers_part = raw.substr(0, header_end);
		response.setBody(raw.substr(header_end + delim_len));
	}
	else {
		//treat everything as body
		response.setBody(raw);
	}

	std::stringstream ss(headers_part);
	std::string line;

	while (std::getline(ss, line)) {
		if (line.empty() || line == "\r")
			continue;
		//trimming the line
		if (line[line.length() - 1] == '\r') {
			line.erase(line.length() - 1);
		}
		size_t colon_pos = line.find(':');
		if (colon_pos != std::string::npos) {
			std::string key = line.substr(0, colon_pos);
			std::string value = line.substr(colon_pos + 1);
			//trimming value
			size_t first_char = value.find_first_not_of(' ');
			if (first_char != std::string::npos) {
				value = value.substr(first_char);
			}
			//I still have to look this one up!
			if (key == "Status") {
				response.setStatusCode(std::atoi(value.c_str()));
				size_t space_pos = value.find(' ');
				if (space_pos != std::string::npos) {
					response.setStatusMessage(value.substr(space_pos + 1));
				}
			}
			else {
				response.addToHeader(key, value);
			}
		}
	}
	if (!response.findInHeader("Content-Length")) {
		response.addToHeader("Content-Length", response.sizeHeader());
	}
}
