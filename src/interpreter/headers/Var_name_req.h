#pragma once
#include "../../frontend/headers/Irequest.h"

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
