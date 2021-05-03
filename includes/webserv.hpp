/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:50:57 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/02 20:45:01 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <algorithm>

enum methods { GET, HEAD, PUT, POST, DELETE };

#define MAX_URI_LEN 8000
#define MAX_HEADER_LEN 8000
#define BUFFER_SIZE_REQUEST 1

#define CLRF "\r\n"
#define CLRF_OCTET_SIZE 2

char asciiToLower(char in);

#endif