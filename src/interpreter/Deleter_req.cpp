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

void Deleter_req::delete_next_statement(Istatement& node){

    node.transfer_req(*this);

    Iresponse* resp = node.transfer_req(standart_addr_req);
    Inode* next = static_cast<Addr_resp*>(resp)->get_addr();
    delete next;
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

    delete_next_statement(node);

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

    delete_next_statement(node);

    return nullptr;
}

Iresponse* Deleter_req::process_req(Assign& node){

    node.transfer_req_lhs(*this);

    Iresponse* resp = node.transfer_req_lhs(standart_addr_req);
    Inode* left = static_cast<Addr_resp*>(resp)->get_addr();
    delete left;

    node.transfer_req_rhs(*this);

    resp = node.transfer_req_rhs(standart_addr_req);
    Inode* right = static_cast<Addr_resp*>(resp)->get_addr();
    delete right;

    delete_next_statement(node);

    return nullptr;
}

Iresponse* Deleter_req::process_req(Print& node){

    node.transfer_req_var(*this);

    Iresponse* resp = node.transfer_req_var(standart_addr_req);
    Inode* var = static_cast<Addr_resp*>(resp)->get_addr();
    delete var;

    delete_next_statement(node);

    return nullptr;
}
