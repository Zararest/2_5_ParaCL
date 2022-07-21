#pragma once

#include "../build/Paragrammar.tab.hh"
#include <FlexLexer.h>
#include <cstring>
#include "./linter/headers/Print_req.h"
#include "./linter/headers/Check_scope_req.h"
#include "./interpreter/headers/Interpreter.h"
#include "./interpreter/headers/Deleter_req.h"

namespace yy{

enum struct Terminator{ //аналогично терминатором можно сделать \n

    Nothing,
    Semicolon,
    Brace,
    Non_term
};

class ParaDriver final{

    FlexLexer *plex_;
    ParaCL::Inode* root = nullptr;
    std::ostream& out = std::cout;
    std::vector<std::string*> tokens;
    bool error_occurred = false;
    Terminator prev_token_priority = Terminator::Semicolon;

    Terminator get_token_priority(const parser::token_type& token){

        if (token == parser::token::SCOL)
            return Terminator::Semicolon;
            
        if (token == parser::token::FRB)
            return Terminator::Brace;

        return Terminator::Non_term;
    }

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

        for (auto i : tokens){

            delete i;
        }
    }

    ParaDriver& operator =(const ParaDriver&) = delete;
    ParaDriver& operator =(ParaDriver&&) = delete;

    void execute(){

        ParaCL::Interpreter interp;

        if (root != nullptr && !error_occurred){

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

    parser::token_type yylex(parser::semantic_type *yylval) { //не считывает нормально ошибку в первой строке

        parser::token_type token;
        Terminator token_priority;

        do {
            token = static_cast<parser::token_type>(plex_->yylex());
            token_priority = get_token_priority(token);

        } while (token_priority <= prev_token_priority);
        
        if (token_priority == Terminator::Brace)
            prev_token_priority = Terminator::Semicolon;     

        if (token_priority == Terminator::Non_term)
            prev_token_priority = Terminator::Nothing;
        
        if (token_priority == Terminator::Semicolon)
            prev_token_priority = Terminator::Semicolon;

        if (token == parser::token::WORD
            || token == parser::token::LOGIC
            || token == parser::token::OP_MUL
            || token == parser::token::OP_SUM
            || token == parser::token::OP_SUB){

            tokens.push_back(new std::string(plex_->YYText())); 
            yylval->as<std::pair<const std::string*, int>>() = std::make_pair(tokens.back(), plex_->lineno());
        
            return token;
        }

        if (token == parser::token::NUM){

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

    void add_root(ParaCL::Scope* node){

        root = node;
    }

    void set_error(){

        error_occurred = true;
    }
};

}