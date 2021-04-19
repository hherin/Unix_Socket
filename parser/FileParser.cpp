/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:06:51 by hherin            #+#    #+#             */
/*   Updated: 2021/04/14 17:18:44 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/FileParser.hpp"

FileParser::FileParser(char *filepath) : _conf(filepath), _in(0), _out(0) { _file.open(_conf.c_str()); }

FileParser::~FileParser() { _file.close(); }

int	bracketRegulator(int &in, int &out, std::string const &buf)
{
	size_t pos = -1; 
	while ( (pos = buf.find_first_of('{', pos + 1)) != std::string::npos) 
		in++;
	
	pos = -1;
	while ( (pos = buf.find_first_of('}', pos + 1)) != std::string::npos)
		out++;
	return 1;
}

void FileParser::getfile()
{
	while (std::getline(_file, _buf)){
		if (_buf.find_first_of("server") != std::string::npos){
			_in = 0; _out = 0;
			bracketRegulator(_in, _out, _buf);
			newServer();
		}
		else continue; // ERRUR 
	}
}

int	cleanLineFromSpaces(std::string &buf)
{
	int i = 0;
	while (isspace(buf[i]))
		buf.erase(0, 1);
	
	// std::cout << buf.size() << "\n"; // trim spaces at the end 
	// std::cout << buf << "\n\n\n";
	// i = buf.size() - 1;
	// while (isspace(buf[i]))
	// 	buf.erase(i, 1);
	return 0;
}

void FileParser::newLocation(ServerInfo &srv)
{
	ServerInfo n_loc;
	int inL = 0, outL = 0;
	
	bracketRegulator(inL, outL, _buf);
	if (!_buf.compare(0, 8, "location")){
		(!_buf.compare(_buf.size() - 1, 1, "{")) ? _buf.erase(_buf.size() - 1, 1) : 0;
		n_loc.setServer(2, 8, _buf);
	}
	while (inL != outL)
	{
		// std::cout << "LINELOC " << _buf << "\n";
		std::getline(_file, _buf);
		(_buf.size()) ? cleanLineFromSpaces(_buf) : 0;
		bracketRegulator(inL, outL, _buf);
		
		if (!_buf.compare(0, 6, "listen"))
			n_loc.setServer(0, 6, _buf);
		else if (!_buf.compare(0, 5, "error"))
			n_loc.setServer(1, 5, _buf);
		else if (!_buf.compare(0, 11, "server_name"))
			n_loc.setServer(2, 11, _buf);
		else if (!_buf.compare(0, 12, "allow_method"))
			n_loc.setServer(3, 12, _buf);
		else if (!_buf.compare(0, 5, "index"))
			n_loc.setServer(4, 5, _buf);
		else if (!_buf.compare(0, 10, "auth_basic"))
			n_loc.setServer(5, 10, _buf);
		else if (!_buf.compare(0, 15, "auth_b_usr_file"))
			n_loc.setServer(6, 15, _buf);
		else if (!_buf.compare(0, 20, "client_max_body_size"))
			n_loc.setServer(7, 20, _buf);
		else if (!_buf.compare(0, 9, "autoindex"))
			n_loc.setServer(8, 9, _buf);
		else if (!_buf.compare(0, 12, "upload_store"))
			n_loc.setServer(9, 12, _buf);
		else if (!_buf.compare(0, 4, "root"))
			n_loc.setServer(10, 4, _buf);
		else continue;
	}
	_out++;
	srv.setLocation(n_loc);
}



void FileParser::newServer(void)
{
	ServerInfo n_srv;

	while (_in != _out)
	{
		std::getline(_file, _buf);
		(_buf.size()) ? cleanLineFromSpaces(_buf) : 0;
		bracketRegulator(_in, _out, _buf);

		if (!_buf.compare(0, 8, "location"))	
			newLocation(n_srv);
		else if (!_buf.compare(0, 6, "listen"))
			n_srv.setServer(0, 6, _buf);
		else if (!_buf.compare(0, 5, "error"))
			n_srv.setServer(1, 5, _buf);
		else if (!_buf.compare(0, 11, "server_name"))
			n_srv.setServer(2, 11, _buf);
		else if (!_buf.compare(0, 12, "allow_method"))
			n_srv.setServer(3, 12, _buf);
		else if (!_buf.compare(0, 5, "index"))
			n_srv.setServer(4, 5, _buf);
		else if (!_buf.compare(0, 10, "auth_basic"))
			n_srv.setServer(5, 10, _buf);
		else if (!_buf.compare(0, 15, "auth_b_usr_file"))
			n_srv.setServer(6, 15, _buf);
		else if (!_buf.compare(0, 20, "client_max_body_size"))
			n_srv.setServer(7, 20, _buf);
		else if (!_buf.compare(0, 9, "autoindex"))
			n_srv.setServer(8, 9, _buf);
		else if (!_buf.compare(0, 12, "upload_store"))
			n_srv.setServer(9, 12, _buf);
		else if (!_buf.compare(0, 4, "root"))
			n_srv.setServer(10, 4, _buf);
		else continue;		// BIG ERROR TO DO
	}
	// _srv.push_back(n_srv);
	addNewServerToMap(n_srv);
}

void FileParser::addNewServerToMap(ServerInfo &srv)
{
	std::vector<int> s_port = srv.getPort();

	for (size_t i = 0; i < s_port.size(); i++){
		std::map<int, std::vector<ServerInfo> >::iterator it = _m_srv.find(s_port[i]);
		
		if (it == _m_srv.end()){
			std::vector<ServerInfo> v_srv(1, srv);
			_m_srv.insert(std::pair<int, std::vector<ServerInfo> >(s_port[i], v_srv));
		}
		else
			it->second.push_back(srv);
	}
}