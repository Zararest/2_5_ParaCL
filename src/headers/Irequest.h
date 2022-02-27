#pragma once 
#include "Istatement.h"
#include "Ioperator.h"


struct Iresponse{   //response

    virtual ~Iresponse() = 0;
};
Iresponse::~Iresponse(){}

struct Irequest{
    
    virtual Iresponse& process_terminal(){}
    virtual Iresponse& process_req(If& node){}
    virtual Iresponse& process_req(While& node){}
    virtual Iresponse& process_req(Assign& node){}
    virtual Iresponse& process_req(Print& node){}

    virtual Iresponse& process_req(Var& node){}
    virtual Iresponse& process_req(Num& node){}
    virtual Iresponse& process_req(Input& node){}
    virtual Iresponse& process_req(LogicOperator& node){}
    virtual Iresponse& process_req(MathOperator& node){}

    virtual ~Irequest() = 0;
};
Irequest::~Irequest(){}