/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInfo.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:42:16 by hherin            #+#    #+#             */
/*   Updated: 2021/05/20 15:47:51 by hherin           ###   ########.fr       */
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
		std::string	_cgi_exe;
		std::string	_cgi_path;
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
		
		int const &getMaxClientsBS() const;	

		bool const &getAutoIndex() const;

		std::string const &getError() const;

		std::string const &getRoot() const;

		std::string const &getAuthBasic() const;

		std::string const &getAuthBasicFile() const;

		std::string const &getUploadStore() const;

		std::string const &getCgiExe() const;

		std::string const &getCgiPath() const;
		
		std::vector<std::string> const &getNames() const;

		std::vector<std::string> const &getMethods() const;
		
		std::vector<std::string> const &getIndex() const;
		
		int const &getPort() const;

		std::vector<ServerInfo> const &getLocation() const;
		
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

		void setCgiExe(char const *);

		void setCgiPath(char const *);
		
		void setStringArray(char const *n, std::vector<std::string> &v);		
};


#endif