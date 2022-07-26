#pragma once

#include "./Symbol_table.h"

namespace ParaCL{

class Irequest;
class Iresponse;

/**
 * @brief Интерфейс узла синтаксического дерева.
 * У каждого узла дерева есть метод grt_request(), который позволяет работать с деревом с помощью наследников Irequest&. 
 * Каждый наследдник Irequest имеет перегруженный по ссылке на каждого наследника Inode метод process_request(),
 * который вызывается из get_request() в текущем узле.
 * Метод get_request() одинаково реализован у ВСЕХ узлов дерева, потому что мне необходимо виртуальное поведение в каждом случае.
 */
class Inode{

protected:

    Inode* prev_ = nullptr;
    TokenHandle token;

public:

    Inode(Inode* prev, TokenHandle handle): prev_{prev}{}
    virtual ~Inode(){}

    void add_prev(Inode* prev){ prev_ = prev; };
    //void set_handle(TokenHandle handle){ token = handle; }
    TokenHandle get_handle(){ return token; }

    virtual Iresponse* get_request(Irequest& cur_req) = 0;
};
}