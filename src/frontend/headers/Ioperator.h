#pragma once
#include "Inode.h"
#include <string>

int define_math_op(const std::string& op);
std::pair<int, bool> define_log_op(const std::string& op);
std::string get_math_op(int op);
std::string get_log_op(std::pair<int, bool> op);

namespace ParaCL{

class Ioperator: public Inode{

protected:

    Ioperator* left_ = nullptr;
    Ioperator* right_ = nullptr;

public:

    Ioperator(Ioperator* left, Ioperator* right);

    void add_left(Ioperator* new_left);
    void add_right(Ioperator* new_right);

    Iresponse* transfer_req_left(Irequest& cur_req);
    Iresponse* transfer_req_right(Irequest& cur_req);

    virtual ~Ioperator() = 0;
};


class Var final: public Ioperator{

    std::string name_;

public:

    Var(const std::string& name);

    std::string get_name() const;
    void set_name(std::string& name);

    Iresponse* get_request(Irequest& cur_req) override;
};

class Num final: public Ioperator{

    int value_ = 0; 

public:

    Num(int value);

    int get_value() const{ return value_; };
    void set_value(int value){ value_ = value; };

    Iresponse* get_request(Irequest& cur_req) override;
};

struct Input final: public Ioperator{

    Input();

    Iresponse* get_request(Irequest& cur_req) override;
};


enum LogicOp{

    Nothing_log = 0,
    Or,
    And,
    Less,
    Greater,
    Equal
};

class LogicOperator final: public Ioperator{

    int type_ = Nothing_log;
    bool equal_ = false;

public:
    
    LogicOperator(std::pair<int, bool> type, Ioperator* left, Ioperator* right);

    std::pair<int, bool> get_operator() const{ return std::make_pair(type_, equal_); }
    void set_operator(std::pair<int, bool> op);

    Iresponse* get_request(Irequest& cur_req) override;
};


enum MathOp{

    Nothing_math = 0,
    Plus,
    Minus,
    Mult,
    Div
};

class MathOperator final: public Ioperator{

    int type_ = Nothing_math;

public:

    MathOperator(int type, Ioperator* left, Ioperator* right);

    int get_operator() const{ return type_; }
    void set_operator(int type){ type_ = type; }

    Iresponse* get_request(Irequest& cur_req) override;
};

struct Assign final: public Ioperator{

    Assign(Ioperator* left, Ioperator* right);

    Iresponse* get_request(Irequest& cur_req) override;
};
}
