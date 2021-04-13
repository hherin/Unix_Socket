/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:06:51 by hherin            #+#    #+#             */
/*   Updated: 2021/04/13 16:43:12 by heleneherin      ###   ########.fr       */
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
	while (std::getline(_file, _buf)){
		if (_buf.find_first_of("server") != std::string::npos){
			_in = 0; _out = 0;
			blockRegulator(_in, _out, _buf);
			newServer();
		}
	}
}

void parser::newLocation(server &srv)
{
	server n_l;
	size_t pos;
	int inL = 0, outL = 0;
	
	blockRegulator(inL, outL, _buf);
	if ( (pos = _buf.find("location")) != std::string::npos)
			n_l.setServer(2, pos, _buf.c_str() + pos + 4);
	while (inL != outL)
	{
		// std::cout << "LINELOC " << _buf << "\n";
		std::getline(_file, _buf);
		blockRegulator(inL, outL, _buf);
		
		if ( (pos = _buf.find("error")) != std::string::npos)
			n_l.setServer(1, pos, _buf.c_str() + pos + 5);
		else if ( (pos = _buf.find("allow_method")) != std::string::npos)
			n_l.setServer(3, pos, _buf.c_str() + pos + 11);
		else if ( (pos = _buf.find("index")) != std::string::npos)
			n_l.setServer(4, pos, _buf.c_str() + pos + 4);
		else if ( (pos = _buf.find("auth_basic")) != std::string::npos)
			n_l.setServer(5, pos, _buf.c_str() + pos + 10);
		else if ( (pos = _buf.find("auth_b_usr_file")) != std::string::npos)
			n_l.setServer(6, pos, _buf.c_str() + pos + 15);
		else if ( (pos = _buf.find("client_max_body_size")) != std::string::npos)
			n_l.setServer(7, pos, _buf.c_str() + pos + 20);
		else if ( (pos = _buf.find("autoindex")) != std::string::npos)
			n_l.setServer(8, pos, _buf.c_str() + pos + 9);
		else if ( (pos = _buf.find("upload_store")) != std::string::npos)
			n_l.setServer(9, pos, _buf.c_str() + pos + 12);
		else continue;
	}
	_out++;
	srv.setLocation(n_l);
}

void parser::newServer(void)
{
	server n_srv;

	while (_in != _out)
	{
		// std::cout << "LINESRV " << _buf << std::endl;
		// std::cout << "IN " << _in << " OUT " << _out << std::endl;
		std::getline(_file, _buf);
		blockRegulator(_in, _out, _buf);
		size_t pos;
		
		if ( (pos = _buf.find("listen")) != std::string::npos)
			n_srv.setServer(0, pos, _buf.c_str() + pos + 6);
		else if ( (pos = _buf.find("error")) != std::string::npos)
			n_srv.setServer(1, pos, _buf.c_str() + pos + 5);
		else if ( (pos = _buf.find("server_name")) != std::string::npos)
			n_srv.setServer(2, pos, _buf.c_str() + pos + 11);
		else if ( (pos = _buf.find("allow_method")) != std::string::npos)
			n_srv.setServer(3, pos, _buf.c_str() + pos + 12);
		else if ( (pos = _buf.find("index")) != std::string::npos)
			n_srv.setServer(4, pos, _buf.c_str() + pos + 5);
		else if ( (pos = _buf.find("auth_basic")) != std::string::npos)
			n_srv.setServer(5, pos, _buf.c_str() + pos + 10);
		else if ( (pos = _buf.find("auth_b_usr_file")) != std::string::npos)
			n_srv.setServer(6, pos, _buf.c_str() + pos + 15);
		else if ( (pos = _buf.find("client_max_body_size")) != std::string::npos)
			n_srv.setServer(7, pos, _buf.c_str() + pos + 20);
		else if ( (pos = _buf.find("autoindex")) != std::string::npos)
			n_srv.setServer(8, pos, _buf.c_str() + pos + 9);
		else if ( (pos = _buf.find("upload_store")) != std::string::npos)
			n_srv.setServer(9, pos, _buf.c_str() + pos + 12);
		else if ( (pos = _buf.find("location")) != std::string::npos)
			newLocation(n_srv);
		else continue;		// BIG ERROR TO DO
	}
	_srv.push_back(n_srv);
}