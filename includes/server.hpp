/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:42:16 by hherin            #+#    #+#             */
/*   Updated: 2021/04/12 18:18:01 by hherin           ###   ########.fr       */
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

		// std::vector<std::string> _method;
		// std::string _default;
		
	public:
		server() {};
		
		~server() {};
		
		void	setServer(int nb, int const &pos, std::string const &buf);

		int const &getPort() { return _port; }
		
		std::string const &getError() { return _error_path; }

		std::vector<std::string> const &getNames() { return _names; }
		
	private:
		void setPort(char const *p);

		void setName(char const *n);
		
		void setError(char const *e);

		void setRoot();
		
};

// server
//     allow_methods
//     listen
//     root
//     server_name
//     location
//     index
//     auth_basic
//     auth_basic_user_file
//     error_page
//     client_max_body_size
//     autoindex
//     upload_store

#endif