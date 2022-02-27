#include "./headers/Ioperator.h"
#include <utility>

Ioperator::Ioperator(Ioperator* left, Ioperator* right):   
    
    Inode{nullptr},
    left_{left},
    right_{right}
{

    if (left != nullptr){

        left->prev_ = this;
    }

    if (right != nullptr){

        right->prev_ = this;
    }
}

Iresponse& Ioperator::transfer_req_left(Irequest& cur_req){

    if (left_ != nullptr){

        return left_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}

Iresponse& Ioperator::transfer_req_right(Irequest& cur_req){

    if (right_ != nullptr){

        return right_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}


Var::Var(const std::string& name):

    Ioperator{nullptr, nullptr},
    name_{name}
{}

std::string Var::get_name(){

    std::string tmp{name_};
    return tmp;
}

void Var::set_name(std::string& name){

    std::string tmp{name};
    std::swap(name_, tmp);
}


Num::Num(int value):
    
    Ioperator{nullptr, nullptr},
    value_{value}   
{}


Input::Input():

    Ioperator{nullptr, nullptr}
{}


LogicOperator::LogicOperator(int type, bool equal, Ioperator* left, Ioperator* right):

    Ioperator{left, right},
    type_{type},
    equal_{equal}
{}

void LogicOperator::set_operator(std::pair<int, bool> op){

    type_ = op.first;
    equal_ = op.second;
}


MathOperator::MathOperator(int type, Ioperator* left, Ioperator* right):

    Ioperator{left, right},
    type_{type}
{}