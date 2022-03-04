#pragma once
#include "Irequest.h"
#include <fstream>

class Addr_resp: public Iresponse{

    Inode* node_addr = nullptr; 

public:
     
    void set_addr(Inode* node){ node_addr = node; }
    Inode* get_addr(){ return node_addr; }
};


class Addr_req: public Irequest{

    Addr_resp standart_resp;

    Iresponse* action_(Inode* node_ptr){ 

        standart_resp.set_addr(node_ptr);
        return &standart_resp;
    }

public: 

    Iresponse* process_terminal(){ return action_(nullptr); }

    Iresponse* process_req(If& node){ return action_(&node); }
    Iresponse* process_req(While& node){ return action_(&node); }
    Iresponse* process_req(Assign& node){ return action_(&node); }
    Iresponse* process_req(Print& node){ return action_(&node); }

    Iresponse* process_req(Var& node){ return action_(&node); }
    Iresponse* process_req(Num& node){ return action_(&node); }
    Iresponse* process_req(Input& node){ return action_(&node); }
    Iresponse* process_req(LogicOperator& node){ return action_(&node); }
    Iresponse* process_req(MathOperator& node){ return action_(&node); }
};


class Print_req: public Irequest{

    std::ofstream out_file;
    Addr_req standart_addr_req;

    void print_next_statement(Istatement& node);

public: 

    Print_req(const char* name);  
    ~Print_req();

    Iresponse* process_req(If& node);
    Iresponse* process_req(While& node);
    Iresponse* process_req(Assign& node);
    Iresponse* process_req(Print& node);

    Iresponse* process_req(Var& node);
    Iresponse* process_req(Num& node);
    Iresponse* process_req(Input& node);
    Iresponse* process_req(LogicOperator& node);
    Iresponse* process_req(MathOperator& node);
};
