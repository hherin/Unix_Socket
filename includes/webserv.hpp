/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:50:57 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/26 18:58:31 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <algorithm>

enum methods { GET, HEAD, PUT, POST, DELETE };

#define MAX_URI_LEN 8000
#define MAX_HEADER_LEN 8000

char asciiToLower(char in);

#endif