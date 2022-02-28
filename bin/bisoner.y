%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::ParaDriver* driver}

%code requires{

    #include <iostream>
    #include <string>
    
    int define_math_op(std::string& op);
    std::pair<int, bool> define_log_op(std::string& op);

    namespace yy{ class ParaDriver; }
}

%code{

    #include "../src/headers/ParaDriver.hpp"

    #include "../src/headers/Ioperator.h"
    #include "../src/headers/Istatement.h"

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
    IF_     "if"
    WHILE_  "while"
    ASSIGN_ "="
    OR      "||"
    AND     "&&"
;

%token <Print*> PRINT_
%token <Input*> INPUT
%token <int> NUM
%token <std::string> VAR
%token <std::string> LOGIC
%token <std::string> OP_MUL
%token <std::string> OP_SUM 

%nterm <Ioperand*> operand 
%nterm <Istatement*> statement
%nterm <Istatement*> statement_list
%nterm <If*> if
%nterm <While*> while 
%nterm <Assign*> assign
%nterm <Print*> print
%nterm <Ioperator*> expr
%nterm <Ioperator*> expr_
%nterm <LogicOperator*> expr_and
%nterm <LogicOperator*> expr_and_
%nterm <LogicOperator*> expr_log 
%nterm <std::pair<LogicOperator*, std::string>> expr_log_
%nterm <MathOperator*> expr_sum
%nterm <std::pair<MathOperator*, std::string>> expr_sum_
%nterm <MathOperator*> expr_mul
%nterm <std::pair<MathOperator*, std::string>> expr_mul_

%start program

%%

program: statement_list
         | %empty
;

statement_list: statement
                | statement_list statement   
                

statement:  if                              { && = $1; }
            | while                         { && = $1; }
            | assign                        { && = $1; }
            | print                         { && = $1; }
;

operand:    VAR                             { $$ = new Var{$1}; }
            | NUM                           { $$ = new Num{$1}; }
            | LB expr RB                    { $$ = $2; }
;

if: IF_ expr RB FLB statement_list FRB           { $$ = new If{$2, $5}; }
;

while:  WHILE_ expr RB FLB statement_list FRB    { $$ = new While{$2, $5}; }
;

assign: VAR ASSIGN_ expr SCOL               { $$ = new Assign{$1, $3}; }
        | VAR ASSIGN_ INPUT SCOL            { $$ = new Assign{$1, $3}; }
;

print:  PRINT_ VAR SCOL                     { $$ = new Print{$2}; }
;

expr:   expr_and expr_                      { if ($2 != nullptr){ $$ = new LogicOperator{Or, false, $1, $2} }else 
                                                { $$ = $1; } }
;
expr_:  OR expr_and expr_                   { if ($3 != nullptr){ $$ = new LogicOperator{Or, false, $2, $3} }else
                                                { $$ = $2; }  }
        | %empty                            { $$ = nullptr; }
;

expr_and:   expr_log expr_and_              { if ($2 != nullptr){ $$ = new LogicOperator{And, false, $1, $2} }else 
                                                { $$ = $1; } }
;
expr_and_:  AND expr_log expr_and_          { if ($3 != nullptr){ $$ = new LogicOperator{And, false, $2, $3} }else
                                                { $$ = $2;}  }
            | %empty                        { $$ = nullptr; }
;

expr_log:   expr_sum expr_log_              { if ($2 != nullptr){ $$ = new LogicOperator{define_log_op($2.second), $1, $2.first} }else 
                                                { $$ = $1; } }
;
expr_log_:  LOGIC expr_sum expr_log_        { if ($3 != nullptr){ $$ = std::make_pair(new LogicOperator{define_log_op($3.second), $2, $3.first}, $1) }else
                                                { $$ = std::make_pair($2, $1); } }
            | %empty                        { $$ = nullptr; }
;

expr_sum:   expr_mul expr_sum_              { if ($2 != nullptr){ $$ = new MathOperator{define_math_op($2.second), $1, $2.first} }else 
                                                { $$ = $1; } }
;
expr_sum_:  OP_SUM expr_mul expr_sum_       { if ($3 != nullptr){ $$ = std::make_pair(new MathOperator{define_math_op($3.second), $2, $3.first}, $1) }else
                                                { $$ = std::make_pair($2, $1); } }
            | %empty                        { $$ = nullptr; }
;

expr_mul:   operand expr_mul_               { if ($2 != nullptr){ $$ = new MathOperator{define_math_op($2.second), $1, $2.first} }else 
                                                { $$ = $1; } }
;
expr_mul_:  OP_MUL operand expr_mul_        { if ($3 != nullptr){ $$ = std::make_pair(new MathOperator{define_math_op($3.second), $2, $3.first}, $1) }else
                                                { $$ = std::make_pair($2, $1); } }
            | operand                       { $$ = $1; }
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
