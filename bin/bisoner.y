%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::ParaDriver* driver}

%code requires{

    #include <iostream>
    #include <string>

    #include "../src/frontend/headers/Ioperator.h"
    #include "../src/frontend/headers/Istatement.h"
    #include "../src/frontend/headers/Operator_wrapper.h"
    
    int define_math_op(std::string& op);
    std::pair<int, bool> define_log_op(std::string& op);

    namespace yy{ class ParaDriver; }

    using namespace ParaCL;
    using std::pair;
}

%code{

    #include "../src/ParaDriver.hpp"

    namespace yy{

        parser::token_type yylex(parser::semantic_type* yyval, ParaDriver* driver);
    }
}

%token <int> SCOL
%token <int> FLB
%token <int> FRB
%token <int> LB
%token <int> RB
%token <int> IF_
%token <int> WHILE_
%token <int> ASSIGN_
%token <int> OR
%token <int> AND
%token <int> PRINT_
%token <int> INPUT

%token <pair<int, int>> NUM
%token <pair<std::string*, int>> VAR
%token <pair<std::string*, int>> LOGIC
%token <pair<std::string*, int>> OP_MUL
%token <pair<std::string*, int>> OP_SUM 

%nterm <Num*> num_
%nterm <Var*> var_
%nterm <Istatement*> program
%nterm <Ioperator*> operand 
%nterm <Istatement*> statement
%nterm <Istatement*> statement_list
%nterm <Istatement*> if
%nterm <Istatement*> while 
%nterm <Istatement*> assign
%nterm <Istatement*> print
%nterm <Ioperator*> expr
%nterm <Ioperator*> expr_
%nterm <Ioperator*> expr_and
%nterm <Ioperator*> expr_and_
%nterm <Ioperator*> expr_log 
%nterm <Wrapper*> expr_log_
%nterm <Ioperator*> expr_sum
%nterm <Wrapper*> expr_sum_
%nterm <Ioperator*> expr_mul
%nterm <Wrapper*> expr_mul_

%start program

%%

program: statement_list                     { driver->add_root($1); }
         | %empty                           { driver->add_root(nullptr); }
;       

statement_list: statement                   { $$ = $1; }
                | statement_list statement  { $1->add_next_statement($2); $$ = $1;}
                

statement:  if                              { $$ = $1; }
            | while                         { $$ = $1; }
            | assign                        { $$ = $1; }
            | print                         { $$ = $1; }
;

var_:       VAR                             { $$ = new Var(*($1.first));
                                              $$->set_line_num($1.second);
                                              delete $1.first; }
;

num_:       NUM                             { $$ = new Num($1.first);
                                              $$->set_line_num($1.second); }
;

operand:    var_                            { $$ = $1; }
            | num_                          { $$ = $1; }
            | LB expr RB                    { $$ = $2; }
;

if: IF_ expr RB FLB statement_list FRB           { $$ = new If($2, $5);
                                                   $$->set_line_num($1); }
;

while:  WHILE_ expr RB FLB statement_list FRB    { $$ = new While($2, $5);
                                                   $$->set_line_num($1); }
;

assign: var_ ASSIGN_ expr SCOL               { $$ = new Assign($1, $3); $$->set_line_num($2); }
        | var_ ASSIGN_ INPUT SCOL            { $$ = new Assign($1, new Input); $$->set_line_num($2); }
;

print:  PRINT_ var_ SCOL                     { $$ = new Print($2);
                                               $$->set_line_num($1); }
;

expr:   expr_and expr_                    { if ($2 != nullptr){ 

                                                $$ = new LogicOperator(std::make_pair(Or, false), $1, $2); 
                                            }else { 

                                                $$ = $1; 
                                            } }
;
expr_:  OR expr_and expr_                 { if ($3 != nullptr){ 

                                                $$ = new LogicOperator(std::make_pair(Or, false), $2, $3); 
                                            }else { 
                                                
                                                $$ = $2; 
                                            }  }
        | %empty                          { $$ = nullptr; }
;

expr_and:   expr_log expr_and_            { if ($2 != nullptr){ 

                                                $$ = new LogicOperator(std::make_pair(And, false), $1, $2); 
                                            }else { 

                                                $$ = $1;; 
                                            } }
;
expr_and_:  AND expr_log expr_and_        { if ($3 != nullptr){ 

                                                $$ = new LogicOperator(std::make_pair(And, false), $2, $3); 
                                            }else {

                                                $$ = $2;
                                            } }
            | %empty                      { $$ = nullptr; }
;

expr_log:   expr_sum expr_log_            { if ($2 != nullptr){ 
                                                
                                                $$ = $2->make_log_op($1);
                                                delete $2;
                                            }else { 

                                                $$ = $1; 
                                            } }
;
expr_log_:  LOGIC expr_sum expr_log_      { if ($3 != nullptr){ 

                                                Ioperator* next_op = $3->make_log_op($2);
                                                $$ = new Wrapper(*($1.first), next_op);
                                                delete $3;  
                                                delete $1.first;                                          
                                            }else { 
                                                
                                                $$ = new Wrapper(*($1.first), $2); 
                                                delete $1.first;
                                            } }
            | %empty                      { $$ = nullptr; }
;

expr_sum:   expr_mul expr_sum_            { if ($2 != nullptr){ 

                                                $$ = $2->make_math_op($1);
                                                delete $2;
                                            }else { 

                                                $$ = $1; 
                                            } }
;
expr_sum_:  OP_SUM expr_mul expr_sum_     { if ($3 != nullptr){ 

                                                Ioperator* next_op = $3->make_math_op($2);
                                                $$ = new Wrapper(*($1.first), next_op);
                                                delete $3; 
                                                delete $1.first;
                                            }else { 
                                                
                                                $$ = new Wrapper(*($1.first), $2); 
                                                delete $1.first;
                                            } }
            | %empty                      { $$ = nullptr; }
;

expr_mul:   operand expr_mul_             { if ($2 != nullptr){ 

                                                $$ = $2->make_math_op($1);
                                                delete $2;
                                            }else {
                                                
                                                $$ = $1; 
                                            } }
;
expr_mul_:  OP_MUL operand expr_mul_      { if ($3 != nullptr){ 

                                                Ioperator* next_op = $3->make_math_op($2);                    
                                                $$ = new Wrapper(*($1.first), next_op);
                                                delete $3;
                                                delete $1.first;
                                            }else { 

                                                $$ = new Wrapper(*($1.first), $2); 
                                                delete $1.first;
                                            } }
            | %empty                      { $$ = nullptr; }
;


%%

namespace yy{

    parser::token_type yylex(parser::semantic_type* yylval, ParaDriver* driver){

        return driver->yylex(yylval);
    }

    void parser::error(const std::string& token){ 
        
        std::cout << "Undefined expression" << std::endl; // << "in line " << yylloc.first_line << std::endl;  
    }    
}
