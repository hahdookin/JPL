#pragma once

/**********************************
 * Jess Programming Language (JPL)
 * Juevenile Esoteric Scripting System (JESS)
 * Types:
 * Int  I
 * Float F
 * Char C
 * Bool B
 * String S
 * StdFunc  0
 * Operator:
 *  +      -      *         /         %
 * plus, minus, times, divided by, modulus
 */


// All Declarations

// Namespace declaration
namespace jess {
    class Token;
    class Tokenized_Line;
}

std::vector<std::string> split_string(std::string line, char delimiter = ' ');
bool bIsInteger(std::string s);
bool bIsFloat(std::string s);
bool bIsStringLiteral(std::string s);
bool bIsOperator(std::string s);
bool bIsStdFunc(std::string s);
bool bIsBool(std::string s);
jess::Token perform_operation(jess::Token& tok1, jess::Token& tok2, std::string op);

// End of declarations

const std::string operator_terms[] = {
    "plus", "minus", "times", "dividedby", "modulus"
};

const std::string func_terms[] = {
    "say", "get"
};

const std::unordered_map<std::string, std::string> operators =
{
    {"plus", "+"},
    {"minus", "-"},
    {"times", "*"},
    {"divideby", "/"},
    {"modulus", "%"}
};

namespace jess
{
    class Token
    {
    public:
        unsigned char type;
        std::string sValue;

        signed int nValue;
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
            if (this->type == 'I') std::cout << "sVal: " << this->sValue << " | T: " << this->type << " | nVal: " << this->nValue << std::endl;
            if (this->type == 'F') std::cout << "sVal: " << this->sValue << " | T: " << this->type << " | fVal: " << this->fValue << std::endl;
            if (this->type == 'B') std::cout << "sVal: " << this->sValue << " | T: " << this->type << " | bVal: " << this->bValue << std::endl;
            if (this->type == 'O') std::cout << "sVal: " << this->sValue << " | T: " << this->type << " | " << std::endl;
            if (this->type == '0') std::cout << "sVal: " << this->sValue << " | T: " << this->type << " | " << std::endl;
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
            // Check for operator
            for (int i = this->line.size() - 1; i >= 0; --i)
            {
                if (this->line[i].type == 'O')
                {

                }
            }

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

jess::Token perform_operation(jess::Token& a, jess::Token& b, std::string op)
{
    if ((a.type == 'F' || b.type == 'F') && op != "modulus")
    {
        if (op == "plus") return a + b;
        if (op == "minus") return a - b;
        if (op == "times") return a * b;
        if (op == "dividedby") return a / b;
    }
    else
    {
        if (op == "plus") return a + b;
        if (op == "minus") return a - b;
        if (op == "times") return a * b;
        if (op == "dividedby") return a / b;
        if (op == "modulus") return a % b;
    }

}
void perform_io(jess::Token obj, std::string op)
{
    if (op == "say") std::cout << obj.sValue << std::endl;
}