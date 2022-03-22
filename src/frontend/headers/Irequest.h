#pragma once 
#include "Istatement.h"
#include "Ioperator.h"

namespace ParaCL{

/**
 * @brief Интерфейс возвращаемого значения запроса. 
 * В этом классе при необходимости может храниться информация, которую получил запрос.
 * Например в Var_name_resp (/interpreter/headers/Var_name_req.h) хранится имя переменной, которую получил класс Var_name_req.
 */
struct Iresponse{

    virtual ~Iresponse(){}
};

/**
 * @brief Интерфейс запроса к синтаксическому дереву.
 * На основе этой структуры создаются кассы для перехода по дереву и работы с ним.
 * Примером таких классов служат интерпретатор, распечатка дерева и проверка переменных на скоупы.
 * В реализации этих классов необходимы более маленькие классы запросов. Например есть класс, который получает имена переменных(/interpreter/headers/Var_name_req.h).
 * Он работает только с узлами типа Var, поэтому, чтобы не прописывать в каждом маленьком классе реализацию кажого метода, 
 * стандартное поведение (возврат nullptr) реализовано здесь(если убрать return nullptr, то это повлияет тольео на то,
 * сколько методов надо будет определять в маленьких классах запросов). 
 */
struct Irequest{
    
    virtual Iresponse* process_terminal(){ return nullptr; }
    virtual Iresponse* process_req(If& node){ return nullptr; }
    virtual Iresponse* process_req(While& node){ return nullptr; }
    virtual Iresponse* process_req(Scope& node){ return nullptr; }
    virtual Iresponse* process_req(Expression& node){ return nullptr; }
    virtual Iresponse* process_req(Print& node){ return nullptr; }

    virtual Iresponse* process_req(Var& node){ return nullptr; }
    virtual Iresponse* process_req(Num& node){ return nullptr; }
    virtual Iresponse* process_req(Input& node){ return nullptr; }
    virtual Iresponse* process_req(LogicOperator& node){ return nullptr; }
    virtual Iresponse* process_req(MathOperator& node){ return nullptr; }
    virtual Iresponse* process_req(Assign& node){ return nullptr; }

    virtual ~Irequest(){}
};
}