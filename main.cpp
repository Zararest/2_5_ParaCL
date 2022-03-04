#include <iostream>

#include <FlexLexer.h>
#include "./src/headers/ParaDriver.hpp"
 
int yyFlexLexer::yywrap() {
  return 1;
}

int main(){

  FlexLexer* lexer = new yyFlexLexer;
  yy::ParaDriver driver(lexer);
  driver.parse();

  driver.print();

  delete lexer;
}