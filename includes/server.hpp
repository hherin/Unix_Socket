/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:42:16 by hherin            #+#    #+#             */
/*   Updated: 2021/04/13 16:45:43 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <string>
# include <cstring>

class server
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
		std::vector<int> _port;					//
		std::vector<server> _location;			//
		

	public:
		server();
		
		~server();
		
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
		
		std::vector<int> const &getPort();

		std::vector<server> const &getLocation();
		
		void setServer(int, int const&, std::string const&);

		void setLocation(server &);
		
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