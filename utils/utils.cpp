/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:56:49 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/10 14:26:11 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

char asciiToLower(char in)
{
    if (in >= 'A' && in <= 'Z')
        return in + ('a' - 'A');
    return in;
}

std::string convertNbToString(size_t nb)
{
	std::ostringstream oss;
	
	oss << nb;
	return oss.str();
}