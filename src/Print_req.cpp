#include "headers/Print_req.h"
#include <iostream>

void Print_req::print_next_statement(Istatement& node){

    Iresponse* resp = node.transfer_req(standart_addr_req);
    Inode* next = static_cast<Addr_resp*>(resp)->get_addr();
    
    if (next != nullptr){

        out_file << "\"" << &node << "\" -> \"" << next << "\"" << std::endl;   //чтобы выдеклить следующий startement
        out_file << "\"" << &node << "\" -> \"" << next << "\"" << std::endl; 

        node.transfer_req(*this);
        //next->get_request(*this);
    }
}

Print_req::Print_req(const char* name): out_file{name}{

    out_file << "digraph Dump{" <<
    "node[color=red,fontsize=14, style=filled]" << std::endl;
}

Print_req::~Print_req(){

    out_file << "}" << std::endl;
    out_file.close();
}

Iresponse* Print_req::process_req(If& node){
    //std::cout << "If" << std::endl;
    out_file << "\"" << &node << "\" [label = \"If\" fillcolor=lightblue]" << std::endl;

    Iresponse* resp = node.transfer_req_condition(standart_addr_req);
    Inode* condition = static_cast<Addr_resp*>(resp)->get_addr();

    if (condition != nullptr){

        out_file << "\"" << &node << "\" -> \"" << condition << "\"" << std::endl;
        
        node.transfer_req_condition(*this);
    }

    resp = node.transfer_req_scope(standart_addr_req);
    Inode* scope = static_cast<Addr_resp*>(resp)->get_addr();

    if (scope != nullptr){

        out_file << "\"" << &node << "\" -> \"" << scope << "\"" << std::endl;
        node.transfer_req_scope(*this);
    }

    print_next_statement(node);

    return nullptr;
}

Iresponse* Print_req::process_req(While& node){
    //std::cout << "While" << std::endl;
    out_file << "\"" << &node << "\" [label = \"While\" fillcolor=red]" << std::endl;

    Iresponse* resp = node.transfer_req_condition(standart_addr_req);
    Inode* condition = static_cast<Addr_resp*>(resp)->get_addr();

    if (condition != nullptr){

        out_file << "\"" << &node << "\" -> \"" << condition << "\"" << std::endl;
        node.transfer_req_condition(*this);
    }

    resp = node.transfer_req_scope(standart_addr_req);
    Inode* scope = static_cast<Addr_resp*>(resp)->get_addr();

    if (scope != nullptr){

        out_file << "\"" << &node << "\" -> \"" << scope << "\"" << std::endl;
        node.transfer_req_scope(*this);
    }   

    print_next_statement(node);

    return nullptr;
}

Iresponse* Print_req::process_req(Assign& node){
    //std::cout << "Assign" << std::endl;
    out_file << "\"" << &node << "\" [label = \"Assign\" fillcolor=green]" << std::endl;

    Iresponse* resp = node.transfer_req_lhs(standart_addr_req);
    Inode* var = static_cast<Addr_resp*>(resp)->get_addr();

    if (var != nullptr){

        out_file << "\"" << &node << "\" -> \"" << var << "\"" << std::endl;
        node.transfer_req_lhs(*this);
    }

    resp = node.transfer_req_rhs(standart_addr_req);
    Inode* rhs = static_cast<Addr_resp*>(resp)->get_addr();

    if (rhs != nullptr){

        out_file << "\"" << &node << "\" -> \"" << rhs << "\"" << std::endl;
        node.transfer_req_rhs(*this);
    }

    print_next_statement(node);

    return nullptr;
}

Iresponse* Print_req::process_req(Print& node){
    //std::cout << "Print" << std::endl;     
    out_file << "\"" << &node << "\" [label = \"Print\" fillcolor=purple]" << std::endl;

    Iresponse* resp = node.transfer_req_var(standart_addr_req);
    Inode* var = static_cast<Addr_resp*>(resp)->get_addr();

    if (var != nullptr){

        out_file << "\"" << &node << "\" -> \"" << var << "\"" << std::endl;
        node.transfer_req_var(*this);
    }

    return nullptr;
}

Iresponse* Print_req::process_req(Var& node){
    //std::cout << "Var" << std::endl;
    out_file << "\"" << &node << "\" [label = \"Var:" << node.get_name() << "\" fillcolor=yellow]" << std::endl;

    return nullptr;
}

Iresponse* Print_req::process_req(Num& node){
    //std::cout << "Num" << std::endl;
    out_file << "\"" << &node << "\" [label = \"Num:" << node.get_value() << "\" fillcolor=yellow]" << std::endl;

    return nullptr;
}

Iresponse* Print_req::process_req(Input& node){
    //std::cout << "Input" << std::endl;
    out_file << "\"" << &node << "\" [label = \"Input\" fillcolor=crimson]" << std::endl;

    return nullptr;
}

Iresponse* Print_req::process_req(LogicOperator& node){
    //std::cout << "LogicOperator" << std::endl;
    out_file << "\"" << &node << "\" [label = \"" << get_log_op(node.get_operator()) << "\" fillcolor=cyan]" << std::endl;

    Iresponse* resp = node.transfer_req_left(standart_addr_req);
    Inode* lhs = static_cast<Addr_resp*>(resp)->get_addr();

    if (lhs != nullptr){

        out_file << "\"" << &node << "\" -> \"" << lhs << "\"" << std::endl;
        node.transfer_req_left(*this);
    }

    resp = node.transfer_req_right(standart_addr_req);
    Inode* rhs = static_cast<Addr_resp*>(resp)->get_addr();

    if (rhs != nullptr){

        out_file << "\"" << &node << "\" -> \"" << rhs << "\"" << std::endl;
        node.transfer_req_right(*this);
    }

    return nullptr;
}

Iresponse* Print_req::process_req(MathOperator& node){
    std::cout << "MathOperator: " << node.get_operator() << std::endl;
    out_file << "\"" << &node << "\" [label = \"" << get_math_op(node.get_operator()) << "\" fillcolor=coral]" << std::endl;

    Iresponse* resp = node.transfer_req_left(standart_addr_req);
    Inode* lhs = static_cast<Addr_resp*>(resp)->get_addr();

    if (lhs != nullptr){

        out_file << "\"" << &node << "\" -> \"" << lhs << "\"" << std::endl;
        node.transfer_req_left(*this);
    }

    resp = node.transfer_req_right(standart_addr_req);
    Inode* rhs = static_cast<Addr_resp*>(resp)->get_addr();

    if (rhs != nullptr){

        out_file << "\"" << &node << "\" -> \"" << rhs << "\"" << std::endl;
        node.transfer_req_right(*this);
    }

    return nullptr;
}
