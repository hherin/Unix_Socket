/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationObj.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:08:11 by hherin            #+#    #+#             */
/*   Updated: 2021/06/11 15:51:54 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONOBJ_HPP
# define LOCATIONOBJ_HPP

# include <string>
# include <vector>
# include "ServerInfo.hpp"
# include "../utils/utils.hpp"
# include "parser.hpp"

class ServerInfo;

// ADD GETTERS FRON SRV

class Location
{
	private:
		/*	===========================================
			================= Variables ===============
		*/
		ServerInfo *_srv;
		std::string _root;
		std::string _upload_store;
		std::vector<std::string> _allow_methd;
		std::vector<std::string> _index;
		std::vector<std::string> _cgi_exe;
		
	public:
		/*	===========================================
			=============== Coplien Form ==============
		*/
		
		Location(ServerInfo*);
		Location(Location const &);
		Location &operator=(Location const &);
		~Location();

		/*	===========================================
			================= GETTERS =================
		*/
		std::string const &getRoot() const;
		std::string const &getUploadStore() const;
		std::vector<std::string> const &getCgiExe() const;
		std::vector<std::string> const &getMethods() const;
		std::vector<std::string> const &getIndex() const;
		
		/*	===========================================
			================= SETTERS =================
		*/
		void	setLocation(int nb, int const &pos, std::string const &buf);
	
		/*	===========================================
			================= METHODS =================
		*/

		void	printLocation(const std::string& locName) const;


	private:	
		void setRoot(char const*);
		void setUploadStore(char const*);
		void setMethods(char const*);
		void setIndex(char const*);
		void setCgiExe(char const *);
		
		/*	===========================================
			============ Private methods ==============
		*/
		template <class T>
		void myswap(T t1, T t2);
};


#endif