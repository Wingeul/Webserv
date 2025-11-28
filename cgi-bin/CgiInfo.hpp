/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiInfo.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:21:35 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/28 18:24:17 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

struct CgiInfo {
	pid_t		pid; //possible to kill process if timed out
	int			cgi_stdin_fd;  // server -> cgi
	int			cgi_stdout_fd; // cgi -> server
	std::string	cgi_output_buffer;

	CgiInfo() : pid(-1), cgi_stdin_fd(-1), cgi_stdout_fd(-1) {}
};
