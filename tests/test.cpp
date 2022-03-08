#include "../src/headers/Interpreter.h"
#include <iostream>
#include <fstream>
#include <cassert>

#define BOOST_TEST_MODULE First_TestSuite
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Modules_tests)

BOOST_AUTO_TEST_CASE(Objects_manager){

    int value = 0, num_of_obj = 0, num_of_scopes = 0;
    std::string name;
    std::ifstream input{"../tests/bin/Objects"};
    std::ifstream req{"../tests/bin/Requests"};
    std::ifstream ans{"../tests/bin/Ans"};
    std::ofstream out{"../tests/bin/out"};
    Object_manager manager;
    Object* tmp_obj = nullptr;

    assert(input.is_open());
    assert(req.is_open());
    assert(ans.is_open());
    assert(out.is_open());

    do{
        num_of_obj++;
        input >> name >> value;

        tmp_obj = new VarInt(name, value);
        manager.add_object(tmp_obj);

        if (num_of_obj % 5 == 0){

            manager.add_scope();
            num_of_scopes++;
        }

    } while (!input.eof());

    do{
        req >> name >> value;

        VarInt* cur_var = static_cast<VarInt*>(manager.get_object(name));
        cur_var->set_value(cur_var->get_value() + value);
        
        out << cur_var->get_name() << " " << cur_var->get_value() << std::endl;

    } while (!req.eof());

    for (int i = 0; i < num_of_scopes; i++){

        manager.remove_scope();
    }

    BOOST_REQUIRE_EQUAL(0, 0);
}


BOOST_AUTO_TEST_SUITE_END()
