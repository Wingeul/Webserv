/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:13:47 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/26 21:33:09 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"

char** build_env(int type) {
	char** env;
	if (type == 1) {
		//build python env
	}
	return (env);
}

void	startCgi(Client_request& client) {
//start pipes
//give body data to ClientConnection (?)
//set to CGI_WRITE_MODE
	int	pipe_in[2]; //local
	int	pipe_out[2]; //local

	if (pipe(pipe_in) < 0 || pipe(pipe_out) < 0) {
		throw std::runtime_error("Pipe failed");
	}

	pid_t pid = fork();

	// child
	if (pid == 0) {
		//Server -> CGI
		if (dup2(pipe_in[0], STDIN_FILENO) < 0) {
			perror("dup2");
			exit (1);
		}
		//CGI -> Server
		if (dup2(pipe_out[1], STDOUT_FILENO) < 0) {
			perror("dup2");
			exit (1);
		}
		close(pipe_in[1]);
		close(pipe_out[0]);

		char* argv[] = {
			(char*)"/usr/bin/python3",
			(char*)client.path.c_str(),
			NULL
		};
		char** env_cgi = build_env(1);
		execve(argv[0], argv, env_cgi); //TODO
		//error msg execve failed TODO
		//exit (1);
	}

	//parent
	else if (pid > 0) {
		close(pipe_in[0]);
		close(pipe_out[1]);

		client.cgi_stdin_fd = pipe_in[1];
		client.cgi_stdout_fd = pipe_out[0];
		fcntl(client.cgi_stdin_fd, F_SETFL, O_NONBLOCK); //essential for nonblocking server
		fcntl(client.cgi_stdout_fd, F_SETFL, O_NONBLOCK);

		if (!client.body.empty()) { //avoid python to wait apparently
			client.state = CGI_WRITING_BODY;
		}
		else {
			close(client.cgi_stdin_fd);
			client.cgi_stdin_fd = -1;
			client.state = CGI_READ_MODE;
		}
	}
	else {
		throw std::runtime_error("Fork failed in CGI");
	}
}

//TODO for Paul: monitor pipe_in[1] for POLLOUT.
//add client states: CGI_WRITING_BODY, CGI_WRITE_MODE, CGI_READ_MODE
//send body to cgi_stdin_fd
