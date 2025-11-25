#include "shebang_reader.hpp"


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
void run_cgi_script(const std::string &path, char* const envp[]) {
		//test if script can be opened before ?
		std::vector<std::string> vec;
		std::vector<char *> args;
		if (has_shebang(path)){
			std::string res = interpret_shebang(path);
			vec = split_shebang(res);
			args = build_args(vec, path);
		}
		/* else {
			//use extension or else..? Or bash?
		} */
		execve(vec[0].c_str(), &args[0], envp);
		//error msg execve failed
		exit (1);
}

void part_to_be_integrated(const std::string &path, int cgi_stdin_fd, int cgi_stdout_fd,  char* const envp[]) {

	pid_t pid = fork();
	if (pid == 0) { //child
		if (dup2(cgi_stdin_fd, STDIN_FILENO) < 0) {
			//throw
		}
		if (dup2(cgi_stdout_fd, STDOUT_FILENO) < 0) {
			//throw
		}
		close(cgi_stdin_fd);
		close (cgi_stdout_fd);

		run_cgi_script(path, envp);
	}
	else if (pid < 0) { //parent
		close(cgi_stdin_fd);
		close (cgi_stdout_fd);
	}
	else {
		//fork failed, error?
	}
}

char** create_cgi_envp(Request& http_req) {
	//body itself is not part of the envp
	char** envp; //problem with freeing?

	return (envp);
}

void parse_request(Request& http_req) {
	char** envp;
	envp = create_cgi_envp(http_req);
	http_req.setEnvp(envp);
}

std::string create_answer();

const std::string request_handler(Request& http_req) {
	std::string http_answer; //buffer
	parse_request(http_req); //at this stage the request should be complete, not just chunks

	http_answer = create_answer();
	return (http_answer);
}


//MAIN LOOP -> calling request_handler
