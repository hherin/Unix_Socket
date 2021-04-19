/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserInfoHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:20:32 by hherin            #+#    #+#             */
/*   Updated: 2021/04/14 17:24:28 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERINFOHANDLER_HPP
# define PARSERINFOHANDLER_HPP

# include "FileParser.hpp"

class ParserInfoHandler
{
    public:
    
    private:
        FileParser _fparse;    
        std::map<int, std::vector<ServerInfo> > _m_srv;
};

#endif