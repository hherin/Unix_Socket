/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:04:02 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/22 15:34:00 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

ClientSocket::ClientSocket(int fd) :
		_fd(fd) {}

ClientSocket::~ClientSocket() {}

ClientSocket::ClientSocket(const ClientSocket& copy) :
		_fd(copy._fd) {}

ClientSocket& ClientSocket::operator=(ClientSocket assign)
{
	swap(assign, *this);
	return *this;
}

int ClientSocket::getFd() const { return _fd; }

//private

void swap(ClientSocket& a, ClientSocket& b)
{
	std::swap(a._fd, b._fd);
}