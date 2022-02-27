#include "./headers/Istatement.h"

Istatement::Istatement(Istatement* next_statement):

    Inode{nullptr},
    next_statement_{next_statement}
{

    if (next_statement != nullptr){

        next_statement->prev_ = this;
    }
}

void Istatement::add_next_statement(Istatement* next_statement){

    if (next_statement != nullptr){

        next_statement->prev_ = this;
    }

    next_statement_ = next_statement;
}

Iresponse& Istatement::transfer_req(Irequest& cur_req){

    if (next_statement_ != nullptr){

        return next_statement_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}


If::If(Ioperator* condition, Istatement* scope):

    Istatement{nullptr},
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

Iresponse& If::transfer_req_condition(Irequest& cur_req){

    if (condition_ != nullptr){

        return condition_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}

Iresponse& If::transfer_req_scope(Irequest& cur_req){

    if (if_scope_ != nullptr){

        return if_scope_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}


While::While(Ioperator* condition, Istatement* scope):

    Istatement{nullptr},
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

Iresponse& While::transfer_req_condition(Irequest& cur_req){

    if (condition_ != nullptr){

        return condition_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}

Iresponse& While::transfer_req_scope(Irequest& cur_req){

    if (while_scope_ != nullptr){

        return while_scope_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}

Assign::Assign(Ioperator* lhs, Ioperator* rhs):

    Istatement{nullptr},
    lhs_{lhs},
    rhs_{rhs}
{}

Iresponse& Assign::transfer_req_lhs(Irequest& cur_req){

    if (lhs_ != nullptr){

        return lhs_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}

Iresponse& Assign::transfer_req_rhs(Irequest& cur_req){

    if (rhs_ != nullptr){

        return rhs_->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}


Print::Print(Ioperator* var):

    Istatement{nullptr},
    out_var{var}
{}

Iresponse& Print::transfer_req_var(Irequest& cur_req){

    if (out_var != nullptr){

        return out_var->get_request(cur_req);
    } else{

        return cur_req.process_terminal();
    }
}