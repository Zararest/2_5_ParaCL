#include "headers/Check_scope_req.h"
#include <iostream>
#include <cassert>

using namespace ParaCL;

void Undefined_objects_resp::add_object(const std::string& name, int line){

    for (auto it : arr_of_obj){

        if (it.first == name){

            return;
        }
    }    

    arr_of_obj.push_back(std::make_pair(name, line));   
}

std::pair<std::string, int> Undefined_objects_resp::get_object(){

    return arr_of_obj.back();
}

void Undefined_objects_resp::pop_back(){

    arr_of_obj.pop_back();
}

int Undefined_objects_resp::get_num_of_objects(){

    return arr_of_obj.size();
}

void Undefined_objects_resp::add_objects_from_resp(Undefined_objects_resp& other_resp){

    for (auto it : other_resp.arr_of_obj){

        arr_of_obj.push_back(it);
    }
}


void Check_scope_req::print_undef_objects(Undefined_objects_resp& undef_objects){

    int size = undef_objects.get_num_of_objects();
    
    for (int i = 0; i < size; i++){

        auto obj = undef_objects.get_object();
        std::cout << "identifier \"" << obj.first << "\" is undefined [" << 
        obj.second << "]" << std::endl;

        undef_objects.pop_back();
        error_occurred = true;
    }
}

void Check_scope_req::define_undef_objects(Undefined_objects_resp& undef_objects){

    assert(undef_objects.get_num_of_objects() == 1);

    auto obj = undef_objects.get_object();
    manager.add_object(new Object(obj.first));

    undef_objects.pop_back();
}

Iresponse* Check_scope_req::process_req(If& node){

    Iresponse* condition_resp = node.transfer_req_condition(*this);

    if (condition_resp != nullptr) {
        
        print_undef_objects(*static_cast<Undefined_objects_resp*>(condition_resp));
    }

    delete condition_resp;

    node.transfer_req_scope(*this);

    return nullptr;
}

Iresponse* Check_scope_req::process_req(While& node){
    
    Iresponse* condition_resp = node.transfer_req_condition(*this);

    if (condition_resp != nullptr) {
        
        print_undef_objects(*static_cast<Undefined_objects_resp*>(condition_resp));
    }

    delete condition_resp;

    node.transfer_req_scope(*this);

    return nullptr;
}

Iresponse* Check_scope_req::process_req(Scope& node){

    manager.add_scope();

    for (int i = 0; i < node.get_size(); i++){

        node.transfer_req_to_statement(*this, i);
    }

    manager.remove_scope();

    return nullptr;
}

Iresponse* Check_scope_req::process_req(Expression& node){

    Iresponse* expression_resp = node.transfer_req_expression(*this);

    if (expression_resp != nullptr) {
        
        print_undef_objects(*static_cast<Undefined_objects_resp*>(expression_resp));
    }

    delete expression_resp;

    return nullptr;
}

Iresponse* Check_scope_req::process_req(Print& node){
    
    Iresponse* expression_resp = node.transfer_req_var(*this);

    if (expression_resp != nullptr) {
        
        print_undef_objects(*static_cast<Undefined_objects_resp*>(expression_resp));
    }

    delete expression_resp;

    return nullptr;
}

Iresponse* Check_scope_req::process_req(Var& node) {

    Object* manager_ret = manager.get_object(node.get_name());

    if (manager_ret == nullptr){

        Undefined_objects_resp* ret = new Undefined_objects_resp;
        ret->add_object(node.get_name(), node.get_line_num());

        return ret;
    }

    return nullptr;
}

Iresponse* Check_scope_req::process_req(LogicOperator& node) {
 
    Iresponse* lhs_resp = node.transfer_req_left(*this);
    Undefined_objects_resp* ret = nullptr;

    if (lhs_resp != nullptr){

        ret = static_cast<Undefined_objects_resp*>(lhs_resp);
    }

    Iresponse* rhs_resp = node.transfer_req_right(*this);

    if (rhs_resp != nullptr){

        if (lhs_resp != nullptr){

            ret->add_objects_from_resp(*static_cast<Undefined_objects_resp*>(rhs_resp));
            delete rhs_resp;
        } else{

            ret = static_cast<Undefined_objects_resp*>(rhs_resp);
        }
    }

    return ret;
}

Iresponse* Check_scope_req::process_req(MathOperator& node) {
    
    Undefined_objects_resp* ret = nullptr;
    Iresponse* lhs_resp = node.transfer_req_left(*this);

    if (lhs_resp != nullptr){

        ret = static_cast<Undefined_objects_resp*>(lhs_resp);
    }

    Iresponse* rhs_resp = node.transfer_req_right(*this);

    if (rhs_resp != nullptr){

        if (lhs_resp != nullptr){

            ret->add_objects_from_resp(*static_cast<Undefined_objects_resp*>(rhs_resp));
            delete rhs_resp;
        } else{

            ret = static_cast<Undefined_objects_resp*>(rhs_resp);
        }
    }

    return ret;
}

Iresponse* Check_scope_req::process_req(Assign& node){

    Iresponse* lhs_resp = node.transfer_req_left(*this);

    if (lhs_resp != nullptr){

        define_undef_objects(*static_cast<Undefined_objects_resp*>(lhs_resp));
    }

    return node.transfer_req_right(*this);
}
