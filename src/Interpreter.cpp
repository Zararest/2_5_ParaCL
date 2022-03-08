#include "headers/Interpreter.h"
#include <iostream>
#include <cassert>

Iresponse* Var_name_req::process_req(Var& node){

    return new Var_name_resp(node.get_name());
}

Iresponse* Interpreter::process_req(If& node){

    Iresponse* condition_ret = node.transfer_req_condition(*this);
    int condition_val = static_cast<Value*>(condition_ret)->get_value();
    delete condition_ret;

    if (condition_val){

        node.transfer_req_scope(*this);
    }

    node.transfer_req(*this);

    return nullptr;
}

Iresponse* Interpreter::process_req(While& node){

    Iresponse* condition_ret = node.transfer_req_condition(*this);
    int condition_val = static_cast<Value*>(condition_ret)->get_value();
    delete condition_ret;

    while (condition_val){

        node.transfer_req_scope(*this);

        condition_val = static_cast<Value*>(condition_ret)->get_value();
        delete condition_ret;
    }

    node.transfer_req(*this);

    return nullptr;
}

Iresponse* Interpreter::process_req(Assign& node){

    Iresponse* lhs_ret = node.transfer_req_lhs(standart_var_req);
    assert(lhs_ret != nullptr);
    Var_name_resp* tmp = static_cast<Var_name_resp*>(lhs_ret);
    const std::string& lhs_name = tmp->get_var_name();
    delete lhs_ret;

    VarInt* lhs = static_cast<VarInt*>(obj_manager.get_object(lhs_name));

    if (lhs == nullptr){

        obj_manager.add_object(new VarInt(lhs_name, 0));
        lhs = static_cast<VarInt*>(obj_manager.get_object(lhs_name));
    }

    Iresponse* rhs_ret = node.transfer_req_rhs(*this);
    int value = 0;

    if (rhs_ret == nullptr){

        std::cin >> value;
    } else{

        value = static_cast<Value*>(rhs_ret)->get_value();
    }
    delete rhs_ret;

    lhs->set_value(value);

    node.transfer_req(*this);

    return nullptr;
}

Iresponse* Interpreter::process_req(Print& node){

    Iresponse* var_ret = node.transfer_req_var(standart_var_req);
    assert(var_ret != nullptr);
    const std::string& var_name = static_cast<Var_name_resp*>(var_ret)->get_var_name();
    delete var_ret;

    VarInt* lhs = static_cast<VarInt*>(obj_manager.get_object(var_name));

    std::cout << lhs->get_value();

    node.transfer_req(*this);

    return nullptr;
}

Iresponse* Interpreter::process_req(Var& node){

    VarInt* var = static_cast<VarInt*>(obj_manager.get_object(node.get_name()));
    assert(var != nullptr);
    Iresponse* ret = new Value(var->get_value());

    return ret;
}

Iresponse* Interpreter::process_req(Num& node){

    Iresponse* ret = new Value(node.get_value());

    return ret;
}

Iresponse* Interpreter::process_req(Input& node){

    return nullptr;
}

Iresponse* Interpreter::process_req(LogicOperator& node){

    Iresponse* lhs_ret = node.transfer_req_left(*this);
    int lhs = static_cast<Value*>(lhs_ret)->get_value();
    delete lhs_ret;

    Iresponse* rhs_ret = node.transfer_req_right(*this);
    int rhs = static_cast<Value*>(rhs_ret)->get_value();

    Value* new_resp = static_cast<Value*>(rhs_ret);
    std::pair<int, bool> op = node.get_operator();

    switch (op.first){
        
        case Equal:
            if (op.second){ 
                new_resp->set_value(lhs == rhs);
            }else{ 
                new_resp->set_value(lhs != rhs);
            }
            break;
        
        case Less:
            if (op.second){ 
                new_resp->set_value(lhs <= rhs);
            }else{ 
                new_resp->set_value(lhs < rhs);
            }
            break;
        
        case Greater:
            if (op.second){ 
                new_resp->set_value(lhs >= rhs);
            }else{ 
                new_resp->set_value(lhs > rhs);
            }
            break;

        case Or:
            new_resp->set_value(lhs || rhs);
            break;

        case And:
            new_resp->set_value(lhs && rhs);
            break;

        case Nothing_log:
            new_resp->set_value(0);
            break;
    }

    return new_resp;
}

Iresponse* Interpreter::process_req(MathOperator& node){

    Iresponse* lhs_ret = node.transfer_req_left(*this);
    int lhs = static_cast<Value*>(lhs_ret)->get_value();
    delete lhs_ret;

    Iresponse* rhs_ret = node.transfer_req_right(*this);
    int rhs = static_cast<Value*>(rhs_ret)->get_value();

    Value* new_resp = static_cast<Value*>(rhs_ret);
    int op = node.get_operator();

    switch (op){

        case Plus:
            new_resp->set_value(lhs + rhs);
            break;
        
        case Minus:
            new_resp->set_value(lhs - rhs);
            break;

        case Mult: 
            new_resp->set_value(lhs * rhs);
            break;
        
        case Div:
            new_resp->set_value(lhs / rhs);
            break;

        case Nothing_math:
            new_resp->set_value(0);
            break;
    }

    return new_resp;
}

