#include "headers/Check_scope_req.h"
#include <iostream>

void Check_scope_req::check_next_statement(Istatement& node){

    Iresponse* resp = node.transfer_req(standart_addr_req);
    Inode* next = static_cast<Addr_resp*>(resp)->get_addr();
    
    if (next != nullptr){

        node.transfer_req(*this);
    }
}

Check_scope_req::Check_scope_req() {

    std::unordered_set<std::string> top_ht;
    decl_var.push_back(top_ht);
}
Check_scope_req::~Check_scope_req() {}

Iresponse* Check_scope_req::process_req(If& node){

    Iresponse* resp = node.transfer_req_condition(standart_addr_req);
    Inode* condition = static_cast<Addr_resp*>(resp)->get_addr();

    if (condition != nullptr) {
        
        node.transfer_req_condition(*this);
        Check_vector();
        
    }

    resp = node.transfer_req_scope(standart_addr_req);
    Inode* scope = static_cast<Addr_resp*>(resp)->get_addr();

    if (scope != nullptr){

    	std::unordered_set<std::string> decl_ht;
    	decl_var.push_back(decl_ht); 

        node.transfer_req_scope(*this);
        //  tmp_var.clear();       There we can don't clean because next is right branch, when clear
        decl_var.pop_back();
    }

    check_next_statement(node);

    return nullptr;
}

Iresponse* Check_scope_req::process_req(While& node){
    
    Iresponse* resp = node.transfer_req_condition(standart_addr_req);
    Inode* condition = static_cast<Addr_resp*>(resp)->get_addr();

    if (condition != nullptr){

        node.transfer_req_condition(*this);
        Check_vector();
    }

    resp = node.transfer_req_scope(standart_addr_req);
    Inode* scope = static_cast<Addr_resp*>(resp)->get_addr();

    if (scope != nullptr){

    	std::unordered_set<std::string> decl_ht;
    	decl_var.push_back(decl_ht); 
        
        node.transfer_req_scope(*this);
        //  tmp_var.clear();         There too
        decl_var.pop_back();
    }   

    check_next_statement(node);

    return nullptr;
}

Iresponse* Check_scope_req::process_req(Assign& node){

    Iresponse* resp = node.transfer_req_lhs(standart_addr_req);
    Inode* var = static_cast<Addr_resp*>(resp)->get_addr();

    if (var != nullptr){

    	std::unordered_set<std::string>& decl_ht = decl_var.back();

        node.transfer_req_lhs(*this);

        auto only_elem = tmp_var.begin();
        decl_ht.insert(*(only_elem));
        tmp_var.clear();
    }

    resp = node.transfer_req_rhs(standart_addr_req);
    Inode* rhs = static_cast<Addr_resp*>(resp)->get_addr();

    if (rhs != nullptr){

        node.transfer_req_rhs(*this);
        Check_vector();
    }

    check_next_statement(node);

    return nullptr;
}

Iresponse* Check_scope_req::process_req(Print& node){
    
    Iresponse* resp = node.transfer_req_var(standart_addr_req);
    Inode* var = static_cast<Addr_resp*>(resp)->get_addr();

    if (var != nullptr){

    	node.transfer_req_var(*this);
// And there we can optimize
		Check_vector();
    }

    check_next_statement(node);

    return nullptr;
}

Iresponse* Check_scope_req::process_req(Var& node) {

	tmp_var.push_back(node.get_name());
    return nullptr;
}

Iresponse* Check_scope_req::process_req(Num& node) { return nullptr; }
Iresponse* Check_scope_req::process_req(Input& node) { return nullptr; }

Iresponse* Check_scope_req::process_req(LogicOperator& node) {
 
    Iresponse* resp = node.transfer_req_left(standart_addr_req);
    Inode* lhs = static_cast<Addr_resp*>(resp)->get_addr();

    if (lhs != nullptr){

        node.transfer_req_left(*this);
    }

    resp = node.transfer_req_right(standart_addr_req);
    Inode* rhs = static_cast<Addr_resp*>(resp)->get_addr();

    if (rhs != nullptr){

        node.transfer_req_right(*this);
    }

    return nullptr;
}

Iresponse* Check_scope_req::process_req(MathOperator& node) {
    
    Iresponse* resp = node.transfer_req_left(standart_addr_req);
    Inode* lhs = static_cast<Addr_resp*>(resp)->get_addr();

    if (lhs != nullptr){

        node.transfer_req_left(*this);
    }

    resp = node.transfer_req_right(standart_addr_req);
    Inode* rhs = static_cast<Addr_resp*>(resp)->get_addr();

    if (rhs != nullptr){

        node.transfer_req_right(*this);
    }

    return nullptr;
}

void Check_scope_req::Check_vector() {

	for (auto it = tmp_var.begin(); it != tmp_var.end(); ++it) {
    	Check_var(*it);
	}
    tmp_var.clear();
}
//     This func, not method
void Check_scope_req::Check_var(std::string const &var) {
	
	for (auto it = decl_var.begin(); it != decl_var.end(); ++it) {
    	if (it->end() == std::find(it->begin(), it->end(), var)) { // ?
    		std::cout << "Var " << var << " don't defined in this scope" << std::endl;
			break; // ?
		}
	}
}
/*
!it.contains(var)

template<class C, class T>
auto contains(const C& v, const T& x)
-> decltype(end(v), true)
{
    return end(v) != std::find(begin(v), end(v), x);
}
*/