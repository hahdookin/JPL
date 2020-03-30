#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>

/**********************************
 * Jess Programming Language (JPL)
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
        char type;
        std::string sValue;

        int nValue;
        float fValue;
        bool bValue;

    public:
        Token(std::string value)
        {
            this->sValue = value;
        }

        void set_type()
        {
            if (bIsOperator(this->sValue)) this->type = 'O';

            if (bIsInteger(this->sValue))
            {
                this->type = 'I';
                this->nValue = std::stoi(this->sValue);
                this->fValue = std::stof(this->sValue);
            }

            if (bIsFloat(this->sValue))
            {
                this->type = 'F';
                this->fValue = std::stof(this->sValue);
                this->nValue = std::stoi(this->sValue);
            }

            if (bIsStringLiteral(this->sValue)) this->type = 'S';

            if (bIsBool(this->sValue))
            {
                this->type = 'B';
                this->bValue = this->sValue == "true";
            }
        }
    };
    
    class Tokenized_Line
    {
    public:
        Tokenized_Line()
        {

        }
    };
}

int main()
{
    std::string file = "code.txt";

    std::string line;
    std::ifstream code(file);

    if (code.is_open())
    {
        while (std::getline(code, line))
        {
            std::vector<std::string> line_split = split_string(line, ' ');

            std::vector<jess::Token> tokenized_line = {}; // { I 5 , O plus, I 8 }

            for (auto word : line_split)
            {
                jess::Token token(word);
                token.set_type();
                tokenized_line.push_back(token);

                /*std::cout << token.sValue << " : " << token.type << " : ";
                if (token.type == 'I') std::cout << token.nValue;
                if (token.type == 'B') std::cout << token.bValue;
                std::cout << std::endl;*/
            }

            for (int i = 0; i < tokenized_line.size(); ++i)
            {
                if (tokenized_line[i].type == 'O')
                {
                    // Int to float conversion
                    if (tokenized_line[i - 1].type == 'F' || tokenized_line[i + 1].type == 'F') {
                        float res = perform_operation(tokenized_line[i - 1].fValue, tokenized_line[i + 1].fValue, tokenized_line[i].sValue);
                        std::cout << res << std::endl;
                    }
                    else {
                        int res = perform_operation(tokenized_line[i - 1].fValue, tokenized_line[i + 1].fValue, tokenized_line[i].sValue);
                        std::cout << res << std::endl;
                    }


                    
                }
            }
            
        }
        code.close();
    }

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