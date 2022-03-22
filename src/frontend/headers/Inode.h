#pragma once

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
    int line_num_ = 0;

public:

    Inode(Inode* prev): prev_{prev}{}
    virtual ~Inode(){}

    void add_prev(Inode* prev){ prev_ = prev; };
    void set_line_num(int line_num){ line_num_ = line_num; }
    int  get_line_num(){ return line_num_; }

    virtual Iresponse* get_request(Irequest& cur_req) = 0;
};
}