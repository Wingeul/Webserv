#include "temp_client.hpp"

void	Client::readCgiOutput(void) {
	char buf[4096];
	ssize_t bytes_read = read(cgi_stdout_fd_, buf, 4096);
	if (bytes_read > 0) {
		cgi_output_buffer_.append(buf, bytes_read);
	}
	else if (bytes_read == 0) {
		//EOF
	}
}

std::string	Client::getCgiOutput() const {
	return(this->cgi_output_buffer_);
}
