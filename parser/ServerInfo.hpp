/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInfo.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:42:16 by hherin            #+#    #+#             */
/*   Updated: 2021/04/28 14:28:28 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERINFO_HPP
# define SERVERINFO_HPP

# include <vector>
# include <string>
# include <cstring>
# include <algorithm>

class ServerInfo
{
	private:
		int _max_clients;						//
		bool _autoindex;						//
		std::string _error_path;				//
		std::string _root;						//
		std::string _auth_basic;				//
		std::string _auth_b_usr_file;			//
		std::string _upload_store;				//
		std::vector<std::string> _names;		//
		std::vector<std::string> _allow_methd;	//
		std::vector<std::string> _index;		//
		int _port;					//
		std::vector<ServerInfo> _location;		//
		

	public:
		ServerInfo();
		
		ServerInfo(ServerInfo const &);

		ServerInfo &operator=(ServerInfo const &);
		
		~ServerInfo();
		
		int const &getMaxClientsBS();	

		bool const &getAutoIndex();

		std::string const &getError();

		std::string const &getRoot();

		std::string const &getAuthBasic();

		std::string const &getAuthBasicFile();

		std::string const &getUploadStore();

		std::vector<std::string> const &getNames();

		std::vector<std::string> const &getMethods();
		
		std::vector<std::string> const &getIndex();
		
		int const &getPort();

		std::vector<ServerInfo> const &getLocation();
		
		void setServer(int, int const&, std::string const&);

		void setLocation(ServerInfo &);
		
	private:
		void setMaxClientsBS(char const*);

		void setAutoIndex(char const*);

		void setError(char const*);
		
		void setRoot(char const*);

		void setAuthBasic(char const*);

		void setAuthBasicFile(char const*);

		void setUploadStore(char const*);

		void setNames(char const*);

		void setMethods(char const*);

		void setIndex(char const*);
		
		void setPort(char const*);
		
		void setStringArray(char const *n, std::vector<std::string> &v);		
};


#endif