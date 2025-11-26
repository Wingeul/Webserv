#include "shebang_reader.hpp"

class Client {
	private:
		std::string	cgi_output_buffer_;
		int			cgi_stdout_fd_;

	public:
		void		readCgiOutput(void);
		std::string	getCgiOutput() const;

};
