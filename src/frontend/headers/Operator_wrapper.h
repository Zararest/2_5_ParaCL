#pragma once 
#include "Ioperator.h"

namespace ParaCL{

class Wrapper{

    TokenHandle op_handle_;
    Ioperator* rhs_node = nullptr;

public:

    Wrapper(TokenHandle op_handle, Ioperator* node): 
        
        op_handle_{op_handle}, 
        rhs_node{node}
    {}

    Ioperator* make_math_op(Ioperator* lhs){

        return new MathOperator(lhs, rhs_node, op_handle_);
    }

    Ioperator* make_log_op(Ioperator* lhs){

        return new LogicOperator(lhs, rhs_node, op_handle_);
    }

    Ioperator* make_assign(Ioperator* lhs){

        return new Assign(lhs, rhs_node, op_handle_);
    }
};
}