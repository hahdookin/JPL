#pragma once

#include <string>
#include <vector>
#include <unordered_map>


/**********************************
 * JESS Programming Language (JPL)
 * Juevenile Esoteric Scripting System (JESS)
 * Types:
 * Int  I
 * Float F
 * Char C
 * Bool B
 * String S
 * StdFunc  0
 * Operator:
 *  +      -      *        /         %     =
 * plus, minus, times, dividedby, modulus, is
 */


 // All Declarations

 // Namespace declaration
namespace jess {
    class Token;
    class Tokenized_Line;
}

// Function declarations
std::vector<std::string> split_string(std::string line, char delimiter = ' ');
bool bIsInteger(std::string s);
bool bIsFloat(std::string s);
bool bIsStringLiteral(std::string s);
bool bIsOperator(std::string s);
bool bIsStdFunc(std::string s);
bool bIsBool(std::string s);
jess::Token perform_operation(jess::Token &tok1, jess::Token &tok2, std::string op);
void perform_io(jess::Token obj, std::string op);

// End of declarations

const std::string operator_terms[] = {
    "plus", "minus", "times", "dividedby", 
    "modulus", "is"
};

const std::string func_terms[] = {
    "say", "get"
};

//const std::unordered_map<std::string, std::string> operators =
//{
//    {"plus", operator_terms}
//};

namespace jess
{
    class Token
    {
    public:
        unsigned char type;
        std::string sValue;

        int nValue;
        double fValue;
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
            if (this->type == 'I') std::cout << "T: " << this->type << " | sVal: " << this->sValue << " | nVal: " << this->nValue << std::endl;
            if (this->type == 'F') std::cout << "T: " << this->type << " | sVal: " << this->sValue << " | fVal: " << this->fValue << std::endl;
            if (this->type == 'B') std::cout << "T: " << this->type << " | sVal: " << this->sValue << " | bVal: " << this->bValue << std::endl;
            if (this->type == 'O') std::cout << "T: " << this->type << " | sVal: " << this->sValue << std::endl;
            if (this->type == '0') std::cout << "T: " << this->type << " | sVal: " << this->sValue << std::endl;
        }

        // Determines the type of the token i.e. Int, Bool, Char
        void set_type()
        {
            if (bIsOperator(this->sValue)) this->type = 'O';

            else if (bIsStdFunc(this->sValue)) this->type = '0';

            else if (bIsInteger(this->sValue))
            {
                this->type = 'I';
                this->nValue = std::stoi(this->sValue);
                this->fValue = std::stod(this->sValue);
            }

            else if (bIsFloat(this->sValue))
            {
                if (this->sValue[0] == '.') this->sValue = "0" + this->sValue;
                this->type = 'F';
                this->fValue = std::stod(this->sValue);
                this->nValue = std::stoi(this->sValue);
            }

            else if (bIsStringLiteral(this->sValue)) this->type = 'S';

            else if (bIsBool(this->sValue))
            {
                this->type = 'B';
                this->bValue = this->sValue == "true";
            }
        }

        Token operator + (Token& obj)
        {
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

        Token operator - (Token& obj)
        {
            Token res;
            if (this->type == 'F' || obj.type == 'F')
            {
                res.type = 'F';
                res.fValue = this->fValue - obj.fValue;
            }
            else {
                res.type = this->type;
                res.nValue = this->nValue - obj.nValue;
            }

            return res;
        }

        Token operator * (Token& obj)
        {
            Token res;
            if (this->type == 'F' || obj.type == 'F')
            {
                res.type = 'F';
                res.fValue = this->fValue * obj.fValue;
            }
            else {
                res.type = this->type;
                res.nValue = this->nValue * obj.nValue;
            }

            return res;
        }

        Token operator / (Token& obj)
        {
            Token res;
            if (this->type == 'F' || obj.type == 'F')
            {
                res.type = 'F';
                res.fValue = this->fValue / obj.fValue;
            }
            else {
                res.type = this->type;
                res.nValue = this->nValue / obj.nValue;
            }

            return res;
        }

        Token operator % (Token& obj)
        {
            Token res;
            res.type = 'I';
            res.nValue = this->nValue % obj.nValue;

            return res;
        }
    };

    class Tokenized_Line
    {
    public:
        std::vector<Token> line = {}; // { say, 5, plus, 2 }
    public:
        Tokenized_Line()
        {

        }
        void append(Token token)
        {
            this->line.push_back(token);
        }
        void interpret_line()
        {
            // iterate over tokens in line
            // Check for operator and reduce line
            // { say, 5, plus, 2 } => { say, 7 }
            for (int i = this->line.size() - 1; i >= 0; --i)
            {
                if (this->line[i].type == 'O')
                {
                    Token res;
                    
                    res = perform_operation(this->line[i - 1], this->line[i + 1], this->line[i].sValue);

                    // COME BACK TO THIS
                    this->line.erase(this->line.begin() + 1, this->line.end());

                    this->line.push_back(res);

                }
            }

            for (int i = 0; i < this->line.size(); ++i)
            {
                if (this->line[i].type == '0')
                {
                    perform_io(this->line[i + 1], this->line[i].sValue);
                }
            }


            /*for (auto tok : this->line)
            {
                tok.print();
            }*/

            // figure out grammar of line

            // maybe return what to do
        }
    };
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

// Determines if token is standard lib function
bool bIsStdFunc(std::string s)
{
    for (auto func : func_terms) {
        if (s == func) return true;
    }
    return false;
}

// Determines if token is a boolean
bool bIsBool(std::string s)
{
    return (s == "true") || (s == "false");
}

jess::Token perform_operation(jess::Token &a, jess::Token &b, std::string op)
{
    if (op == "plus") return a + b;
    if (op == "minus") return a - b;
    if (op == "times") return a * b;
    if (op == "dividedby") return a / b;
    if (op == "modulus") return a % b;
}
void perform_io(jess::Token obj, std::string op)
{
    if (op == "say")
    {
        if (obj.type == 'F') std::cout << obj.fValue << std::endl;
        if (obj.type == 'I') std::cout << obj.nValue << std::endl;
        if (obj.type == 'B') std::cout << obj.bValue << std::endl;
        if (obj.type == 'S') std::cout << obj.sValue << std::endl;
    }
}
