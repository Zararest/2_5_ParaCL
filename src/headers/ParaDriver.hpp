#pragma once

#include "Paragrammar.tab.hh"
#include <FlexLexer.h>
#include <cstring>
#include "Print_req.h"

namespace yy {

class ParaDriver {
  FlexLexer *plex_;
  Inode* root = nullptr;

public:
  ParaDriver(FlexLexer *plex) : plex_(plex) {}

  parser::token_type yylex(parser::semantic_type *yylval) {
    parser::token_type token = static_cast<parser::token_type>(plex_->yylex());

    if (token == yy::parser::token::VAR){

      yylval->as<Var*>() = new Var(std::string(plex_->YYText()));
    }

    if (token == yy::parser::token::NUM){

      yylval->as<Num*>() = new Num(atoi(plex_->YYText()));
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
};

}