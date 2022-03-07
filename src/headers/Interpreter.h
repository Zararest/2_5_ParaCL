#include "Irequest.h"
#include "Objects_manager.h"

class VarInt final: public Object{

    int value_ = 0;

public:

    VarInt(const std::string& name, int value);

    VarInt operator +=(const VarInt& rhs); 
    VarInt operator -=(const VarInt& rhs);
    VarInt operator *=(const VarInt& rhs);
    VarInt operator /=(const VarInt& rhs);

    operator bool();
};  

class Interpreter final: public Irequest{


};