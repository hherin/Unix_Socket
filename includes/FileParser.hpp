#ifndef PARSER_HPP
# define PARSER_HPP

# include <fstream>
# include <string>
# include <map>
# include "ServerInfo.hpp"

# include <cctype>  // function isspace
# include <iostream>

class FileParser 
{
    public:
        FileParser(char*);

        ~FileParser();

        void getfile();

        std::vector<ServerInfo> const &getServer() { return _srv; }
        std::map<int, std::vector<ServerInfo> > const &getMapServer() { return _m_srv; }

    private:
        std::string _conf;
        std::ifstream _file;
        std::string _buf;
        std::vector<ServerInfo> _srv;
        int _in, _out;
        void newServer(void);
        void newLocation(ServerInfo &);
        void addNewServerToMap(ServerInfo &);
        std::map<int, std::vector<ServerInfo> > _m_srv;
        

};


#endif