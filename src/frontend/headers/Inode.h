#pragma once

class Irequest;
class Iresponse;

class Inode{

protected:

    Inode* prev_ = nullptr;
    int line_num_ = 0;

public:

    Inode(Inode* prev): prev_{prev}{}
    void add_prev(Inode* prev){ prev_ = prev; };
    void set_line_num(int line_num){ line_num_ = line_num; }
    int  get_line_num(){ return line_num_; }
    virtual Iresponse* get_request(Irequest& cur_req) = 0;
    virtual ~Inode(){}
};
