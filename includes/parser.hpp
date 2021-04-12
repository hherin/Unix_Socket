#ifndef PARSER_HPP
# define PARSER_HPP

# include <fstream>
# include <string>
# include <map>
# include "server.hpp"

# include <cctype>  // function isspace
# include <iostream>

class parser 
{
    public:
        parser(char*);

        ~parser();

        void getfile();

        std::vector<server> const &getServer() { return _srv; }

    private:
        std::string _conf;
        std::ifstream _file;
        std::string _buf;
        // server srv;
        std::vector<server> _srv;
        int _in, _out;
        void newServer(void);

        // std::map<>
        

};


#endif