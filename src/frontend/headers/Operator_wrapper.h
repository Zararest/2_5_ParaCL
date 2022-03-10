#pragma once 
#include "Ioperator.h"

class Wrapper{

    int type_ = 0;
    bool equal_ = false;

    Ioperator* node_ = nullptr;

public:

    Wrapper(std::string& op, Ioperator* node): node_{node}{

        if (define_math_op(op) != Nothing_math){

            type_ = define_math_op(op);
        } else{

            std::pair<int, bool> tmp = define_log_op(op);

            type_ = tmp.first;
            equal_ = tmp.second;
        }
    }

    void set_params(int type, bool equal, Ioperator* node){

        type_ = type;
        equal_ = equal;
        node_ = node;
    }

    Ioperator* make_math_op(Ioperator* lhs){

        return new MathOperator(type_, lhs, node_);
    }

    Ioperator* make_log_op(Ioperator* lhs){

        return new LogicOperator(std::make_pair(type_, equal_), lhs, node_);
    }
};