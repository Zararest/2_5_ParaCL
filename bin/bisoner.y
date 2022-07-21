%language "c++"

%skeleton "lalr1.cc"

%defines
%define api.value.type variant
%define parse.error verbose

%locations 


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

    extern size_t cur_col, cur_col_end, cur_line;
    extern std::string line; 
    extern bool error_occurred;
}

%code{

    #include "../src/ParaDriver.hpp"

    namespace yy{

        parser::token_type yylex(parser::semantic_type* yyval, parser::location_type* loc, ParaDriver* driver);
    }
}

%token <int> COMMA      ","
%token <int> SCOL       ";"
%token <int> FLB        "{"
%token <int> FRB        "}"
%token <int> LB         "("
%token <int> RB         ")"
%token <int> IF_        "if"
%token <int> WHILE_     "while"
%token <int> ASSIGN     "="
%token <int> OR         "||"
%token <int> AND        "&&"
%token <int> PRINT_     "print"
%token <int> INPUT      "?" 
%token <int> TYPEDEF_   "typedef"

%token <pair<int, int>> NUM                   "number"
%token <pair<const std::string*, int>> WORD   "word"
%token <pair<const std::string*, int>> LOGIC  "logic operator"
%token <pair<const std::string*, int>> OP_MUL "math operator (* /)"
%token <pair<const std::string*, int>> OP_SUM "+"
%token <pair<const std::string*, int>> OP_SUB "-"

%nterm <Input*> input_
%nterm <Num*> num_
%nterm <Var*> var_
%nterm <Istatement*> program
%nterm <Ioperator*> operand 
%nterm <Istatement*> statement
%nterm <Scope*> scope
%nterm <Istatement*> if
%nterm <Istatement*> while 
%nterm <Istatement*> print
%nterm <Istatement*> expr_statement
%nterm <Istatement*> scope_statement
%nterm <Ioperator*> expr
%nterm <Ioperator*> expr_
%nterm <Ioperator*> expr_assign
%nterm <Ioperator*> expr_assign_
%nterm <Ioperator*> expr_and
%nterm <Ioperator*> expr_and_
%nterm <Ioperator*> expr_log 
%nterm <Wrapper*> expr_log_
%nterm <Ioperator*> expr_sum
%nterm <Wrapper*> expr_sum_
%nterm <Ioperator*> expr_sub
%nterm <Wrapper*> expr_sub_
%nterm <Ioperator*> expr_mul
%nterm <Wrapper*> expr_mul_
%nterm <Inode*> decl                  //надо поправить 
%nterm <Inode*> type_
%nterm <Inode*> function
%nterm <Inode*> global_object
%nterm <Inode*> global_object_set
%nterm <Inode*> type_decl
%nterm <Inode*> decl_set

%start program

%%

//на этапе управляемой токенизации избавились от лишних ;

/*------------------
* Правила для функций и переменных
* 1) определение функции аналогично С                                                              +
* 2) переменные могут быть: string, int, float, пользовательский тип                    
* 3) пользовательские типы определяются через ключевое слово typedef (*название*) {*перечисление*} +
* 4) програма состоит из функций, пользовательских определений и препроцессора
* 5) на этапе парсинга происходит промтейший препроцессор 
*   5.1) #entry *название первой функции*
* 6) пока из соображений простоты все перечисления идут с ;
------------------*/

/* TODO
* 1) сделать нормальную таблицу символов
*   1.1) в таблице хранится позиция для каждого токена 
    1.2) в таблице есть временный файл с исходным кодом 
    1.3) в таблице хранится начало каждой строки
*/

program: global_object_set          {  }
        | %empty                    { driver->add_root(nullptr); }
;

global_object_set:  global_object                       {}
                    | global_object_set global_object   {}

global_object:  function                                {}
                | type_decl                             {}


function:   type_ WORD LB decl_set RB  scope_statement  {} 
            | type_ WORD LB  RB  scope_statement        {}

type_decl:  TYPEDEF_ WORD RB FLB decl_set FRB           {}

decl_set:   decl SCOL                                   {}
            | decl_set decl SCOL                        {}


scope:  statement                   { $$ = new Scope; $$->add_statement($1); }
        | scope statement           { if ($2 != nullptr){
                                        $1->add_statement($2);
                                        $$ = $1;
                                    } else{
                                        $$ = $1;
                                    } }
;     

statement:  if                              { $$ = $1; }
            | while                         { $$ = $1; }
            | expr_statement                { $$ = $1; }
            | print                         { $$ = $1; }
            | scope_statement               { $$ = $1; }
            | decl  SCOL                    {}
            | error SCOL                    { $$ = nullptr; error_occurred = true; }
;

decl:       type_ var_                      {}  

type_:      WORD                            {}    

var_:       WORD                            { $$ = new Var(*($1.first));
                                              $$->set_line_num($1.second); }
