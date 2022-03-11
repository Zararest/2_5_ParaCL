#include "headers/Objects_manager.h"
#include <cassert>

using namespace ParaCL;

bool operator ==(const Objects_stack& lhs, const Objects_stack& rhs){

    return lhs.cmp(rhs);
}

Objects_stack::~Objects_stack(){

    while (stack_.size() != 0){

        delete stack_.back().first;
        stack_.pop_back();
    }
}

bool Object_manager::add_object(Object* obj){

    auto stack_it = objects_.find(obj->get_name());

    if (stack_it != objects_.end() && stack_it->second.top().second == num_of_scopes){

        return false;//это значит переопределение
    }

    auto new_back = std::make_pair(obj->get_name(), num_of_scopes);
    objects_stack.push_back(new_back);

    if (stack_it == objects_.end()){

        auto empl_ret = objects_.emplace(obj->get_name(), obj->get_name());//через emplace создаем новый стек с именем
        empl_ret.first->second.push_back(obj, num_of_scopes);
    } else{

        stack_it->second.push_back(obj, num_of_scopes);
    }

    return true;
}

Object* Object_manager::get_object(const std::string& name) const{

    auto stack_it = objects_.find(name);
    if (stack_it == objects_.end()){ return nullptr; }

    assert(stack_it->second.size() != 0);
    return stack_it->second.top().first;
}

void Object_manager::add_scope(){

    num_of_scopes++;
}

void Object_manager::remove_scope(){

    while (objects_stack.size() != 0 && objects_stack.back().second == num_of_scopes){

        auto stack_it = objects_.find(objects_stack.back().first);
        stack_it->second.pop_back();

        if (stack_it->second.size() == 0){

            objects_.erase(stack_it);
        }
    }

    num_of_scopes--;
}