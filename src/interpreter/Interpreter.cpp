#include "interpreter/Interpreter.h"
#include <iostream>
#include <cassert>

using namespace ParaCL;

Iresponse* Var_name_req::process_req(Var& node){

    return new Var_name_resp(node.get_name());
}


Iresponse* Interpreter::process_req(If& node){

    Iresponse* condition_ret = node.transfer_req_condition(*this);

    if (condition_ret == nullptr){

        std::cout << "\x1b[1;31mRuntime error:\x1b[0m no condition in if [" << 
        node.get_line_num() << "]" << std::endl;

        return nullptr;
    }

    int condition_val = static_cast<Value*>(condition_ret)->get_value();
    delete condition_ret;

    if (condition_val){

        node.transfer_req_scope(*this);
    }

    return nullptr;
}

Iresponse* Interpreter::process_req(While& node){

    Iresponse* condition_ret = node.transfer_req_condition(*this);

    if (condition_ret == nullptr){

        std::cout << "\x1b[1;31mRuntime error:\x1b[0m no condition in while [" << 
        node.get_line_num() << "]" << std::endl;

        return nullptr;
    }

    int condition_val = static_cast<Value*>(condition_ret)->get_value();
    delete condition_ret;

    while (condition_val){

        node.transfer_req_scope(*this);

        condition_ret = node.transfer_req_condition(*this);
        condition_val = static_cast<Value*>(condition_ret)->get_value();
        delete condition_ret;
    }

    return nullptr;
}

Iresponse* Interpreter::process_req(Scope& node){

    obj_manager.add_scope();

    for (int i = 0; i < node.get_size(); i++){

        node.transfer_req_to_statement(*this, i);
    }

    obj_manager.remove_scope();

    return nullptr;
}

Iresponse* Interpreter::process_req(Expression& node){

    node.transfer_req_expression(*this);

    return nullptr;
}

Iresponse* Interpreter::process_req(Assign& node){

    Iresponse* lhs_ret = node.transfer_req_left(standart_var_req);
    
    if (lhs_ret == nullptr){

        std::cout << "\x1b[1;31mRuntime error:\x1b[0m expected object [" <<
        node.get_line_num() << "]" << std::endl;

        return nullptr;
    }

    Var_name_resp* tmp = static_cast<Var_name_resp*>(lhs_ret);
    std::string lhs_name = tmp->get_var_name();
    delete lhs_ret;

    VarInt* lhs = static_cast<VarInt*>(obj_manager.get_object(lhs_name));

    if (lhs == nullptr){

        obj_manager.add_object(new VarInt(lhs_name, 0));
        lhs = static_cast<VarInt*>(obj_manager.get_object(lhs_name));
        assert(lhs != nullptr);
    }
    
    Iresponse* rhs_ret = node.transfer_req_right(*this);
    
    if (rhs_ret == nullptr){

        std::cout << "\x1b[1;31mRuntime error:\x1b[0m expected value [" <<
        node.get_line_num() << "]" << std::endl;

        return nullptr;
    }

    int value = static_cast<Value*>(rhs_ret)->get_value();
    
    lhs->set_value(value);

    return rhs_ret;
}

Iresponse* Interpreter::process_req(Print& node){

    Iresponse* rhs_ret = node.transfer_req_var(*this);

    if (rhs_ret == nullptr){

        std::cout << "\x1b[1;31mRuntime error:\x1b[0m expected value [" <<
        node.get_line_num() << "]" << std::endl;

        return nullptr;
    }

    int value = static_cast<Value*>(rhs_ret)->get_value();
    delete rhs_ret;

    std::cout << value << std::endl;

    return nullptr;
}

Iresponse* Interpreter::process_req(Var& node){

    VarInt* var = static_cast<VarInt*>(obj_manager.get_object(node.get_name()));
    
    if (var == nullptr){

        std::cout << "\x1b[1;31mRuntime error:\x1b[0m undefined object " << node.get_name() << "[" <<
        node.get_line_num() << "]" << std::endl;

        return nullptr;
    }

    Iresponse* ret = new Value(var->get_value());

    return ret;
}

Iresponse* Interpreter::process_req(Num& node){

    Iresponse* ret = new Value(node.get_value());

    return ret;
}

Iresponse* Interpreter::process_req(Input& node){

    int input_val = 0;
    std::cin >> input_val;

    Iresponse* ret = new Value(input_val);

    return ret;
}

Iresponse* Interpreter::process_req(LogicOperator& node){

    Iresponse* lhs_ret = node.transfer_req_left(*this);
    assert(lhs_ret != nullptr);
    int lhs = static_cast<Value*>(lhs_ret)->get_value();
    delete lhs_ret;

    Iresponse* rhs_ret = node.transfer_req_right(*this);
    assert(rhs_ret != nullptr);
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
            assert(false);
            break;
    }

    return new_resp;
}

Iresponse* Interpreter::process_req(MathOperator& node){

    Iresponse* lhs_ret = node.transfer_req_left(*this);
    assert(lhs_ret != nullptr);
    int lhs = static_cast<Value*>(lhs_ret)->get_value();
    delete lhs_ret;

    Iresponse* rhs_ret = node.transfer_req_right(*this);
    assert(rhs_ret != nullptr);
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
            assert(false);
            new_resp->set_value(0);
            break;
    }

    return new_resp;
}

