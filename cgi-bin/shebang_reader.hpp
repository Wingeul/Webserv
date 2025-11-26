/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shebang_reader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:26:54 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/26 15:35:51 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHEBANG_READER_HPP
#define SHEBANG_READER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <unistd.h> //for fork and execve
#include <sys/types.h> //for fork
#include <vector>
#include <string.h>
#include <sys/types.h> //for waitpid
#include <sys/wait.h> //for waitpid

class HttpRequest {
	private:
		//char**	envptr; //to avoid free in child process ?
		bool	requiresCgi;
		int		cgi_stdin_fd[2];
		int		cgi_stdout_fd[2];
		std::string path;

	public:
		//char**	getEnvp();
		bool	getRequiresCgi();
		int*	getCgiStdinFd();
		int*	getCgiStdoutFd();
		std::string getPath();

		//void	setEnvp(char** envp);

};

#endif
