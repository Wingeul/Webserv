/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shebang_reader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:26:54 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/25 18:08:33 by jschmitz         ###   ########.fr       */
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

class Request {
	private:
		char** envptr; //to avoid free in child process ?

	public:
		char** getEnvp();
		void setEnvp(char** envp);
};

#endif
