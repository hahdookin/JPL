#include <iostream>
#include <fstream>
#include "JPL.h"


int main()
{
    /*std::string file = "code.txt";

    std::string line;
    std::ifstream code(file);

    if (code.is_open())
    {
        while (std::getline(code, line))
        {
            std::vector<std::string> line_split = split_string(line, ' ');

            jess::Tokenized_Line tok_line; // { I 5 , O plus, I 8 }

            for (auto word : line_split)
            {
                jess::Token token(word);
                tok_line.append(token);
            }


            tok_line.interpret_line();
            
        }
        code.close();
    }*/

    std::vector<std::string> all_code =
    {
        "say \"Enter:\"",
        "get x",
        "say x plus 5"
    };
    for (auto code_line : all_code)
    {
        std::vector<std::string> code_line_split = split_string(code_line);
        jess::Tokenized_Line tok_line;
        for (auto word : code_line_split)
        {
            jess::Token token(word);
            tok_line.append(token);
        }
        tok_line.interpret_line();
    }

    return 0;
}