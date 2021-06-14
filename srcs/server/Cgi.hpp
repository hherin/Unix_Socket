/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:50:03 by hherin            #+#    #+#             */
/*   Updated: 2021/06/14 17:47:07 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

#include "msg_format/Body.hpp"
#include "msg_format/StatusLine.hpp"
#include "Request.hpp"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include <sstream>

class CGI
{
	private:
		char **_envvar;
		char **_args;
		Body *_emptyBody;
		Request *_req;
		std::ifstream _openArgfile;
		std::string _exec_extension;
		std::string _realUri;
		std::pair<std::string, std::string> _path_info;
		
		
	public:
	/* ===================================================================
	 ======================= COPLIEN FORM ==============================*/
		CGI(Body *, Request *, const std::string &, const std::string& exec = "");
		CGI(CGI const &);
		CGI &operator=(CGI &);
		~CGI();
	
	
	/* ===================================================================
	 ======================= PUBLIC METHODS ============================*/
		void executeCGI();
		
	private:
	
	/* ===================================================================
	 ======================= PRIVATE METHODS ============================*/
	void mySwap(CGI &, CGI &);

};

#endif