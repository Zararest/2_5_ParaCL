/**
 * @file Check_scope_req.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022
 * Проверка на то определены переменные или нет
 */
#pragma once
#include "../../frontend/headers/Irequest.h"
#include "../../interpreter/headers/Objects_manager.h"
#include <fstream>
#include <vector>
#include <unordered_set>

namespace ParaCL{

class Undefined_objects_resp: public Iresponse{

    std::vector<std::pair<std::string, int>> arr_of_obj;

public:

    void add_object(const std::string& name, int line);
    void add_objects_from_resp(Undefined_objects_resp& other_resp);
    std::pair<std::string, int> get_object();
    void pop_back();
    int get_num_of_objects();
};

class Check_scope_req : public Irequest {

	Object_manager manager;
    bool error_occurred = false;

    void print_undef_objects(Undefined_objects_resp& undef_objects);
    void define_undef_objects(Undefined_objects_resp& undef_objects);

public: 

    bool is_success(){ return !error_occurred; }

    Iresponse* process_req(If& node);
    Iresponse* process_req(While& node);
    Iresponse* process_req(Scope& node);
    Iresponse* process_req(Expression& node);
    Iresponse* process_req(Print& node);

    Iresponse* process_req(Var& node);
    Iresponse* process_req(LogicOperator& node);
    Iresponse* process_req(MathOperator& node);
    Iresponse* process_req(Assign& node);
};
}
