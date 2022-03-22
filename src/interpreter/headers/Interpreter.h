/**
 * @file Interpreter.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022
 * Класс интерпретатор наследуется от запроса Irequest и использует Object_manager
 */
#pragma once
#include "../../frontend/headers/Irequest.h"
#include "Objects_manager.h"
#include "Object_types.h"
#include "Var_name_req.h"

namespace ParaCL{

/**
 * @brief Возвращаемое значение интерперетатора.
 * Поскольку интерпретатор тоже является запросом, он возвращает из выражений значение через этот класс.
 */
class Value final: public Iresponse{

    int value_ = 0;

public: 

    Value(int value): value_{value}{}
    void set_value(int value){ value_ = value; }
    int get_value(){ return value_; }
};

/**
 * @brief Интерпретатор.
 * Переход между узлами осуществляется с помощью методов transfer_req_XXX, которые реализованы в каждом узле дерева.
 */
class Interpreter final: public Irequest{

    Object_manager obj_manager;
    Var_name_req standart_var_req;

public:

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