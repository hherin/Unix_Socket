/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:50:57 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/27 17:30:35 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <algorithm>

enum methods { GET, HEAD, PUT, POST, DELETE };

#define MAX_URI_LEN 8000
#define MAX_HEADER_LEN 8000
#define BUFFER_SIZE_REQUEST 5000

char asciiToLower(char in);

#endif