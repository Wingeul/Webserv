#include "shebang_reader.hpp"

//writing in pipe only works if big bodies are rejected (413 Payload Too Large)

bool	HttpRequest::getRequiresCgi() {
	return (this->requiresCgi);
}

//invalid CGI if script has no shebang??

//not tested yet
bool has_shebang(const std::string &path) {
	std::ifstream script(path.c_str());
	if (!script.is_open()) {
		//throw error
	}
	std::string line;
	std::getline(script, line);
	if (line.rfind("#!", 0) == 0) {
		script.close();
		return (true);
	}
	script.close();
	return (false);
}

//example for a shebang line: #!/usr/bin/env python3 -O
std::string interpret_shebang(const std::string &path) {
	std::ifstream script(path.c_str());
	if (!script.is_open()) {
		//throw error
	}
	std::string line;
	std::getline(script, line);
	if (line.rfind("#!", 0) == 0) {
		return (line.substr(2));
	}
	return ("");
}

//splits the shebang line into it's components
std::vector<std::string> split_shebang(const std::string &line) {
	std::istringstream iss(line);
	std::vector<std::string> vec;
	std::string word;
	while (iss >> word) {
		vec.push_back(word);
	}
	return (vec);
}


std::vector<char *> build_args(const std::vector<std::string> &vec, const std::string &script) {
	std::vector<char *> args;
	for (size_t i = 0; i < vec.size(); i++) {
		args.push_back(const_cast<char*>(vec[i].c_str()));
	}
	args.push_back(const_cast<char*>(script.c_str()));
	args.push_back(NULL);
	return (args);
}

//add the part with the pipes??
void run_cgi_script_in_child(int cgi_stdin_fd[2], int cgi_stdout_fd[2], \
		const std::string &path, char* const envp[], int client_fd_in, \
		int client_fd_out) {
	//test if script can be opened before ?
	std::vector<std::string> vec;
	std::vector<char *> args;

	if (dup2(cgi_stdin_fd[0], STDIN_FILENO) < 0) {
		//throw?
	}
	if (dup2(cgi_stdout_fd[1], STDOUT_FILENO) < 0) {
		//throw?
	}
	if (dup2(cgi_stdin_fd[1], client_fd_in) < 0) {
		//throw?
	}
	if (dup2(cgi_stdout_fd[0], client_fd_out) < 0) {
		//throw?
	}
	close(cgi_stdin_fd[1]);
	close (cgi_stdout_fd[0]);

	if (has_shebang(path)){
		std::string res = interpret_shebang(path);
		vec = split_shebang(res);
		args = build_args(vec, path);
	}
	/* else {
		//use extension or else..? Or bash?
	} */
	execve(vec[0].c_str(), &args[0], envp);
	//error msg execve failed PLACEHOLDER
	exit (1);
}

std::string fork_process(const std::string &path, int client_fd_in, \
		int client_fd_out,  char* const envp[]) {

	char buffer[4096];

	int cgi_stdin_fd[2];
	int cgi_stdout_fd[2];
	//link the child and the parent though pipes
	pipe(cgi_stdin_fd);
	pipe(cgi_stdout_fd);
	pid_t pid = fork();
	if (pid == 0) { //child
		run_cgi_script_in_child(cgi_stdin_fd, cgi_stdout_fd, path, envp);
	}
	else { //parent
		//close the child ends of the pipes
		close(cgi_stdin_fd[0]);
		close (cgi_stdout_fd[1]);
		ssize_t bytes_read = read(client.cgi_stdout_fd)
		//write http_req to server

	}
	close(cgi_stdout_fd[0]);
	return(output);
}

char** create_cgi_envp(HttpRequest& http_req) {
	//body itself is not part of the envp
	char** envp; //problem with freeing?
	//actually creating it PLACEHOLDER
	return (envp);
}

std::string handle_cgi(HttpRequest& http_req, T client_socket) {
	char** envp;
	envp = create_cgi_envp(http_req);
	//http_req.setEnvp(envp);
	return (fork_process(http_req.getPath(), client_socket-fdin, \
		 client_socket-fdout, envp));
}

std::string serve_static(HttpRequest& http_req);

void request_handler(HttpRequest& http_req, T client_socket) {
	std::string http_answer; //buffer
	//at this stage the HttpRequest should be received completely, not just chunks
	if (http_req.getRequiresCgi()) {
		handle_cgi(http_req, client_socket);
	}
	else {
		serve_static(http_req);
	}
	//send to server ??
	return (http_answer);
}
