#ifndef PARSER_HPP
# define PARSER_HPP

# include <fstream>
# include <string>
# include <map>
# include <cctype>  // function isspace
# include <iostream>
# include "ServerInfo.hpp"


class FileParser 
{
    public:
        FileParser(const char*);

        ~FileParser();

        void parseConfigFile();

        void parseOutputFile();
        
        std::string const& getOutputFile();

        std::map<int, std::vector<ServerInfo> > const &getConfig();

    private:
        std::ifstream _file;
        std::string _buf;
        int _bracket;
        std::map<int, std::vector<ServerInfo> > _m_srv;
        std::string _outputFile;

        void newServer(void);
        void newLocation(ServerInfo &);
        void addNewServerToMap(ServerInfo &);
};


#endif