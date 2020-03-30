#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>

/**********************************
 * Jess Programming Language (JPL)
 * Juevenile Esoteric Scripting System (JESS)
 * Types:
 * Int  I
 * Float F
 * Char C
 * Bool B
 * String S
 * Operator:
 *  +      -      *         /         %
 * plus, minus, times, divided by, modulus
 *
 */

// 8 plus 4
// { "8", "plus", "4" }

std::vector<std::string> split_string(std::string line, char delimiter);
bool bIsInteger(std::string s);
bool bIsFloat(std::string s);
bool bIsStringLiteral(std::string s);
bool bIsOperator(std::string s);
bool bIsBool(std::string s);
int perform_operation(int a, int b, std::string op);
float perform_operation(float a, float b, std::string op);


const std::string operator_terms[] = {
    "plus", "minus", "times", "dividedby", "modulus",
    "say"
};

const std::unordered_map<std::string, std::string> operators =
{
    {"plus", "+"},
    {"minus", "-"},
    {"times", "*"},
    {"divideby", "/"},
    {"modulus", "%"},
    {"say", "cout"}
};

namespace jess
{
    class Token
    {
    public:
        unsigned char type;
        std::string sValue;

        int nValue;
        float fValue;
        bool bValue;

    public:
        Token()
        {

        }

        Token(std::string value)
        {
            this->sValue = value;
            this->set_type();
        }

        // Prints token detail
        void print()
        {
            if (this->type == 'I') std::cout << this->sValue << " | " << this->type << " | " << this->nValue << std::endl;
            if (this->type == 'F') std::cout << this->sValue << " | " << this->type << " | " << this->fValue << std::endl;
            if (this->type == 'B') std::cout << this->sValue << " | " << this->type << " | " << this->bValue << std::endl;
            if (this->type == 'O') std::cout << this->sValue << " | " << this->type << " | " << std::endl;
        }

        // Determines the type of the token i.e. Int, Bool, Char
        void set_type()
        {
            if (bIsOperator(this->sValue)) this->type = 'O';

            else if (bIsInteger(this->sValue))
            {
                this->type = 'I';
                this->nValue = std::stoi(this->sValue);
                this->fValue = std::stof(this->sValue);
            }

            else if (bIsFloat(this->sValue))
            {
                this->type = 'F';
                this->fValue = std::stof(this->sValue);
                this->nValue = std::stoi(this->sValue);
            }

            else if (bIsStringLiteral(this->sValue)) this->type = 'S';

            else if (bIsBool(this->sValue))
            {
                this->type = 'B';
                this->bValue = this->sValue == "true";
            }
        }

        Token operator + (Token &obj) {
            Token res;
            if (this->type == 'F' || obj.type == 'F')
            {
                res.type = 'F';
                res.fValue = this->fValue + obj.fValue;
            }
            else {
                res.type = this->type;
                res.nValue = this->nValue + obj.nValue;
            }
            
            return res;
        }
    };
    
    class Tokenized_Line
    {
    public:
        std::vector<Token> line = {};
    public:
        Tokenized_Line()
        {

        }
        void append(Token token)
        {
            this->line.push_back(token);
        }
    };
}

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

    jess::Tokenized_Line line;
    jess::Token one("5.12");
    jess::Token two("true");
    jess::Token three("123");
    jess::Token four("minus");

    line.append(one);
    line.append(two);
    line.append(three);
    
    jess::Token a("5.25");
    jess::Token b("3.25");

    jess::Token res = a + b;

    res.print();

    return 0;
}

// Splits a string by a delimiter char
std::vector<std::string> split_string(std::string line, char delimiter)
{
    std::vector<std::string> split = {};

    std::string currentWord = "";
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == delimiter)
        {
            split.push_back(currentWord);
            currentWord = "";
        }
        else if (i == line.size() - 1) {
            currentWord += line[i];
            split.push_back(currentWord);
        }
        else {
            currentWord += line[i];
        }
    }

    return split;
}

// Determines if the token value is an integer
bool bIsInteger(std::string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

// Determines if the token values is a floating point
bool bIsFloat(std::string s) 
{
    int period_counter = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '.') ++period_counter;
        if (period_counter > 1) return false;
        if (!(std::isdigit(s[i])) && s[i] != '.') return false;
    }
    return true;
}

// Determines if token is a string literal
bool bIsStringLiteral(std::string s)
{
    return (s[0] == '"') && (s[s.size() - 1] == '"');
}

// Determines if token is an operator term
bool bIsOperator(std::string s)
{
    for (auto op : operator_terms) {
        if (s == op) return true;
    }
    return false;
}

// Determines if token is a boolean
bool bIsBool(std::string s)
{
    return (s == "true") || (s == "false");
}

int perform_operation(int a, int b, std::string op)
{
    if (op == "plus") return a + b;
    if (op == "minus") return a - b;
    if (op == "times") return a * b;
    if (op == "dividedby") return a / b;
    if (op == "modulus") return a % b;
}
float perform_operation(float a, float b, std::string op)
{
    if (op == "plus") return a + b;
    if (op == "minus") return a - b;
    if (op == "times") return a * b;
    if (op == "dividedby") return a / b;
}