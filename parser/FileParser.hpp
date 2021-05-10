#ifndef FILEPARSER_HPP
# define FILEPARSER_HPP

# include "parser.hpp"

class FileParser 
{
    private:
        std::ifstream _file;
        std::string _buf;
        int _bracket;
        std::map<int, std::vector<ServerInfo> > _m_srv;
        std::string _requestFile;
        ServerInfo *_cli_srv;
        std::string _filePath;

    public:

        FileParser(const char*);

        // FileParser(const char*, ServerInfo *);

        FileParser(FileParser const&);

        FileParser &operator=(FileParser const&);

        ~FileParser();
        
        std::string const& getRequestFile();

        std::map<int, std::vector<ServerInfo> > const &getConfigFile();

    private:
        void parseConfigFile();

        void parseRequestFile();
        
        void newServer(void);
        
        void newLocation(ServerInfo &);
        
        void addNewServerToMap(ServerInfo &);
};

#endif