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
bool bIsVariable(std::string s);
bool bVariableExists(std::string varName);

jess::Token perform_operation(jess::Token &tok1, jess::Token &tok2, std::string op);
void say(jess::Token &obj);
void get(std::string varName);

// End of declarations

bool DEBUG_MODE = false;

const std::string operator_terms[] = {
    "plus", "+", "minus", "-", 
    "times", "*", "dividedby", "/", 
    "modulus", "%"
};

const std::string func_terms[] = {
    "say", "get"
};

const std::string assignment_operator = "is";

// Stores token variables
std::unordered_map<std::string, jess::Token> variables = {};

namespace jess
{
    
    class Token
    {
    public:
        std::string vName = "";

        char type; 
        std::string sValue = "";

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
            std::cout << "T: " << this->type;
            std::cout << " | sVal: " << this->sValue;
            std::cout << " | nVal: " << this->nValue;
            std::cout << " | fVal: " << this->fValue;
            std::cout << " | bVal: " << this->bValue;
            std::cout << " | vName: " << this->vName;

            std::cout << std::endl;          
           
        }

        // Determines the type of the token i.e. Int, Bool, Char
        void set_type()
        {
            if (bIsOperator(this->sValue))
            {
                this->type = 'O';

                this->nValue = 1;
                this->fValue = 1.0;
                this->bValue = true;
            }

            else if (bIsStdFunc(this->sValue))
            {
                this->type = '0';

                this->nValue = 1;
                this->fValue = 1.0;
                this->bValue = true;
            }

            else if (bIsInteger(this->sValue))
            {
                this->type = 'I';
                this->nValue = std::stoi(this->sValue);

                this->fValue = std::stod(this->sValue);
                this->bValue = this->nValue != 0;
            }

            else if (bIsFloat(this->sValue))
            {
                if (this->sValue[0] == '.') this->sValue = "0" + this->sValue;

                this->type = 'F';
                this->fValue = std::stod(this->sValue);

                this->nValue = std::stoi(this->sValue);
                this->bValue = this->fValue != 0;
            }

            else if (bIsStringLiteral(this->sValue))
            {
                this->type = 'S';

                this->nValue = 1;
                this->fValue = 1;
                this->bValue = this->sValue == "";
            }

            else if (bIsBool(this->sValue))
            {
                this->type = 'B';
                this->bValue = this->sValue == "true";

                this->nValue = this->bValue == true ? 1 : 0;
                this->fValue = this->bValue == true ? 1 : 0;
            }

            else if (bIsVariable(this->sValue))
            {
                this->type = 'V';
                this->vName = this->sValue;

                //variables[this->vName] = *this;
                
                this->bValue = false;
                this->nValue = 0;
                this->fValue = 0.0;
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
            else if (this->type == 'S')
            {
                res.type = 'S';
                res.sValue = this->sValue.substr(0, this->sValue.size() - 1) + obj.sValue.substr(1, obj.sValue.size() - 1);
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
        /*Token operator = (Token& obj)
        {
            this->sValue = obj.sValue;
            this->nValue = obj.nValue;
            this->fValue = obj.fValue;
            this->bValue = obj.bValue;
            this->vName = obj.vName;

            return *this;
        }*/
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
            // { get, x }
            // { say, x, plus, 5 }

            // Check for variable tokens and replace them with their values;
            for (int i = 0; i < this->line.size(); ++i)
            {
                
                if (bVariableExists(this->line[i].vName))
                {
                    // DEBUG
                    if (DEBUG_MODE) std::cout << "Setting " << this->line[i].sValue << " to global variable: " << variables[this->line[i].vName].vName << std::endl;

                    this->line[i] = variables[this->line[i].vName];
                }
            }

            for (int i = this->line.size() - 1; i >= 0; --i)
            {
                if (this->line[i].type == 'O')
                {
                    Token res;
                    
                    //if (bVariableExists(this->line[i + 1].vName)) this->line[i + 1] = variables[this->line[i + 1].vName];
                    //if (bVariableExists(this->line[i - 1].vName)) this->line[i - 1] = variables[this->line[i - 1].vName];

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
                    // assignment operator
                    // { x, is, 10 }
                    if (this->line[i].sValue == "is")
                    {
                        std::string temp = this->line[i - 1].vName;
                        this->line[i - 1] = this->line[i + 1];
                        this->line[i - 1].vName = temp;
                        variables[this->line[i - 1].vName] = this->line[i - 1]; // Updates the variable upon assignment
                        // DEBUG
                        if (DEBUG_MODE) std::cout << "Updating global variable: " << this->line[i - 1].vName;

                    }

                    // std SAY
                    if (this->line[i].sValue == "say")
                    {
                                              

                        if (bVariableExists(this->line[i + 1].vName))
                        {
                            say(variables[this->line[i + 1].vName]);
                        }
                        else {
                            say(this->line[i + 1]);
                            /*for (int j = i; j < this->line.size(); ++j)
                            {
                                say(this->line[j]);
                            }*/
                        }
                        
                    }
                        
                    // std GET
                    if (this->line[i].sValue == "get")
                    {
                        get(this->line[i + 1].vName);
                    }
                        
                }
            }


            
            // figure out grammar of line

            // maybe return what to do
        }
    };
}

// Splits string by delimiter character (fixed for not splitting spaces in string literals)
std::vector<std::string> split_string(std::string line, char delimiter)
{
    std::vector<std::string> split = {};

    std::string currentWord = "";
    bool inStringLiteral = false;
    int nQuotMarks = 0;
    for (unsigned int i = 0; i < line.size(); ++i) {
        if (line[i] == '"' && !inStringLiteral) inStringLiteral = true;

        if (!inStringLiteral) {
            if (line[i] == delimiter)
            {
                if (currentWord != "") split.push_back(currentWord);
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
        else {
            if (line[i] == '"') ++nQuotMarks;
            currentWord += line[i];
            if (line[i] == '"' && nQuotMarks == 2) {
                inStringLiteral = false;
                nQuotMarks = 0;
                split.push_back(currentWord);
                currentWord = "";
            }
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

// Determines if the token value is a floating point
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
    if (s == assignment_operator) return true;
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

// Determines if token is a variable
bool bIsVariable(std::string s)
{
    // Make variable name not contain the following:
    // !@#$%^&*()+-";></?:'~`[]{}|\.
    return true;
}

// Checks if variable exists
bool bVariableExists(std::string varName)
{
    if (variables.empty()) return false;
    std::unordered_map<std::string, jess::Token>::iterator it;
    for (it = variables.begin(); it != variables.end(); it++)
    {
        if (it->first == varName) return true;
    }
    return false;
}

jess::Token perform_operation(jess::Token &a, jess::Token &b, std::string op)
{
    if (op == "plus" || op == "+") return a + b;
    if (op == "minus" || op == "-") return a - b;
    if (op == "times" || op == "*") return a * b;
    if (op == "dividedby" || op == "/") return a / b;
    if (op == "modulus" || op == "%") return a % b;
}
void say(jess::Token &obj)
{
    if (obj.type == 'V') obj = variables[obj.vName];
    if (obj.type == 'F') std::cout << obj.fValue << std::endl;
    if (obj.type == 'I') std::cout << obj.nValue << std::endl;
    if (obj.type == 'B') std::cout << obj.bValue << std::endl;
    if (obj.type == 'S') std::cout << obj.sValue << std::endl;
  
}
void get(std::string varName) // { get, apple }
{
    std::string input;
    std::cin >> input;
    jess::Token token(input);
    token.vName = varName;
    variables[varName] = token;
    // DEBUG
    if (DEBUG_MODE) std::cout << "Added glob variable: " << varName << std::endl;
}