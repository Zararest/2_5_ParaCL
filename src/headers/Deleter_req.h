#include "Print_req.h"

class Deleter_req: public Irequest{

    Addr_req standart_addr_req;

    void delete_next_statement(Istatement& node);
    void delete_next_operators(Ioperator& node);

public:

    Iresponse* process_req(If& node);
    Iresponse* process_req(While& node);
    Iresponse* process_req(Assign& node);
    Iresponse* process_req(Print& node);

    Iresponse* process_req(Var& node){ return nullptr; };
    Iresponse* process_req(Num& node){ return nullptr; };
    Iresponse* process_req(Input& node){ return nullptr; };
    Iresponse* process_req(LogicOperator& node){ delete_next_operators(node); return nullptr; };
    Iresponse* process_req(MathOperator& node){ delete_next_operators(node); return nullptr; };
};