/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgipass.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:55:28 by hherin            #+#    #+#             */
/*   Updated: 2021/05/31 16:21:44 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIPASS_HPP
# define CGIPASS_HPP

#include <string>

class Cgipass
{
	public:
		Cgipass(Request const &req, )

	private:
		std::string _auth_type;
		int _c_lenght;
		std::string _c_type;
		std::string _gateway_int;
		std::string _path_info;
		std::string _path_transl;
		std::string _query_string;
		long _remote_addr;					// The IP address of the visitor
		std::string _remote_ident;
		std::string _remote_usr;			// The visitor's username
		std::string _req_method;
		std::string _req_uri;				// The interpreted pathname of the requested document or CGI 
		std::string _script_name;			// The interpreted pathname of the current CGI (relative to the document root)
		int _srv_port;						// The port number your server is listening on
		std::string _protocol;
		std::string _software;				// The server software you're using
		std::string _srv_name;
};

#endif