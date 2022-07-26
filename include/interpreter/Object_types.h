#pragma once
#include "interpreter/Objects_manager.h"

namespace ParaCL{

class VarInt final: public Object{

    int value_ = 0;

public:

    VarInt(const std::string& name, int value): Object{name}, value_{value}{}
    
    int get_value() const{ return value_; }
    void set_value(int value){ value_ = value; }
};  
}