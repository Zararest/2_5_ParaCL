#pragma once
#include "Inode.h"

class Istatement: public Inode{

protected:

    Istatement* next_statement_ = nullptr;

public:

    Istatement(Istatement* next_statement);

    void add_next_statement(Istatement* next_statement);
    Iresponse& transfer_req(Irequest& cur_req);

    virtual ~Istatement() = 0; 
};

Istatement::~Istatement(){}


class If final: public Istatement{

    Ioperator* condition_ = nullptr;
    Istatement* if_scope_ = nullptr;

public:

    If(Ioperator* condition, Istatement* scope);

    Iresponse& transfer_req_condition(Irequest& cur_req);
    Iresponse& transfer_req_scope(Irequest& cur_req);

    Iresponse& get_request(Irequest& cur_req) override{ return cur_req.process_req(*this); }
};

class While final: public Istatement{

    Ioperator* condition_ = nullptr;
    Istatement* while_scope_ = nullptr;

public:

    While(Ioperator* condition, Istatement* scope);

    Iresponse& transfer_req_condition(Irequest& cur_req);
    Iresponse& transfer_req_scope(Irequest& cur_req);

    Iresponse& get_request(Irequest& cur_req) override{ return cur_req.process_req(*this); }
};

class Assign final: public Istatement{

    Ioperator* lhs_ = nullptr;
    Ioperator* rhs_ = nullptr;

public:

    Assign(Ioperator* lhs, Ioperator* rhs);

    Iresponse& transfer_req_lhs(Irequest& cur_req);
    Iresponse& transfer_req_rhs(Irequest& cur_req);

    Iresponse& get_request(Irequest& cur_req) override{ return cur_req.process_req(*this); }
};

class Print final: public Istatement{

    Ioperator* out_var = nullptr;

public:

    Print(Ioperator* var);

    Iresponse& transfer_req_var(Irequest& cur_req);
    Iresponse& get_request(Irequest& cur_req) override{ return cur_req.process_req(*this); }
};