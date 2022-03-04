#include <iostream>

#include <FlexLexer.h>
#include "headers/ParaDriver.hpp"
 
int yyFlexLexer::yywrap() {
  return 1;
}

////////       THIS DON'T USE

int main(){
  std::cout << "We start" << std::endl;

  FlexLexer* lexer = new yyFlexLexer;
  yy::ParaDriver driver(lexer);
  driver.parse();
  driver.print();
  std::cout << "We print" << std::endl;
  driver.check_scope();

  delete lexer;
}