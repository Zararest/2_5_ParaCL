
%option c++

%{
    
#include "Paragrammar.tab.hh"

using std::cerr;
using std::endl;

%}

WS      [ \t\n\v]+
PRINT   "print"
INPUT   "?"
SCOLON  ";"


DIGIT   [0-9]
DIGIT1  [1-9]
NUM     ({DIGIT1}{DIGIT}*)|"0"

LETTER  [a-z]|[A-Z]
UNDERLI "_"
VAR     ({LETTER}|{UNDERLI})({UNDERLI}|{NUM}|{LETTER})*

OP_SUM  [\+\-]
OP_MUL  [\*\\]

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

%%

{WS}                /* skip blanks and tabs */
{OR}                { return yy::parser::token_type::OR; }
{AND}               { return yy::parser::token_type::AND; }
{OP_SUM}            { return yy::parser::token_type::OP_SUM; }
{OP_MUL}            { return yy::parser::token_type::OP_MUL; }
{NUM}               { return yy::parser::token_type::NUM; }
{LOGIC}             { return yy::parser::token_type::LOGIC; }
{ASSIGN}            { return yy::parser::token_type::ASSIGN_; }
{IF}                { return yy::parser::token_type::IF_; }
{WHILE}             { return yy::parser::token_type::WHILE_; }
{PRINT}             { return yy::parser::token_type::PRINT_; }
{VAR}               { return yy::parser::token_type::VAR; }
{INPUT}             { return yy::parser::token_type::INPUT; }
{SCOLON}            { return yy::parser::token_type::SCOL; }
{FLB}               { return yy::parser::token_type::FLB; }
{FRB}               { return yy::parser::token_type::FRB; }
{LB}                { return yy::parser::token_type::LB; }
{RB}                { return yy::parser::token_type::RB; }
.                   { return 1; }

%%