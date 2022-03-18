#include "headers/Deleter_req.h"

using namespace ParaCL;

void Deleter_req::delete_next_operators(Ioperator& node){

    node.transfer_req_left(*this);

    Iresponse* resp = node.transfer_req_left(standart_addr_req);
    Inode* left = static_cast<Addr_resp*>(resp)->get_addr();
    delete left;

    node.transfer_req_right(*this);

    resp = node.transfer_req_right(standart_addr_req);
    Inode* right = static_cast<Addr_resp*>(resp)->get_addr();
    delete right;
}


Iresponse* Deleter_req::process_req(If& node){

    node.transfer_req_condition(*this);

    Iresponse* resp = node.transfer_req_condition(standart_addr_req);
    Inode* condition = static_cast<Addr_resp*>(resp)->get_addr();
    delete condition;

    node.transfer_req_scope(*this);

    resp = node.transfer_req_scope(standart_addr_req);
    Inode* scope = static_cast<Addr_resp*>(resp)->get_addr();
    delete scope;

    return nullptr;
}

Iresponse* Deleter_req::process_req(While& node){

    node.transfer_req_condition(*this);

    Iresponse* resp = node.transfer_req_condition(standart_addr_req);
    Inode* condition = static_cast<Addr_resp*>(resp)->get_addr();
    delete condition;

    node.transfer_req_scope(*this);

    resp = node.transfer_req_scope(standart_addr_req);
    Inode* scope = static_cast<Addr_resp*>(resp)->get_addr();
    delete scope;

    return nullptr;
}

Iresponse* Deleter_req::process_req(Scope& node){

    for (int i = 0; i < node.get_size(); i++){
        
        node.transfer_req_to_statement(*this, i);

        Iresponse* resp = node.transfer_req_to_statement(standart_addr_req, i);
        Inode* statement = static_cast<Addr_resp*>(resp)->get_addr();
        delete statement;
    }

    return nullptr;
}

Iresponse* Deleter_req::process_req(Expression& node){

    node.transfer_req_expression(*this);

    Iresponse* resp = node.transfer_req_expression(standart_addr_req);
    Inode* expr = static_cast<Addr_resp*>(resp)->get_addr();
    delete expr;

    return nullptr;
}

Iresponse* Deleter_req::process_req(Print& node){

    node.transfer_req_var(*this);

    Iresponse* resp = node.transfer_req_var(standart_addr_req);
    Inode* var = static_cast<Addr_resp*>(resp)->get_addr();
    delete var;

    return nullptr;
}