;

num_:       NUM                             { $$ = new Num($1.first);
                                              $$->set_line_num($1.second); }
;

input_:     INPUT                           {
                                              $$ = new Input();
                                              $$->set_line_num($1); }
;

operand:    var_                            { $$ = $1; }
            | num_                          { $$ = $1; }
            | input_                        { $$ = $1; }
            | LB expr RB                    { $$ = $2; }
;

expr_statement: expr SCOL           { $$ = new Expression($1); }
;

scope_statement: FLB scope FRB      { $$ = $2; }
                 | FLB FRB          { $$ = nullptr; }
;

if: IF_ expr RB FLB scope FRB           { $$ = new If($2, $5);
                                          $$->set_line_num($1); }
    | IF_ expr RB FLB FRB               { $$ = new If($2, nullptr);
                                          $$->set_line_num($1); }
;

while:  WHILE_ expr RB FLB scope FRB    { $$ = new While($2, $5);
                                                   $$->set_line_num($1); }   
        | WHILE_ expr RB FLB FRB        { $$ = new While($2, nullptr);
                                                   $$->set_line_num($1);}                               
;

print:  PRINT_ expr SCOL                     { $$ = new Print($2);
                                               $$->set_line_num($1); }
;


expr:   expr_assign expr_                 { if ($2 != nullptr){ 

                                                $$ = new LogicOperator(std::make_pair(Or, false), $1, $2); 
                                            }else { 

                                                $$ = $1; 
                                            } }
        | error SCOL                        { $$ = nullptr; error_occurred = true; }
        | error RB                          { $$ = nullptr; error_occurred = true; }
;
expr_:  OR expr_assign expr_              { if ($3 != nullptr){ 

                                                $$ = new LogicOperator(std::make_pair(Or, false), $2, $3); 
                                            }else { 
                                                
                                                $$ = $2; 
                                            }  }
        | %empty                          { $$ = nullptr; }
;

expr_assign: expr_and expr_assign_            { if ($2 != nullptr){ 

                                                    $$ = new Assign($1, $2); 
                                                }else { 

                                                    $$ = $1; 
                                                } }
;
expr_assign_:   ASSIGN expr_and expr_assign_  { if ($3 != nullptr){ 

                                                    $$ = new Assign($2, $3); 
                                                }else { 
                                                
                                                    $$ = $2; 
                                                } }
                | %empty                      { $$ = nullptr; }
;

expr_and:   expr_log expr_and_            { if ($2 != nullptr){ 

                                                $$ = new LogicOperator(std::make_pair(And, false), $1, $2); 
                                            }else { 

                                                $$ = $1;  
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
                                            }else { 
                                                
                                                $$ = new Wrapper(*($1.first), $2); 
                                            } }
            | %empty                      { $$ = nullptr; }
;

expr_sum:   expr_sub expr_sum_            { if ($2 != nullptr){ 

                                                $$ = $2->make_math_op($1);
                                                delete $2;
                                            }else { 

                                                $$ = $1; 
                                            } }
;
expr_sum_:  OP_SUM expr_sub expr_sum_     { if ($3 != nullptr){ 

                                                Ioperator* next_op = $3->make_math_op($2);
                                                $$ = new Wrapper(*($1.first), next_op);
                                                delete $3; 
                                            }else { 
                                                
                                                $$ = new Wrapper(*($1.first), $2); 
                                            } }
            | %empty                      { $$ = nullptr; }
;

expr_sub:   expr_mul expr_sub_            { if ($2 != nullptr){ 

                                                $$ = $2->make_math_op($1);
                                                delete $2;
                                            }else { 

                                                $$ = $1; 
                                            } }
;
expr_sub_:  OP_SUB expr_mul expr_sub_     { if ($3 != nullptr){ 

                                                Ioperator* next_op = $3->make_math_op($2);
                                                $$ = new Wrapper(*($1.first), next_op);
                                                delete $3; 
                                            }else { 
                                                
                                                $$ = new Wrapper(*($1.first), $2); 
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
                                            }else { 

                                                $$ = new Wrapper(*($1.first), $2); 
                                            } }
            | %empty                      { $$ = nullptr; }
;


%%

namespace yy{

    parser::token_type yylex(parser::semantic_type* yylval, parser::location_type* loc, ParaDriver* driver){

        if (error_occurred){ driver->set_error(); }
        return driver->yylex(yylval);
    }

    void parser::error(const location_type& loc, const std::string& token){ 
        
        std::cout << token << " [" << cur_line + 1 << ", " << cur_col + 1 << "]" << std::endl;
        std::cout <<  line << std::endl;

        for (int i = 0; i < cur_col; i++){

            std::cout << "\x1b[1;31m~";
        }

        std::cout << "\x1b[1;31m^\x1b[0m" << std::endl;
    }    
}
