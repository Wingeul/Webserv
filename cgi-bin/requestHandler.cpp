/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:13:47 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/28 20:37:19 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "requestHandler.hpp"
#include <vector>
#include <algorithm>

//transform the headers into env variables for execve
void addHeaderEnvs(std::vector<std::string>& env, \
		const std::map<std::string, std::string>& headers) {

	std::map<std::string,std::string>:: const_iterator it;
	for (it = headers.begin(); it != headers.end(); it++) {
		std::string key = it->first;
		std::string value = it->second;
		if (key == "Content-Length" || key == "Content-Type") {
			continue;
		}
		std::transform(key.begin(), key.end(),key.begin(), ::toupper);
		std::replace(key.begin(), key.end(), '-', '_');
		std::string env_var = "HTTP_" + key + "=" + value;
		env.push_back(env_var);
	}
}

char** convertVectorToCharArray(std::vector<std::string> env) {

	char** envp = new char*[env.size() + 1];

	for (size_t i = 0; i < env.size(); i++) {
		envp[i] = new char[env[i].size() + 1];
		std::strcpy(envp[i], env[i].c_str());
	}

	envp[env.size()] = NULL;
	return (envp);
}

//creates the array of env variables needed for script execution
char** build_env(Client_request request) {

	std::vector<std::string> env;

    env.push_back("REQUEST_METHOD=" + request.getMethod());
    env.push_back("QUERY_STRING=" + request.getQuery());
    env.push_back("SCRIPT_FILENAME=" + request.getPath());
    env.push_back("CONTENT_LENGTH=" + request.getHeaders("Content-Length"));
    env.push_back("CONTENT_TYPE=" + request.getHeaders("Content-Type"));
	//still missing some

	//important for PHP
    env.push_back("REDIRECT_STATUS=200");

   	addHeaderEnvs(env, request.getHeaders());

	char** envp = convertVectorToCharArray(env);
    return (envp);
}

//the tiny pipex without waitpid
void	handleCgi(Client_socket& client) {

	Client_request request = client.getClient_request();
	int	pipe_in[2]; //local
	int	pipe_out[2]; //local

	if (pipe(pipe_in) < 0 || pipe(pipe_out) < 0) {
		throw std::runtime_error("Pipe failed");
	}

	pid_t pid = fork();

	if (pid == 0) {
		if (dup2(pipe_in[0], STDIN_FILENO) < 0) { //direction Server -> CGI
			perror("dup2");
			exit (1);
		}
		if (dup2(pipe_out[1], STDOUT_FILENO) < 0) { //direction CGI -> Server
			perror("dup2");
			exit (1);
		}
		close(pipe_in[1]);
		close(pipe_out[0]);
		char* argv[] = {
			//add path to interpreter, //add one more if necessary
			(char*)request.getPath().c_str(),
			NULL
		};
		char** env_cgi = build_env(request);
		execve(argv[0], argv, env_cgi);
		//error msg execve failed TODO
		perror("execve failed");
		freeCharArray(env_cgi);
		exit (1);
	}
	else if (pid > 0) {
		close(pipe_in[0]);
		close(pipe_out[1]);

		client.attachCgi(pid, pipe_in[1], pipe_out[0]);
		/* client.cgi_stdin_fd = pipe_in[1];
		client.cgi_stdout_fd = pipe_out[0]; */
		fcntl(client.cgi_stdin_fd, F_SETFL, O_NONBLOCK); //essential for nonblocking server
		fcntl(client.cgi_stdout_fd, F_SETFL, O_NONBLOCK);

		if (!client_request.body.empty()) { //avoid python to wait apparently
			client.getState() = CGI_WRITING_BODY;
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

//TODO
void	requestHandler::handleStatic(Client_socket& client) {}



//TODO for Paul: monitor pipe_in[1] for POLLOUT.
//add client states: CGI_WRITING_BODY, CGI_START, CGI_READ_RESPONSE
//send body to client_socket.cgi_info.cgi_stdin_fd and when state is CGI_WRITING_BODY


