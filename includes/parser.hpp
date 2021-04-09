#ifndef PARSER_HPP
# define PARSER_HPP

# include <fstream>
# include <string>

class parser 
{
    public:
        parser(char*);

        ~parser();

        void getfile();

    private:
        std::string conf;
        std::ifstream file;
        std::string buf;
        

};

#endif