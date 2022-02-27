#pragma once
#include "Irequest.h"

class Inode{

protected:

    Inode* prev_ = nullptr;

public:

    Inode(Inode* prev): prev_{prev}{}
    void add_prev(Inode* prev){ prev_ = prev; };
    virtual Iresponse& get_request(Irequest& cur_req);
    virtual ~Inode() = 0;
};

Inode::~Inode(){}
