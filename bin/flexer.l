%option yylineno
%option c++

%{
    
#include "Paragrammar.tab.hh"

size_t cur_col = 0, cur_col_end = 0, cur_line = 0;
std::string line;  
bool error_occurred = false;

#define YY_USER_ACTION { cur_col = cur_col_end; cur_col_end += yyleng; }

%}

WS      [ \t\v]+
PRINT   "print"
INPUT   "?"
SCOL    ";"
NEW_LIN "\n"
COMMA   ","


DIGIT   [0-9]
DIGIT1  [1-9]
NUM     ({DIGIT1}{DIGIT}*)|"0"

LETTER  [a-z]|[A-Z]
UNDERLI "_"
WORD    ({LETTER}|{UNDERLI})({UNDERLI}|{NUM}|{LETTER})*

OP_SUM  [\+]
OP_SUB  [\-]
OP_MUL  [\*\/]

UNEQUAL "!="
EQUAL   "=="
GRETEQ  ">="
LESSEQ  "<="
LOGIC   {EQUAL}|{UNEQUAL}|{GRETEQ}|{LESSEQ}|[\<\>]

OR  "||"
AND "&&"

ASSIGN [\=]

FLB "{"
FRB "}"
LB  "("
RB  ")"
IF_ "if"
IF  {IF_}{WS}*{LB}

WHILE_ "while"
WHILE {WHILE_}{WS}*{LB}

TYPEDEF_ "typedef"
TYPEDEF  {TYPEDEF_}{WS}*{LB}

%%

{WS}            
\n.*                { cur_col = 0; cur_col_end = 0; line.clear(); line.append(yytext + 1); yyless(1); cur_line++; }
{OR}                { return yy::parser::token_type::OR; }
{AND}               { return yy::parser::token_type::AND; }
{OP_SUM}            { return yy::parser::token_type::OP_SUM; }
{OP_SUB}            { return yy::parser::token_type::OP_SUB; }
{OP_MUL}            { return yy::parser::token_type::OP_MUL; }
{NUM}               { return yy::parser::token_type::NUM; }
{LOGIC}             { return yy::parser::token_type::LOGIC; }
{ASSIGN}            { return yy::parser::token_type::ASSIGN; }
{IF}                { return yy::parser::token_type::IF_; }
{WHILE}             { return yy::parser::token_type::WHILE_; }
{PRINT}             { return yy::parser::token_type::PRINT_; }
{TYPEDEF}           { return yy::parser::token_type::TYPEDEF_; }
{WORD}              { return yy::parser::token_type::WORD; }
{INPUT}             { return yy::parser::token_type::INPUT; }
{COMMA}             { return yy::parser::token_type::COMMA; }
{SCOL}              { return yy::parser::token_type::SCOL; }
{FLB}               { return yy::parser::token_type::FLB; }
{FRB}               { return yy::parser::token_type::FRB; }
{LB}                { return yy::parser::token_type::LB; }
{RB}                { return yy::parser::token_type::RB; }
.                   { return -1; }  

%%