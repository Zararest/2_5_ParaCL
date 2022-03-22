/**
 * @file Print_req.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022
 * Распечатка дерева в graphviz.
 */
#pragma once
#include "Nodes_addr_req.h"
#include <fstream>

namespace ParaCL{

class Print_req: public Irequest{

    std::ofstream out_file;
    Addr_req standart_addr_req;

    void print_next_statement(Istatement& node);

public: 

    Print_req(const char* name);  
    ~Print_req();

    Iresponse* process_req(If& node);
    Iresponse* process_req(While& node);
    Iresponse* process_req(Scope& node);
    Iresponse* process_req(Expression& node);
    Iresponse* process_req(Print& node);

    Iresponse* process_req(Var& node);
    Iresponse* process_req(Num& node);
    Iresponse* process_req(Input& node);
    Iresponse* process_req(LogicOperator& node);
    Iresponse* process_req(MathOperator& node);
    Iresponse* process_req(Assign& node);
};
}