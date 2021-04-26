/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:04:02 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/23 18:15:40 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

ClientSocket::ClientSocket(int fd) :
		_fd(fd), _request(), _response() {}

ClientSocket::~ClientSocket() {}

ClientSocket::ClientSocket(const ClientSocket& copy) :
		_fd(copy._fd) {}

ClientSocket& ClientSocket::operator=(ClientSocket assign)
{
	swap(assign, *this);
	return *this;
}

// Getters

int ClientSocket::getFd() const { return _fd; }

const Request& ClientSocket::getRequest() const { return _request; }

const std::string& ClientSocket::getResponse() const { return _response; }

// Methods

int ClientSocket::receiveRequest(const char* buffer)
{
	_request += buffer;
	_request.parsingCheck();

	return 0;
}

//private

void swap(ClientSocket& a, ClientSocket& b)
{
	std::swap(a._fd, b._fd);
}
