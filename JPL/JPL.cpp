#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include "JPL.h"



int main()
{
    //std::string file = "code.txt";

    //std::string line;
    //std::ifstream code(file);

    //if (code.is_open())
    //{
    //    while (std::getline(code, line))
    //    {
    //        std::vector<std::string> line_split = split_string(line, ' ');

    //        jess::Tokenized_Line tok_line; // { I 5 , O plus, I 8 }

    //        for (auto word : line_split)
    //        {
    //            jess::Token token(word);
    //            tok_line.append(token);
    //        }


    //        tok_line.interpret_line();
    //        
    //    }
    //    code.close();
    //}

    std::vector<std::string> all_code =
    {
        "say 10 times 2",
        "say 15 minus 3.2",
        "say 7.2 modulus 3",
        "say 18 dividedby 6",
        "say 5.25 plus .25"
    };

    for (auto line : all_code)
    {
        std::vector<std::string> code_split = split_string(line);
        jess::Tokenized_Line tok_line;
        for (auto term : code_split)
        {
            jess::Token token(term);
            tok_line.append(token);
        }
        tok_line.interpret_line();
    }

    /*std::string code = "say 9.4 times 4";
    std::vector<std::string> code_split = split_string(code);

    jess::Tokenized_Line tok_line;
    for (auto word : code_split)
    {
        jess::Token token(word);
        tok_line.append(token);
    }
    
    tok_line.interpret_line();*/

    return 0;
}