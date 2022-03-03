
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

EQUAL   "=="
GRETEQ  ">="
LESSEQ  "<="
LOGIC   {EQUAL}|{GRETEQ}|{LESSEQ}|[\<\>]

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
{OR}                { cerr << " logic or<" << yytext    << ">" << endl; return yy::parser::token_type::OR; }
{AND}               { cerr << " logic an<" << yytext    << ">" << endl; return yy::parser::token_type::AND; }
{OP_SUM}            { cerr << "operator <" << yytext[0] << ">" << endl; return yy::parser::token_type::OP_SUM; }
{OP_MUL}            { cerr << "operator <" << yytext[0] << ">" << endl; return yy::parser::token_type::OP_MUL; }
{NUM}               { cerr << " number  <" << yytext    << ">" << endl; return yy::parser::token_type::NUM; }
{LOGIC}             { cerr << " logic   <" << yytext    << ">" << endl; return yy::parser::token_type::LOGIC; }
{ASSIGN}            { cerr << " assign   " <<           endl; return yy::parser::token_type::ASSIGN_; }
{IF}                { cerr << " if       " <<           endl; return yy::parser::token_type::IF_; }
{WHILE}             { cerr << " while    " <<           endl; return yy::parser::token_type::WHILE_; }
{PRINT}             { cerr << " print    " <<           endl; return yy::parser::token_type::PRINT_; }
{VAR}               { cerr << " var name<" << yytext    << ">" << endl; return yy::parser::token_type::VAR; }
{INPUT}             { cerr << " INPUT    " <<           endl; return yy::parser::token_type::INPUT; }
{SCOLON}            { cerr << " SCOLON   " <<           endl; return yy::parser::token_type::SCOL; }
{FLB}               { cerr << " bracket <" << yytext[0] << ">" << endl; return yy::parser::token_type::FLB; }
{FRB}               { cerr << " bracket <" << yytext[0] << ">" << endl; return yy::parser::token_type::FRB; }
{LB}                { cerr << " bracket <" << yytext[0] << ">" << endl; return yy::parser::token_type::LB; }
{RB}                { cerr << " bracket <" << yytext[0] << ">" << endl; return yy::parser::token_type::RB; }
.                   { cerr << " UNKNOWN <" << yytext[0] << ">" << endl; return 1; }

%%