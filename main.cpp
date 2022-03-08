#include <iostream>

#include <FlexLexer.h>
#include "./src/headers/ParaDriver.hpp"
 
int yyFlexLexer::yywrap() {
    return 1;
}

int main(int argc, char** argv){

    FlexLexer* lexer = new yyFlexLexer;
    
    if (argc == 1) {

        yy::ParaDriver driver(lexer);
      
        driver.parse();
        driver.print();
        driver.check_scope();
        driver.execute();
        driver.delete_tree();

        delete lexer;
    }

    else if (argc == 2) { 

        std::ifstream in_file(argv[1]); 
        lexer->switch_streams(in_file, std::cout);

        yy::ParaDriver driver(lexer);
      
        driver.parse();
        driver.print();
        driver.check_scope();
        driver.execute();
        driver.delete_tree();

        delete lexer;
    }
    
    else if (argc == 3) {

        std::ifstream in_file(argv[1]); 
        lexer->switch_streams(in_file, std::cout);

        std::ofstream out_file(argv[2]); 
        yy::ParaDriver driver(lexer, out_file);

        driver.parse();
        driver.print();
        driver.check_scope();
        driver.execute();
        driver.delete_tree();

        delete lexer;
    } 

    else {
      std::cout << "Invalid quantity of args" << std::endl;
    }
}
