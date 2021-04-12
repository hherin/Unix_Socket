/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:06:51 by hherin            #+#    #+#             */
/*   Updated: 2021/04/12 18:14:11 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/parser.hpp"

parser::parser(char *filepath) : _conf(filepath), _in(0), _out(0) { _file.open(_conf.c_str()); }

parser::~parser() { _file.close(); }

int	blockRegulator(int &in, int &out, std::string const &buf)
{
	size_t pos = -1;
	while ( (pos = buf.find_first_of('{', pos + 1)) != std::string::npos) 
		in++;
	
	pos = -1;
	while ( (pos = buf.find_first_of('}', pos + 1)) != std::string::npos)
		out++;
	return 1;
}

void parser::getfile()
{
	while (std::getline(_file, _buf))
	{
		if (_buf.find_first_of("server") != std::string::npos){
			_in = 0; _out = 0;
			blockRegulator(_in, _out, _buf);
			newServer();
		}
	}
}

void parser::newServer(void)
{
	server n_srv;
	while (_in != _out)
	{
		std::getline(_file, _buf);
		blockRegulator(_in, _out, _buf);
		size_t pos;
		
		if ( (pos = _buf.find("listen")) != std::string::npos)
			n_srv.setServer(0, pos, _buf.c_str() + pos + 6);
		else if ( (pos = _buf.find("error")) != std::string::npos)
			n_srv.setServer(1, pos, _buf.c_str() + pos + 5);
		else if ( (pos = _buf.find("server_name")) != std::string::npos)
			n_srv.setServer(2, pos, _buf.c_str() + pos + 11);
	}
	_srv.push_back(n_srv);
}