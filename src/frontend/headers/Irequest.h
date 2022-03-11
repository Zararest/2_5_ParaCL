#pragma once 
#include "Istatement.h"
#include "Ioperator.h"

namespace ParaCL{

struct Iresponse{

    virtual ~Iresponse(){}
};

struct Irequest{
    
    virtual Iresponse* process_terminal(){ return nullptr; }
    virtual Iresponse* process_req(If& node){ return nullptr; }
    virtual Iresponse* process_req(While& node){ return nullptr; }
    virtual Iresponse* process_req(Assign& node){ return nullptr; }
    virtual Iresponse* process_req(Print& node){ return nullptr; }

    virtual Iresponse* process_req(Var& node){ return nullptr; }
    virtual Iresponse* process_req(Num& node){ return nullptr; }
    virtual Iresponse* process_req(Input& node){ return nullptr; }
    virtual Iresponse* process_req(LogicOperator& node){ return nullptr; }
    virtual Iresponse* process_req(MathOperator& node){ return nullptr; }

    virtual ~Irequest(){}
};
}