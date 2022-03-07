#include "Irequest.h"
#include "Objects_manager.h"

class VarInt final: public Object{

    int value_ = 0;

public:

    VarInt(const std::string& name, int value);
    
    int get_value();
    void set_value(int value);
};  

class Value: public Iresponse{

    int value_ = 0;

public: 

    Value(int value): value_{value}{}
    void set_value(int value){ value_ = value; }
    int get_value(){ return value_; }
};


class Var_name_resp: public Iresponse{

    const std::string& var_name_ref;

public:

    Var_name_resp(const std::string var_name): var_name_ref{var_name}{}
    const std::string& get_var_name() const{ return var_name_ref; }
};

struct Var_name_req: public Irequest{

    Iresponse* process_req(Var& node);
};



class Interpreter final: public Irequest{

    Object_manager obj_manager;
    Var_name_req standart_var_req;

public:

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