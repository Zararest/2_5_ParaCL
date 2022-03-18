#pragma once
#include "Inode.h"
#include "Ioperator.h"
#include <vector>

namespace ParaCL{

struct Istatement: public Inode{

    Istatement();
};


class Scope final: public Istatement{

    std::vector<Istatement*> statements_;

public:

    void add_statement(Istatement* new_statement);
    int get_size();
    void reverse_statements();

    Iresponse* transfer_req_to_statement(Irequest& cur_req, int num_of_statement);

    Iresponse* get_request(Irequest& cur_req) override;
};


class Expression final: public Istatement{

    Ioperator* expression_;

public:

    Expression(Ioperator* expr);

    Iresponse* transfer_req_expression(Irequest& cur_req);

    Iresponse* get_request(Irequest& cur_req) override;
};

class If final: public Istatement{

    Ioperator* condition_ = nullptr;
    Scope* if_scope_ = nullptr;

public:

    If(Ioperator* condition, Scope* scope);

    Iresponse* transfer_req_condition(Irequest& cur_req);
    Iresponse* transfer_req_scope(Irequest& cur_req);

    Iresponse* get_request(Irequest& cur_req) override;
};

class While final: public Istatement{

    Ioperator* condition_ = nullptr;
    Scope* while_scope_ = nullptr;

public:

    While(Ioperator* condition, Scope* scope);

    Iresponse* transfer_req_condition(Irequest& cur_req);
    Iresponse* transfer_req_scope(Irequest& cur_req);

    Iresponse* get_request(Irequest& cur_req) override;
};

class Print final: public Istatement{

    Ioperator* out_var = nullptr;

public:

    Print(Ioperator* var);

    Iresponse* transfer_req_var(Irequest& cur_req);
    
    Iresponse* get_request(Irequest& cur_req) override;
};
}