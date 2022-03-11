#pragma once

#include "../build/Paragrammar.tab.hh"
#include <FlexLexer.h>
#include <cstring>
#include "./linter/headers/Print_req.h"
#include "./linter/headers/Check_scope_req.h"
#include "./interpreter/headers/Interpreter.h"
#include "./interpreter/headers/Deleter_req.h"

namespace yy{

class ParaDriver final{

    FlexLexer *plex_;
    ParaCL::Inode* root = nullptr;
    std::ostream& out = std::cout;
    std::vector<std::string> tokens;

public:

    ParaDriver(FlexLexer *plex) : plex_(plex) {}
    ParaDriver(FlexLexer *plex, std::ofstream& out_file) : plex_(plex), out(out_file) {}
    ParaDriver(const ParaDriver&) = delete;
    ParaDriver(ParaDriver&&) = delete;
    ~ParaDriver(){

        ParaCL::Deleter_req deleter;
        if (root != nullptr){

            root->get_request(deleter);
            delete root;
        }
    }

    ParaDriver& operator =(const ParaDriver&) = delete;
    ParaDriver& operator =(ParaDriver&&) = delete;

    void execute(){

        ParaCL::Interpreter interp;

        if (root != nullptr){

            root->get_request(interp);
        }
    }

    bool check_scope() {

        ParaCL::Check_scope_req check_scope_tree;

        if (root != nullptr){

            root->get_request(check_scope_tree);
        }

        return check_scope_tree.is_success();
    }

    void print(){
            
        ParaCL::Print_req print_tree{"../bin/graph.dot"};

        if (root != nullptr){

            root->get_request(print_tree);
        }
    }

    parser::token_type yylex(parser::semantic_type *yylval) {

        parser::token_type token = static_cast<parser::token_type>(plex_->yylex());
        
        if (token == yy::parser::token::VAR 
            || token == yy::parser::token::LOGIC
            || token == yy::parser::token::OP_MUL
            || token == yy::parser::token::OP_SUM){

            tokens.push_back(plex_->YYText());    
            yylval->as<std::pair<std::string*, int>>() = std::make_pair(&tokens.back(), plex_->lineno());

            return token;
        }

        if (token == yy::parser::token::NUM){

            yylval->as<std::pair<int, int>>() = std::make_pair(atoi(plex_->YYText()), plex_->lineno());

            return token;
        }
        
        yylval->as<int>() = plex_->lineno();

        return token;
    }

    bool parse() {

        parser parser{this};
        bool res = parser.parse();
        return !res;
    }

    void add_root(ParaCL::Inode* node){

        root = node;
    }
};

}