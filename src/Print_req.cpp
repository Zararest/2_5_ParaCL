#include "headers/Print_req.h"

void Print_req::print_next_statement(Istatement* node){

    if (node == nullptr){ return; }

    Iresponse* resp = node->transfer_req(standart_addr_req);
    Inode* next = static_cast<Addr_resp*>(resp)->get_addr();
    
    if (next != nullptr){

        out_file << node << "->" << next << std::endl;   //чтобы выдеклить следующий startement
        out_file << node << "->" << next << std::endl; 

        next->get_request(*this);
    }
    
}

Iresponse* Print_req::process_req(If& node){

    out_file << this << "[label = \"If\" fillcolor=lightblue]" << std::endl;

    Iresponse* resp = node.transfer_req_condition(standart_addr_req);
    Inode* condition = static_cast<Addr_resp*>(resp)->get_addr();


}

Iresponse* Print_req::process_req(If& node){

}

Iresponse* Print_req::process_req(If& node){

}

Iresponse* Print_req::process_req(If& node){

}

Iresponse* Print_req::process_req(If& node){

}

Iresponse* Print_req::process_req(If& node){

}

Iresponse* Print_req::process_req(If& node){

}

Iresponse* Print_req::process_req(If& node){

}

Iresponse* Print_req::process_req(If& node){

}
