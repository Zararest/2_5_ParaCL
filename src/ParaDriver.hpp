#pragma once

#include "../build/Paragrammar.tab.hh"
#include <FlexLexer.h>
#include <cstring>
#include "./linter/headers/Print_req.h"
#include "./linter/headers/Check_scope_req.h"
#include "./interpreter/headers/Interpreter.h"
#include "./interpreter/headers/Deleter_req.h"

namespace yy{

class ParaDriver{

    FlexLexer *plex_;
    Inode* root = nullptr;
    std::ostream& out = std::cout;

public:

    ParaDriver(FlexLexer *plex) : plex_(plex) {}
    ParaDriver(FlexLexer *plex, std::ofstream& out_file) : plex_(plex), out(out_file) {}

    parser::token_type yylex(parser::semantic_type *yylval) {

        parser::token_type token = static_cast<parser::token_type>(plex_->yylex());

        if (token == yy::parser::token::VAR 
            || token == yy::parser::token::LOGIC
            || token == yy::parser::token::OP_MUL
            || token == yy::parser::token::OP_SUM){
        
            yylval->as<std::string*>() = new std::string(plex_->YYText());
        }

        if (token == yy::parser::token::NUM){

            yylval->as<int>() = atoi(plex_->YYText());
        }
        
        return token;
    }

    bool parse() {

        parser parser{this};
        bool res = parser.parse();
        return !res;
    }

    void add_root(Inode* node){

        root = node;
    }

    void print(){
        
        Print_req print_tree{"../bin/graph.dot"};

        root->get_request(print_tree);
    }

    void check_scope() {

        Check_scope_req check_scope_tree; // Why there {}? why this and () not the same object [v]
    std::cout << "Start check request" << std::endl;
        root->get_request(check_scope_tree);
    }

    void execute(){

        Interpreter interp;

        root->get_request(interp);
    }

    void delete_tree(){

        Deleter_req deleter;
        
        root->get_request(deleter);
        delete root;
    }
};
}