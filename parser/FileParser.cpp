/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:06:51 by hherin            #+#    #+#             */
/*   Updated: 2021/05/25 16:02:04 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileParser.hpp"

FileParser::FileParser(const char *filepath) : _bracket(0), _cli_srv(0), _filePath(filepath) { _file.open(filepath); }

FileParser::FileParser(const char *filepath, ServerInfo *cli_srv) : _bracket(0), _cli_srv(cli_srv), _filePath(filepath) { _file.open(filepath); }

FileParser::FileParser(FileParser const&copy) :  _buf(copy._buf), _bracket(copy._bracket), 
_m_srv(copy._m_srv), _requestFile(copy._requestFile), _cli_srv(copy._cli_srv), _filePath(copy._filePath)
{
	_file.open(_filePath);
}

FileParser &FileParser::operator=(FileParser const&copy)
{
	FileParser tmp(copy);

	std::swap(tmp, *this);
	return *this;
}

FileParser::~FileParser() { _file.close(); }

void FileParser::parseRequestFile()
{
	if (!_cli_srv){
		std::cerr << "NOT ALLOWED\n";
		exit(1);
	}
	while (std::getline(_file, _buf))
		_requestFile.append(_buf + "\n");
}

std::string const& FileParser::getRequestFile() { parseRequestFile(); return _requestFile; }

void FileParser::parseConfigFile()
{
	if (_cli_srv){
		std::cerr << "NOT ALLOWED\n";
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

size_t FileParser::getRequestFileSize() const { return _requestFile.size(); }

// check bracket la ou il faut pas
void FileParser::newLocation(ServerInfo &srv)
{
	Location n_loc(&srv);
	std::string uri;
	int brack = 0;
	
	bracketRegulator(brack, _buf);
	if (!_buf.compare(0, 8, "location")){
		(!_buf.compare(_buf.size() - 1, 1, "{")) ? _buf.erase(_buf.size() - 1, 1) : 0;
		uri = *wsTrim(_buf);
		uri.replace(0, 8, "");
		std::cout << "uri ." << uri << ".\n";
	}
	while (brack > 0)
	{
		std::getline(_file, _buf);
		cleanLineFromSpaces(_buf);
		bracketRegulator(brack, _buf);

		if (!_buf.compare(0, 12, "allow_method"))
			n_loc.setLocation(METHO, 12, _buf);
		else if (!_buf.compare(0, 5, "index"))
			n_loc.setLocation(IDX, 5, _buf);
		else if (!_buf.compare(0, 10, "auth_basic"))
			n_loc.setLocation(AUTHB, 10, _buf);
		else if (!_buf.compare(0, 15, "auth_b_usr_file"))
			n_loc.setLocation(AUTHB_FILE, 15, _buf);
		else if (!_buf.compare(0, 9, "autoindex"))
			n_loc.setLocation(AUTOIDX, 9, _buf);
		else if (!_buf.compare(0, 12, "upload_store"))
			n_loc.setLocation(STORE, 12, _buf);
		else if (!_buf.compare(0, 4, "root"))
			n_loc.setLocation(ROOT, 4, _buf);
		else if (!_buf.compare(0, 3, "cgi"))
			n_loc.setLocation(CGI_EXE, 3, _buf);
		else if (!_buf.compare(0, 8, "cgi_path"))
			n_loc.setLocation(CGI_PATH, 8, _buf);
		else continue;
	}
	_bracket--;
	addNewLocationToMap(&n_loc, uri);
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
			n_srv.setServer(LIS, 6, _buf);
		else if (!_buf.compare(0, 5, "error"))
			n_srv.setServer(ERR, 5, _buf);
		else if (!_buf.compare(0, 11, "server_name"))
			n_srv.setServer(SRV_N, 11, _buf);
		else if (!_buf.compare(0, 20, "client_max_body_size"))
			n_srv.setServer(BODY, 20, _buf);
		else if (!_buf.compare(0, 4, "host"))
			n_srv.setServer(HOST, 4, _buf);
		else continue;		// BIG ERROR TO DO
	}
	addNewServerToMap(n_srv);
}

void FileParser::addNewServerToMap(ServerInfo &srv)
{
	int s_port = srv.getPort();
	srv.getLocation()->insert(_m_loc.begin(), _m_loc.end());
	std::map<int, std::vector<ServerInfo> >::iterator it = _m_srv.find(s_port);
		
	if (it == _m_srv.end()){
		std::vector<ServerInfo> v_srv(1, srv);
		_m_srv.insert(std::pair<int, std::vector<ServerInfo> >(s_port, v_srv));
	}
	else
		it->second.push_back(srv);
	_m_loc.clear();
}

void FileParser::addNewLocationToMap(Location *loc, std::string const &name)
{
	std::map<std::string, Location>::iterator it = _m_loc.find(name);
	
	if (it == _m_loc.end())
		_m_loc.insert(std::pair<std::string, Location>(name, *loc));
	else
		throw "Error location already exist\n";
}

std::map<int, std::vector<ServerInfo> > const &FileParser::getConfigFile() { parseConfigFile(); return _m_srv; }

void FileParser::setServerInfo(ServerInfo *s) { _cli_srv = s; }