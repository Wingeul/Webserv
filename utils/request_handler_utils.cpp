/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_handler_utils.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitz <jschmitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:55:42 by jschmitz          #+#    #+#             */
/*   Updated: 2025/11/28 19:43:52 by jschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/client_request.hpp"

bool isPythonScript(Client_request request) {
	if (request.getPath().find(".py") != std::string::npos) {
		return (true);
	}
	return (false);
}

bool isPhpScript(Client_request request) {
	if (request.getPath().find(".php") != std::string::npos) {
		return (true);
	}
	return (false);
}

//to avoid memory leaks in child
void freeCharArray(char** array) {
    if (!array) return;

    for (size_t i = 0; array[i] != NULL; ++i) {
        delete[] array[i];
    }
    delete[] array;
}
