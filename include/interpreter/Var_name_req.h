/**
 * @file Var_name_req.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022
 * Запрос имени переменной(необходим когда другой запрос находится например в узле Assign и надо узнать имя lhs)
 */
#pragma once
#include "frontend/Irequest.h"

namespace ParaCL{

class Var_name_resp final: public Iresponse{

    std::string var_name_ref;

public:

    Var_name_resp(const std::string& var_name): var_name_ref{var_name}{}
    std::string get_var_name() const{ return var_name_ref; }
};

struct Var_name_req final: public Irequest{

    Iresponse* process_req(Var& node);
};
}
