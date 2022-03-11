#pragma once
#include "../../frontend/headers/Irequest.h"
#include "Objects_manager.h"
#include "Object_types.h"
#include "Var_name_req.h"

namespace ParaCL{

class Value final: public Iresponse{

    int value_ = 0;

public: 

    Value(int value): value_{value}{}
    void set_value(int value){ value_ = value; }
    int get_value(){ return value_; }
};

class Interpreter final: public Irequest{

    Object_manager obj_manager;
    Var_name_req standart_var_req;

public:

    Iresponse* process_req(If& node);
    Iresponse* process_req(While& node);
    Iresponse* process_req(Assign& node);
    Iresponse* process_req(Print& node);

    Iresponse* process_req(Var& node);
    Iresponse* process_req(Num& node);
    Iresponse* process_req(Input& node);
    Iresponse* process_req(LogicOperator& node);
    Iresponse* process_req(MathOperator& node);
};
}