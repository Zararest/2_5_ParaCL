#include <string>
#include <unordered_map>
#include <vector>

class Object{

    std::string name_;

public:

    Object(const std::string& name): name_{name}{}
    const std::string& get_name() const{ return name_; }
    virtual ~Object();
};


class Objects_stack final{//тут память утекает тк мы не освобождаем по указателю

    std::string stack_name;
    std::vector<std::pair<Object*, int>> stack_;

public:

    Objects_stack(const std::string& name): stack_name{name}{}
    void push_back(Object* obj, int scope_num){ stack_.emplace_back(obj, scope_num); }
    void pop_back(){ stack_.pop_back(); }
    int size() const{ return stack_.size(); }
    std::pair<Object*, int> top() const{ return stack_.back(); }

    bool cmp (const Objects_stack& obj) const{ return stack_name == obj.stack_name; }
};

bool operator ==(const Objects_stack& lhs, const Objects_stack& rhs);


class Object_manager final{

    std::unordered_map<std::string, Objects_stack> objects_;
    std::vector<std::pair<std::string, int>> objects_stack;
    int num_of_scopes = 0;

public:

    bool add_object(Object*);//возвращает false если объект уже существует в скоупе
    Object* get_object(std::string name);//возвращает объект если он был определен в одном из скоупов выше
    void add_scope();                    //вызывается при переходе в новый скоуп
    void remove_scope();                 //вызывается при выходе из скоупа
};