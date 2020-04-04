#include <iostream>
#include <fstream>
#include "JPL.h"


int main()
{
    DEBUG_MODE = true;

    /*std::string file = "code.jess"; 

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
        "say \"Enter a value for x:\"",
        "get x",
        "say \"Enter a value for y:\"",
        "get y",
        "say x",
        "say y"
    };
    for (auto code_line : all_code)
    {
        if (DEBUG_MODE) std::cout << "#Global variables: " << variables.size() << std::endl;

        std::vector<std::string> code_line_split = split_string(code_line);
        jess::Tokenized_Line tok_line;
        for (auto word : code_line_split)
        {
            jess::Token token(word);
            tok_line.append(token);
        }
        for (auto tok : tok_line.line)
        {
            tok.print();
        }
        std::cout << ">> ";
        tok_line.interpret_line();

        

        
        
        
    }
    
    return 0;
}