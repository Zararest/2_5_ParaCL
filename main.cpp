#include <iostream>
#include <string>
#include <cstdio>

#include <FlexLexer.h>
#include "./src/ParaDriver.hpp"
 
int yyFlexLexer::yywrap() {
    return 1;
}

int main(int argc, char** argv){

    FlexLexer* lexer = new yyFlexLexer;
    
    if (argc == 1) {

        yy::ParaDriver driver(lexer);
      
        driver.parse();
        driver.print();

        if (driver.check_scope()){

            driver.execute();
        }

        delete lexer;
    }

    else if (argc == 2) {

        std::ifstream in_file(argv[1]); 
        assert(in_file.is_open());
        lexer->switch_streams(in_file, std::cout);

        yy::ParaDriver driver(lexer);
      
        driver.parse();
        driver.print();

        if (driver.check_scope()){

            driver.execute();
        }

        delete lexer;
    }
    
    else if (argc == 3) {

        std::ifstream in_file(argv[1]); 
        lexer->switch_streams(in_file, std::cout);
 
        yy::ParaDriver driver(lexer);

        driver.parse();
        driver.print();

        if (driver.check_scope()){

            driver.execute();
        }

        delete lexer;


        std::ifstream prog_answer{"tmp_answer.txt"};
        std::ifstream true_answer{argv[2]};
        std::ofstream log{"log_str.txt"};


        /*int prog_num, true_num;

        while (!prog_answer.eof()) {
            prog_answer >> prog_num;
            true_answer >> true_num;

            log << prog_num << " and " << true_num << std::endl;

            if (prog_num != true_num) {
                log << "failed" << std::endl;
                return 3;
            }
        }
                log << "success" << std::endl;
        return 0;*/

        /*
        std::vector<int> true_data;
        std::vector<int> prog_data;
        int tmp;

        while(!prog_answer.eof()) {
            prog_answer >> tmp;
            prog_data.push_back(tmp);
        }

        while(!true_answer.eof()) {
            true_answer >> tmp;
            printf("once\n");
            true_data.push_back(tmp);
        }*/
        prog_answer.seekg(0, prog_answer.end);
        std::streamsize prog_size = prog_answer.tellg();
        prog_answer.seekg(0, std::ios::beg);
        
        std::vector<char> prog_data(prog_size, 0);
        prog_answer.read(&prog_data[0], prog_size); 

log << "This prog: " << prog_data.size() << std::endl;
        for (auto i = prog_data.begin(); i != prog_data.end(); ++i)
            log << *i;

        true_answer.seekg(0, std::ios::end);
        std::streamsize true_size = true_answer.tellg();
        true_answer.seekg(0, std::ios::beg);
        
        std::vector<char> true_data(true_size, 0);
        true_answer.read(&true_data[0], true_size); 

log << "\nThis true: " << true_size << std::endl;     
        for (auto i = true_data.begin(); i != true_data.end(); ++i)
            log << *i;

        prog_answer.close();
        true_answer.close();

        if (prog_data == true_data) {
            log << "Test success" << std::endl;
            return 0;
        }  
        log << "Test failed" << std::endl;
        return 1;
    } 

    else {
      std::cout << "Invalid quantity of args" << std::endl;
    }
}
