%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::ParaDriver* driver}

%code requires{

    #include <iostream>

    namespace yy{ class ParaDriver; }
}

%code{

    #include "../src/headers/ParaDriver.hpp"

    namespace yy{

        parser::token_type yylex(parser::semantic_type* yyval, ParaDriver* driver);
    }
}


%token
    SCOL    ";" 
    FLB     "{"
    FRB     "}"
    LB      "("
    RB      ")"
;

%token <int> PRINT_
%token <int> INPUT
%token <int> NUM
%token <int> VAR
%token <int> OP_SUM
%token <int> OP_MUL
%token <int> LOGIC
%token <int> ASSIGN_
%token <int> IF_
%token <int> WHILE_
%token <int> OR
%token <int> AND

%nterm <int> statement
%nterm <int> statement_list
%nterm <int> if
%nterm <int> while 
%nterm <int> assign
%nterm <int> print
%nterm <int> expr
%nterm <int> expr_
%nterm <int> expr_and
%nterm <int> expr_and_
%nterm <int> expr_log 
%nterm <int> expr_log_
%nterm <int> expr_sum
%nterm <int> expr_sum_
%nterm <int> expr_mul
%nterm <int> expr_mul_

%start program

%%

program: statement_list
         | %empty
;

statement_list: statement
                | statement_list statement   
                

statement:  if                              { std::cout << "if in statement" << std::endl; }
            | while                         { std::cout << "while in statement" << std::endl; }
            | assign                        { std::cout << "assign in statement" << std::endl; }
            | print                         { std::cout << "print in statement" << std::endl; }
;

operand:    VAR                             { std::cout << "var in operand" << std::endl; }
            | NUM                           { std::cout << "num in operand" << std::endl; }
            | LB expr RB                    { std::cout << "expr in operand" << std::endl; }
;

if: IF_ expr RB FLB statement_list FRB           { std::cout << "if" << std::endl; }
;

while:  WHILE_ expr RB FLB statement_list FRB    { std::cout << "while" << std::endl; }
;

assign: VAR ASSIGN_ expr SCOL            { std::cout << "var assign" << std::endl; }
        | VAR ASSIGN_ INPUT SCOL            { std::cout << " var assign input" << std::endl; }
;

print:  PRINT_ VAR SCOL                     { std::cout << "print var" << std::endl; }
;

expr:   expr_and expr_                      { std::cout << "expr or" << std::endl; }
;
expr_:  OR expr_and expr_                   { std::cout << "or" << std::endl; }
        | %empty                            { std::cout << "or end -------" << std::endl;}
;

expr_and:   expr_log expr_and_              { std::cout << "expr and" << std::endl; }
;
expr_and_:  AND expr_log expr_and_          { std::cout << "and" << std::endl; }
            | %empty                        { std::cout << "and end -------" << std::endl;}
;

expr_log:   expr_sum expr_log_              { std::cout << "expr logic" << std::endl; }
;
expr_log_:  LOGIC expr_sum expr_log_        { std::cout << "logic" << std::endl; }
            | %empty                        { std::cout << "logic end -------" << std::endl;}
;

expr_sum:   expr_mul expr_sum_              { std::cout << "expr sum" << std::endl; }
;
expr_sum_:  OP_SUM expr_mul expr_sum_       { std::cout << "sum" << std::endl; }
            | %empty                        { std::cout << "sum end -------" << std::endl;}
;

expr_mul:   operand expr_mul_               { std::cout << "expr mul" << std::endl; }
;
expr_mul_:  OP_MUL operand expr_mul_        { std::cout << "mul" << std::endl; }
            | %empty                        { std::cout << "mul end -------" << std::endl;}
;


%%

namespace yy{

    parser::token_type yylex(parser::semantic_type* yylval,                         
                                ParaDriver* driver)
    {
        return driver->yylex(yylval);
    }

    void parser::error(const std::string&){ std::cout << "error" << std::endl; }    
}
