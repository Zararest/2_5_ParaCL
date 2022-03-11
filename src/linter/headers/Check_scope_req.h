#pragma once
#include "../../frontend/headers/Irequest.h"
#include "Print_req.h"
#include <fstream>
#include <vector>
#include <unordered_set>

namespace ParaCL{

class Check_scope_req : public Irequest {
// May be we want string&?
	std::vector<std::unordered_set<std::string>> decl_var;
	std::vector<std::string> tmp_var;
    int cur_pos = 0;
    Addr_req standart_addr_req;
    bool error_occurred = false;

    void check_next_statement(Istatement& node);

public: 

    Check_scope_req();
    ~Check_scope_req();
    void Check_var(std::string const &var);
    void Check_vector();

    bool is_success(){ return !error_occurred; }

    Iresponse* process_req(If& node);
    Iresponse* process_req(While& node);
    Iresponse* process_req(Assign& node);
    Iresponse* process_req(Print& node);

    Iresponse* process_req(Var& node);
    Iresponse* process_req(Num& node);
    Iresponse* process_req(Input& node);
    Iresponse* process_req(LogicOperator& node);
    Iresponse* process_req(MathOperator& node);
};
}
