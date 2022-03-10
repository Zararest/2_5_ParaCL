#pragma once

class Irequest;
class Iresponse;

class Inode{

protected:

    Inode* prev_ = nullptr;

public:

    Inode(Inode* prev): prev_{prev}{}
    void add_prev(Inode* prev){ prev_ = prev; };
    virtual Iresponse* get_request(Irequest& cur_req) = 0;
    virtual ~Inode(){}
};
