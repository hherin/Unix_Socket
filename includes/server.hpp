/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:42:16 by hherin            #+#    #+#             */
/*   Updated: 2021/04/12 18:31:35 by hherin           ###   ########.fr       */
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
		int _port;
		std::vector<std::string> _names;
		std::string _error_path;
		std::vector<server> _root_path;
		std::vector<std::string> _allow_methd;
		std::vector<std::string> _index;
		std::string _auth_basic;
		std::string _auth_b_usr_file;
		int _max_clients;
		bool _autoindex;
		std::string _upload_store;
		

	public:
		server();
		
		~server();
		
		void setServer(int nb, int const &pos, std::string const &buf);

		int const &getPort();
		
		std::string const &getError();

		std::vector<std::string> const &getNames();
		
	private:
		void setPort(char const *p);

		void setName(char const *n);
		
		void setError(char const *e);

		void setRoot();
		
};


#endif