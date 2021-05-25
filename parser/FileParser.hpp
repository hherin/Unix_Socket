/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:02:25 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/25 16:02:28 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEPARSER_HPP
# define FILEPARSER_HPP

# include "parser.hpp"

enum e_srv { LIS, ERR, SRV_N, BODY, HOST};

enum e_loc { METHO, IDX, AUTHB, AUTHB_FILE, AUTOIDX, STORE, ROOT, CGI_EXE, CGI_PATH};


class FileParser 
{
	private:
		std::ifstream _file;
		std::string _buf;
		int _bracket;
		std::map<int, std::vector<ServerInfo> > _m_srv;
		std::map<std::string, Location> _m_loc;
		std::string _requestFile;
		ServerInfo *_cli_srv;
		std::string _filePath;

	public:

		FileParser(const char*);

		FileParser(const char*, ServerInfo *);

		FileParser(FileParser const&);

		FileParser &operator=(FileParser const&);

		~FileParser();
		
		std::string const& getRequestFile();

		std::map<int, std::vector<ServerInfo> > const &getConfigFile();

		void setServerInfo(ServerInfo *);

		size_t getRequestFileSize() const;

    private:
        void parseConfigFile();

		void parseRequestFile();
		
		void newServer(void);
		
		void newLocation(ServerInfo &);
		
		void addNewServerToMap(ServerInfo &);

		void addNewLocationToMap(Location*, std::string const&);
};

#endif