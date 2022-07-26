#include "./headers/Irequest.h"
#include <iostream>

using namespace ParaCL;

Istatement::Istatement(TokenHandle handle):

    Inode{nullptr, handle}
{}

Scope::Scope(): 

    Istatement{TokenHandle{}}
{}

void Scope::add_statement(Istatement* new_statement){

    statements_.push_back(new_statement);
}

int Scope::get_size(){

    return statements_.size();
}

void Scope::reverse_statements(){

    int size = statements_.size();

    for (int i = 0; i < size / 2 - 1; i++){

        std::swap(statements_[i], statements_[size - 1 - i]); 
    }
}

Iresponse* Scope::transfer_req_to_statement(Irequest& cur_req, int num_of_statement){

    if (num_of_statement < statements_.size() 
        && num_of_statement >= 0 
        && statements_[num_of_statement] != nullptr){
        
        return statements_[num_of_statement]->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}

Iresponse* Scope::get_request(Irequest& cur_req){

    return cur_req.process_req(*this); 
}


Expression::Expression(Ioperator* expr, TokenHandle handle): 

    Istatement{handle},
    expression_{expr}
{}

Iresponse* Expression::transfer_req_expression(Irequest& cur_req){

    if (expression_ != nullptr){
        
        return expression_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}

Iresponse* Expression::get_request(Irequest& cur_req){

    return cur_req.process_req(*this); 
}


If::If(Ioperator* condition, Scope* scope, TokenHandle handle):
    
    Istatement{handle},
    condition_{condition},
    if_scope_{scope}
{
    if (condition != nullptr){
        
        condition->add_prev(this);
    }

    if (scope != nullptr){

        scope->add_prev(this);
    }
}

Iresponse* If::transfer_req_condition(Irequest& cur_req){

    if (condition_ != nullptr){
        
        return condition_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}

Iresponse* If::transfer_req_scope(Irequest& cur_req){

    if (if_scope_ != nullptr){

        return if_scope_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}

Iresponse* If::get_request(Irequest& cur_req){

    return cur_req.process_req(*this); 
}


While::While(Ioperator* condition, Scope* scope, TokenHandle handle):

    Istatement{handle},
    condition_{condition},
    while_scope_{scope}
{
    if (condition != nullptr){
        
        condition->add_prev(this);
    }

    if (scope != nullptr){

        scope->add_prev(this);
    }
}

Iresponse* While::transfer_req_condition(Irequest& cur_req){

    if (condition_ != nullptr){

        return condition_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}

Iresponse* While::transfer_req_scope(Irequest& cur_req){

    if (while_scope_ != nullptr){

        return while_scope_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}

Iresponse* While::get_request(Irequest& cur_req){

    return cur_req.process_req(*this); 
}


Print::Print(Ioperator* var, TokenHandle handle):

    Istatement{handle},
    out_var{var}
{}

Iresponse* Print::transfer_req_var(Irequest& cur_req){

    if (out_var != nullptr){

        return out_var->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}

Iresponse* Print::get_request(Irequest& cur_req){

    return cur_req.process_req(*this); 
}