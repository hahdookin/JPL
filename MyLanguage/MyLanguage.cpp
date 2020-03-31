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
    //            token.set_type();
    //            tok_line.append(token);

    //            /*std::cout << token.sValue << " : " << token.type << " : ";
    //            if (token.type == 'I') std::cout << token.nValue;
    //            if (token.type == 'B') std::cout << token.bValue;
    //            std::cout << std::endl;*/
    //        }

    //        for (int i = 0; i < tok_line.line.size(); ++i)
    //        {
    //            if (tok_line.line[i].type == 'O')
    //            {
    //                // Int to float conversion
    //                if (tok_line.line[i - 1].type == 'F' || tok_line.line[i + 1].type == 'F') {
    //                    float res = perform_operation(tok_line.line[i - 1].fValue, tok_line.line[i + 1].fValue, tok_line.line[i].sValue);
    //                    std::cout << res << std::endl;
    //                }
    //                else {
    //                    int res = perform_operation(tok_line.line[i - 1].fValue, tok_line.line[i + 1].fValue, tok_line.line[i].sValue);
    //                    std::cout << res << std::endl;
    //                }
    //                
    //            }
    //        }
    //        
    //    }
    //    code.close();
    //}

    std::string code = "say 5.2 plus 2";
    std::vector<std::string> code_split = split_string(code);

    jess::Tokenized_Line tok_line;
    for (auto word : code_split)
    {
        jess::Token token(word);
        tok_line.append(token);
    }
    for (auto token : tok_line.line)
    {
        token.print();
    }
    
    return 0;
}
