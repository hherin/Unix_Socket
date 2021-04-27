#ifndef FILEPARSER_HPP
# define FILEPARSER_HPP

# include "parser.hpp"

class FileParser 
{
    public:
        FileParser(const char*);

        FileParser(const char*, ServerInfo *);

        ~FileParser();

        void parseConfigFile();

        void parseRequestFile();
        
        std::string const& getRequestFile();

        std::map<int, std::vector<ServerInfo> > const &getConfigFile();

    private:
        std::ifstream _file;
        std::string _buf;
        int _bracket;
        std::map<int, std::vector<ServerInfo> > _m_srv;
        std::string _requestFile;
        ServerInfo *cli_srv;

        void newServer(void);
        void newLocation(ServerInfo &);
        void addNewServerToMap(ServerInfo &);
};

#endif