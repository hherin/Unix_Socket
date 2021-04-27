/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:06:51 by hherin            #+#    #+#             */
/*   Updated: 2021/04/27 17:34:40 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileParser.hpp"

FileParser::FileParser(const char *filepath) : _bracket(0), _cli_srv(0), _filePath(filepath) { _file.open(filepath); }

FileParser::FileParser(const char *filepath, ServerInfo *cli_srv) : _bracket(0), _cli_srv(cli_srv), _filePath(filepath) { _file.open(filepath); }

FileParser::~FileParser() { _file.close(); }

void FileParser::parseRequestFile()
{
	if (!_cli_srv){
		std::cerr << "Wrong construteur\n";
		exit(1);
	}
	std::vector<ServerInfo> loc = _cli_srv->getLocation();
	for (size_t i = 0; i < loc.size(); i++){
		std::vector<std::string > locName = loc[i].getNames();
		for (size_t j = 0; j < locName.size(); j++){
			if (locName[j] == _filePath){
				
			}
		}
	}
	while (std::getline(_file, _buf))
		_requestFile.append(_buf + "\n");
}

std::string const& FileParser::getRequestFile() { parseRequestFile(); return _requestFile; }

void FileParser::parseConfigFile()
{
	if (_cli_srv){
		std::cerr << "Wrong construteur\n";
		exit(1);
	}
	while (std::getline(_file, _buf)){
		if (_buf.find_first_of("server") != std::string::npos){
			_bracket = 0;
			bracketRegulator(_bracket, _buf);
			newServer();
		}
		else continue; // ERREUR 
	}
}

// check bracket la ou il faut pas
void FileParser::newLocation(ServerInfo &srv)
{
	ServerInfo n_loc;
	int brack = 0;
	
	bracketRegulator(brack, _buf);
	if (!_buf.compare(0, 8, "location")){
		(!_buf.compare(_buf.size() - 1, 1, "{")) ? _buf.erase(_buf.size() - 1, 1) : 0;
		n_loc.setServer(2, 8, _buf);
	}
	while (brack > 0)
	{
		std::getline(_file, _buf);
		cleanLineFromSpaces(_buf);
		bracketRegulator(brack, _buf);
		
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
	_bracket--;
	srv.setLocation(n_loc);
}

void FileParser::newServer(void)
{
	ServerInfo n_srv;
	while (_bracket > 0)
	{
		std::getline(_file, _buf);
		cleanLineFromSpaces(_buf);
		bracketRegulator(_bracket, _buf);

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
	addNewServerToMap(n_srv);
}

void FileParser::addNewServerToMap(ServerInfo &srv)
{
	int s_port = srv.getPort();

	std::map<int, std::vector<ServerInfo> >::iterator it = _m_srv.find(s_port);
		
	if (it == _m_srv.end()){
		std::vector<ServerInfo> v_srv(1, srv);
		_m_srv.insert(std::pair<int, std::vector<ServerInfo> >(s_port, v_srv));
	}
	else
		it->second.push_back(srv);
	
}

std::map<int, std::vector<ServerInfo> > const &FileParser::getConfigFile() { parseConfigFile(); return _m_srv; }