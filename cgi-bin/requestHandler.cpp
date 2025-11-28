/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:13:47 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/28 13:12:33 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "requestHandler.hpp"

//creates the array of env variables needed for script execution
char** build_env_python() {
	char** env;

	return (env);
}

char** build_env_php() {
	char** env;

	return (env);
}

//the tiny pipex without waitpid
void	requestHandler::handleCgi(Client_socket& client, const std::string& interpreter) {
	Client_request request = client.getClient_request();
	int	pipe_in[2]; //local
	int	pipe_out[2]; //local

	if (pipe(pipe_in) < 0 || pipe(pipe_out) < 0) {
		throw std::runtime_error("Pipe failed");
	}
	pid_t pid = fork();

	if (pid == 0) {
		//direction Server -> CGI
		if (dup2(pipe_in[0], STDIN_FILENO) < 0) {
			perror("dup2");
			exit (1);
		}
		//direction CGI -> Server
		if (dup2(pipe_out[1], STDOUT_FILENO) < 0) {
			perror("dup2");
			exit (1);
		}
		close(pipe_in[1]);
		close(pipe_out[0]);


		char* argv[] = {
			(char*)"/usr/bin/python3", //add one more if necessary
			(char*)request.getPath().c_str(),
			NULL
		};

		char** env_cgi = build_env(1);
		execve(argv[0], argv, env_cgi);
		//error msg execve failed TODO
		perror("execve failed");
		exit (1);
	}
	else if (pid > 0) {
		close(pipe_in[0]);
		close(pipe_out[1]);

		client.cgi_stdin_fd = pipe_in[1];
		client.cgi_stdout_fd = pipe_out[0];
		fcntl(client.cgi_stdin_fd, F_SETFL, O_NONBLOCK); //essential for nonblocking server
		fcntl(client.cgi_stdout_fd, F_SETFL, O_NONBLOCK);

		if (!client_request.body.empty()) { //avoid python to wait apparently
			client.state = CGI_WRITING_BODY;
			//this applies to POST, but not to GET
		}
		else {
			close(client.cgi_stdin_fd);
			client.cgi_stdin_fd = -1;
			client.state = CGI_READ_RESPONSE;
		}
	}
	else {
		throw std::runtime_error("Fork failed in CGI");
	}
}


void	requestHandler::handleStatic(Client_socket& client) {}

//TODO for Paul: monitor pipe_in[1] for POLLOUT.
//add client states: CGI_WRITING_BODY, CGI_START, CGI_READ_RESPONSE
//send body to cgi_stdin_fd when state is CGI_WRITE_MODE (?)


