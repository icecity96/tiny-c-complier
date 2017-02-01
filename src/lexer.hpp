//
// Created by ice_city on 1/25/17.
//

#ifndef CH03_LEXER_HPP
#define CH03_LEXER_HPP

//using hash_set( O(1) ) instead of set( O(lgn) )
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>

const std::unordered_set<std::string> KEY_WORD_SET = {
        "if",       "else",     "while",    "break",    "continue",
        "for",      "double",   "int",      "float",    "long",
        "short",    "switch",   "case",     "return",   "void"
};

const std::unordered_set<std::string> SEPARATOR_SET = {
        "{",    "}",    "[",    "]",    "(",
        ")",    "~",    ",",    ";",    ".",
        "?",    ":",
};

const std::unordered_set<std::string> OPERATOR_SET = {
        "+",    "++",   "-",    "--",   "+=",
        "-=",   "*",    "*=",   "%",    "%=",
        "->",   "|",    "||",   "|=",   "/",
        "/=",   ">",    "<",    ">=",   "<=",
        "=",    "==",   "!=",   "!"
};

const std::unordered_map<std::string,int> CATEGORY_MAP = {
        {"EOF", -1},
        {"ID", 256},
        {"double", 265},
        {"int", 266},
        {"break", 267},
        {"else", 268},
        {"switch", 269},
        {"case", 270},
        {"char", 271},
        {"return", 272},
        {"float", 273},
        {"continue", 274},
        {"for", 275},
        {"void", 276},
        {"do", 277},
        {"if", 278},
        {"while", 279},
        {"static", 280},
        {"{", 281},
        {"}", 282},
        {"[", 283},
        {"]", 284},
        {"(", 285},
        {")", 286},
        {"~", 287},
        {",", 288},
        {";", 289},
        {"?", 290},
        {":", 291},
        {"<", 292},
        {"<=", 293},
        {">", 294},
        {">=", 295},
        {"=", 296},
        {"==", 297},
        {"|", 298},
        {"||", 299},
        {"|=", 300},
        {"^", 301},
        {"^=", 302},
        {"&", 303},
        {"&&", 304},
        {"&=", 305},
        {"%", 306},
        {"%=", 307},
        {"+", 308},
        {"++", 309},
        {"+=", 310},
        {"-", 311},
        {"--", 312},
        {"-=", 313},
        {"->", 314},
        {"/", 315},
        {"/=", 316},
        {"*", 317},
        {"*=", 318},
        {"!", 319},
        {"!=", 320},
        {"INT10", 321},
        {"FLOAT", 322},
        {"STRING", 323}
};

struct token
{
    std::string tag;
    std::string value;
    int         id;
public:
    token(std::string tag, std::string value, int id) : tag(tag), value(value), id(id) {};
    std::string to_string()
    {
        return "( " + tag + " : " + std::to_string(id) + " : " + value +" )" + "\n";
    }
};

int current_row = -1;
int current_line = 0;
std::vector<std::string> lines;

inline bool is_keyword(std::string& s)
{
   return KEY_WORD_SET.find(s) != KEY_WORD_SET.end();
}

inline bool is_separator(const std::string& s)
{
   return SEPARATOR_SET.find(s) != SEPARATOR_SET.end();
}

inline bool is_operate(const std::string& s)
{
    return OPERATOR_SET.find(s) != OPERATOR_SET.end();
}

inline int get_cate_id(const std::string& s)
{
   return CATEGORY_MAP.find(s) == CATEGORY_MAP.end() ? -1
                                                     : CATEGORY_MAP.find(s)->second;
}

void read_source(std::istream& is)
{
    std::string temp_string;
    while (std::getline(is,temp_string))
    {
        lines.push_back(temp_string);
    }
    lines.shrink_to_fit();
}

char get_char()
{
    ++current_row;

    if (current_row == lines.at(static_cast<size_t >(current_line)).length())
    {
        current_line++;
        current_row = 0;
    }

    //after read all character
    if (current_line == lines.size())
    {
        return EOF;
    }

    return lines.at(static_cast<size_t >(current_line)).at(static_cast<size_t >(current_row));
}

char unget_char()
{
    --current_row;
    if (current_row < 0)
    {
        --current_line;
        current_row = static_cast<int>(lines.at(static_cast<size_t >(current_line)).length()) - 1;
    }
    return lines.at(static_cast<size_t >(current_line)).at(static_cast<size_t >(current_row));
}

inline void lexical_err_msg(std::string msg,
                            int line = current_line + 1,
                            int row = current_row + 1)
{
   std::cout << line << " : " << row << " Lexical error: " << msg <<std::endl;
}

const std::string EOF_STRING = "EOF";

token get_next_token()
{
    char current_char = ' ';
    //deal with space character
    while (isspace(current_char))
    {
        current_char = get_char();
    }
    if (current_char == EOF)
    {
        return token(EOF_STRING,EOF_STRING,get_cate_id(EOF_STRING));
    }

    //deal with number
    if (isdigit(current_char))
    {
        std::string value = "";
        while (isdigit(current_char))
        {
            value += current_char;
            current_char = get_char();
        }
        //integer
        if (current_char != '.')
        {
            unget_char();
            return token("INT", value, get_cate_id("INT10"));
        }
        //float number
        value += current_char;
        current_char = get_char();
        while (isdigit(current_char))
        {
            value += current_char;
            current_char = get_char();
        }
        unget_char();
        return token("FLOAT", value, get_cate_id("FLOAT"));
    }

    //deal with id
    if (isalpha(current_char) || current_char == '_')
    {
        std::string value = "";
        while (isalpha(current_char) || isdigit(current_char) || current_char == '_')
        {
            value += current_char;
            current_char = get_char();
        }
        unget_char();
        if (is_keyword(value))
        {
            return token(value, value, get_cate_id(value));
        }
        return token("ID", value, get_cate_id("ID"));
    }

    //deal with commend only support /**/
    if (current_char == '/')
    {
        char next_char = get_char();
        if (next_char == '*')
        {
            next_char = get_char();
            while (true)
            {
                if (next_char == EOF)
                {
                    lexical_err_msg("unteminated /* comment");
                    return token(EOF_STRING,EOF_STRING,get_cate_id(EOF_STRING));
                }
                if (next_char == '*')
                {
                    char end_char = get_char();
                    if (end_char == '/')
                    {
                        return get_next_token();
                    }
                    if (end_char == EOF)
                    {
                        lexical_err_msg("unteminated /* comment");
                        return token(EOF_STRING,EOF_STRING,get_cate_id(EOF_STRING));
                    }
                }
                next_char = get_char();
            }
        }
        else
        {
            if (next_char == '=')
            {
                std::string op = "";
                op.push_back(current_char);
                op.push_back(next_char);
                return token("OP", op, get_cate_id(op));
            }
            else
            {
                unget_char();
                std::string op = "";
                op.push_back(current_char);
                return token("OP", op, get_cate_id(op));
            }
        }
    }

    //deal with separator
    std::string temp = "";
    temp.push_back(current_char);

    if (is_separator(temp))
    {
        return token("SEP", temp, get_cate_id(temp));
    }

    //deal with op
    if (is_operate(temp))
    {
        std::string op = temp;
        current_char = get_char();
        if (is_operate(op + current_char))
        {
            op += current_char;
        }
        else
        {
            unget_char();
        }
        return token("OP", op, get_cate_id(op));
    }

    lexical_err_msg("unknown character");
    return token("ERROR", "ERROR", 0);
}
#endif //CH03_LEXER_HPP
