#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

class Object{

    std::string name_;

public:

    Object(const std::string& name): name_{name}{}
    const std::string& get_name() const{ return name_; }
    virtual ~Object(){}
};


class Objects_stack final{

    std::string stack_name;
    std::vector<std::pair<Object*, int>> stack_;

public:

    Objects_stack(const std::string& name): stack_name{name}{}
    Objects_stack(const Objects_stack&) = delete;
    Objects_stack(Objects_stack&&) = delete;
    ~Objects_stack();

    Objects_stack& operator =(const Objects_stack&) = delete;
    Objects_stack& operator =(Objects_stack&&) = delete;

    void push_back(Object* obj, int scope_num){ stack_.push_back(std::make_pair(obj, scope_num)); }
    void pop_back(){ stack_.pop_back(); }
    int size() const{ return stack_.size(); }
    std::pair<Object*, int> top() const{ return stack_.back(); }

    bool cmp (const Objects_stack& obj) const{ return stack_name == obj.stack_name; }

    const std::string& get_name(){ return stack_name; }
};

bool operator ==(const Objects_stack& lhs, const Objects_stack& rhs);


class Object_manager final{

    std::unordered_map<std::string, Objects_stack> objects_;
    std::vector<std::pair<std::string, int>> objects_stack;
    int num_of_scopes = 0;

public:

    bool add_object(Object*);               //возвращает false если объект уже существует в скоупе
    Object* get_object(const std::string& name);//возвращает объект если он был определен в одном из скоупов выше
    void add_scope();                       //вызывается при переходе в новый скоуп
    void remove_scope();                    //вызывается при выходе из скоупа
};