/**
 * @file Deleter_req.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022
 * Наследник класса Irequest.
 */
#pragma once
#include "frontend/Irequest.h"
#include "linter/Nodes_addr_req.h" //здесь лежит класс запроса адреса узла

namespace ParaCL{

/**
 * @brief Удаление дерева.
 * 
 */
class Deleter_req final: public Irequest{

    Addr_req standart_addr_req;

    void delete_next_statement(Istatement& node);
    void delete_next_operators(Ioperator& node);

public:

    Iresponse* process_req(If& node);
    Iresponse* process_req(While& node);
    Iresponse* process_req(Scope& node);
    Iresponse* process_req(Expression& node);
    Iresponse* process_req(Print& node);

    Iresponse* process_req(Var& node){ return nullptr; };   //эти строчки можно было бы убрать тк такое поведение определено в Irequest
    Iresponse* process_req(Num& node){ return nullptr; };
    Iresponse* process_req(Input& node){ return nullptr; };
    Iresponse* process_req(LogicOperator& node){ delete_next_operators(node); return nullptr; };
    Iresponse* process_req(Assign& node){ delete_next_operators(node); return nullptr; };
    Iresponse* process_req(MathOperator& node){ delete_next_operators(node); return nullptr; };
};
}