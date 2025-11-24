/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testscript.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:26:22 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/24 15:28:33 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testscript.hpp"

int main() {
	int pipe_in[2];
	int pipe_out[2];
	pipe(pipe_in);
	pipe(pipe_out);

	pid_t pid = fork();

	if (pid == 0){
		dup2(pipe_in[0], STDIN_FILENO);
		dup2(pipe_out[1], STDOUT_FILENO);
		close(pipe_in[1]);
		close(pipe_out[0]);
		std::vector<char *> env;
		env.push_back(strdup("CONTENT_LENGTH=11"));
		env.push_back(strdup("FOO=bar"));
		env.push_back(NULL);

		char* for_env[] = { strdup("env"), NULL };
		execve("/usr/bin/cat", for_env, env.data());
		perror("execve failed");
		_exit(1);
	}
	//parent:
	close(pipe_in[0]);
	close(pipe_out[1]);

	const char* msg = "hellooooo";
	write(pipe_in[1], msg, strlen(msg));
	close(pipe_in[1]);
	char buf[256];
	ssize_t n;
	while ((n = read(pipe_out[0], buf, sizeof(buf))) > 0) {
		std::cout.write(buf, n);
	}
	close(pipe_out[0]);

	int status;
	waitpid(pid, &status, 0);
	return (0);
}
