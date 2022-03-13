#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

#define BOOST_TEST_MODULE First_TestSuite
#include <boost/test/included/unit_test.hpp>

#include <FlexLexer.h>
#include "../src/ParaDriver.hpp"

#define MAX_NUM 3
#define MAX_FILE_NAME 20

int yyFlexLexer::yywrap() {
    return 1;
}

BOOST_AUTO_TEST_SUITE(Modules_tests)

BOOST_AUTO_TEST_CASE(Objects_manager){

    int value = 0, num_of_obj = 0, num_of_scopes = 0;
    std::string name;
    std::ifstream input{"../tests/bin/Objects"};
    std::ifstream req{"../tests/bin/Requests"};
    std::ifstream ans{"../tests/bin/Ans"};
    std::ofstream out{"../tests/bin/out"};
    ParaCL::Object_manager manager;
    ParaCL::Object* tmp_obj = nullptr;

    assert(input.is_open());
    assert(req.is_open());
    assert(ans.is_open());
    assert(out.is_open());

    do{
        num_of_obj++;
        input >> name >> value;

        tmp_obj = new ParaCL::VarInt(name, value);
        manager.add_object(tmp_obj);

        if (num_of_obj % 5 == 0){

            manager.add_scope();
            num_of_scopes++;
        }

    } while (!input.eof());

    do{
        req >> name >> value;

        ParaCL::VarInt* cur_var = static_cast<ParaCL::VarInt*>(manager.get_object(name));
        cur_var->set_value(cur_var->get_value() + value);
        
        out << cur_var->get_name() << " " << cur_var->get_value() << std::endl;

    } while (!req.eof());

    for (int i = 0; i < num_of_scopes; i++){

        manager.remove_scope();
    }

    BOOST_REQUIRE_EQUAL(0, 0);
}


BOOST_AUTO_TEST_SUITE_END()

void run_programm(){

    FlexLexer* lexer = new yyFlexLexer;
    yy::ParaDriver driver(lexer);

    driver.parse();
    driver.print();

    if (driver.check_scope()){

        driver.execute();
    }
    
    delete lexer;
}

int test_case(int num){

    char num_line[MAX_NUM];
    sprintf(num_line, "%i", num);

    std::string cur_dir("../tests/e2e_examples/");
    std::string input_name("./input_");
    input_name.append(num_line);
    input_name.append(".txt");

    std::string output_name("out/output_");
    output_name.append(num_line);
    output_name.append(".txt");

    std::ifstream in(input_name);
    assert(in.is_open());
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf());

    std::ofstream out(output_name);
    assert(out.is_open());
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());

    run_programm();

    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    out.close();

    std::string answer_name("answer_");
    answer_name.append(num_line);
    answer_name.append(".txt");

    std::string message("diff ");
    message.append(output_name);
    message.append(" ");
    message.append(answer_name);
    message.append(" > ../out_diff");

    return system(message.c_str());
}

BOOST_AUTO_TEST_SUITE(Vadims_tests)

BOOST_AUTO_TEST_CASE(Input1){

    int ret = chdir("../tests/e2e_examples");

    BOOST_REQUIRE_EQUAL(test_case(1), 0);
}

BOOST_AUTO_TEST_CASE(Input2){

    BOOST_REQUIRE_EQUAL(test_case(2), 0);
}

BOOST_AUTO_TEST_CASE(Input3){

    BOOST_REQUIRE_EQUAL(test_case(3), 0);
}

BOOST_AUTO_TEST_CASE(Input4){

    BOOST_REQUIRE_EQUAL(test_case(4), 0);
}

BOOST_AUTO_TEST_CASE(Input5){

    BOOST_REQUIRE_EQUAL(test_case(5), 0);
}

BOOST_AUTO_TEST_CASE(Input6){

    BOOST_REQUIRE_EQUAL(test_case(6), 0);
}

BOOST_AUTO_TEST_CASE(Input7){

    BOOST_REQUIRE_EQUAL(test_case(7), 0);
}

BOOST_AUTO_TEST_CASE(Input8){

    BOOST_REQUIRE_EQUAL(test_case(8), 0);
}

BOOST_AUTO_TEST_CASE(Input9){

    BOOST_REQUIRE_EQUAL(test_case(9), 0);
}

BOOST_AUTO_TEST_CASE(Input10){

    BOOST_REQUIRE_EQUAL(test_case(10), 0);
}

BOOST_AUTO_TEST_CASE(Input11){

    BOOST_REQUIRE_EQUAL(test_case(11), 0);
}

BOOST_AUTO_TEST_CASE(Input12){

    BOOST_REQUIRE_EQUAL(test_case(12), 0);
}


BOOST_AUTO_TEST_SUITE_END()
